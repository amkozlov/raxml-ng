#ifndef RAXML_AUTEST_HPP_
#define RAXML_AUTEST_HPP_

#include <memory>
#include <utility>
#include "../types.hpp"
#include "../PartitionedMSA.hpp"

extern const doubleVector AU_DEFAULT_SCALES;
extern const uintVector AU_DEFAULT_REPS;

/**
 * Calculates RELL bootstrap replicates at different replicate sequence lengths in parallel, calculate empirical CDF
 * functions from the resulting BP counts, and calculate the AU test p-value from that.
 *
 * The class is instanced with a pointer to the MSA and persite-loglikelihood matrix, as well as scaling factors for the
 * replicate sequence lengths and number of replicates per scale, a random seed, and the number of trees.
 *
 * It then allows repeated calculation of the AU test in parallel, as long as the number of trees remains constant.
 * The bootstrapping and p value calculation happens in three steps, since some of them can be run in parallel, and
 * some happen on one thread only, after gathering the data.
 */
class AuTest {
public:
    AuTest(const std::shared_ptr<PartitionedMSA> &msa,
           const std::vector<std::vector<doubleVector> > &persite_loglh,
           const doubleVector &scales,
           const uintVector &num_replicates,
           const int seed) : AuTest(msa, make_persite_vec(persite_loglh), scales, num_replicates, seed) {
    }

    AuTest(std::shared_ptr<PartitionedMSA> msa,
           std::vector<std::vector<const double *> > loglh_matrices,
           doubleVector scales,
           uintVector num_replicates,
           const int seed) : msa(std::move(msa)),
                              persite_loglh(std::move(loglh_matrices)),
                              test_statistics(nullptr),
                              normalized_statistics(nullptr),
                              p_values(persite_loglh.size()),
                              finished(false),
                              scales(std::move(scales)),
                              num_replicates(std::move(num_replicates)),
                              num_trees(persite_loglh.size()),
                              seed(seed) {
    }

    // custom move constructor
    AuTest(AuTest &&other) noexcept : msa(std::move(other.msa)),
                                      persite_loglh(std::move(other.persite_loglh)),
                                      test_statistics(other.test_statistics),
                                      normalized_statistics(other.normalized_statistics),
                                      p_values(std::move(other.p_values)),
                                      finished(other.finished),
                                      scales(std::move(other.scales)),
                                      num_replicates(std::move(other.num_replicates)),
                                      num_trees(other.num_trees),
                                      seed(other.seed) {
        other.test_statistics = nullptr;
        other.normalized_statistics = nullptr;
    }


    virtual ~AuTest() {
        if (test_statistics) {
            // free individual matrices
            for (unsigned int i = 0; i < scales.size(); i++) {
                if (!test_statistics[i]) continue;
                free(test_statistics[i]);
            }
            free(test_statistics);
        }

        // if we have normalized statistics that are different from test statistics
        if (normalized_statistics && normalized_statistics != test_statistics) {
            for (unsigned int i = 0; i < scales.size(); i++) {
                if (!normalized_statistics[i]) continue;
                free(normalized_statistics[i]);
            }
            free(normalized_statistics);
        }
    }

    // disable copy-construction and assignment, since we are guarding a C-style allocation
    AuTest(const AuTest &) = delete;

    AuTest &operator=(const AuTest &) = delete;

    /**
     *  Allocate the test statistic arrays for bootstrap replicates for all trees.
     *
     *  @param inplace if true, normalized statistics are stored in-place in the statistics array, overwriting
     *  bootstrap replicates.
     */
    void allocate_test_statistics(bool inplace = true);

    /**
     * Run the RELL bootstrapping on the per-site log-likelihood vectors assigned to this instance.
     * Since the test assumes that no fine-grained parallelization happens across MPI ranks, the vectors are all
     * complete.
     *
     * @param num_rows how many trees to run bootstrap for. This should match `num_trees` given to the constructor,
     *                  except if the method is called with `offset` to run partial bootstraps in parallel
     * @param offset    offset in the tree array. The function will run bootstrap for all trees in the range
     *                  `offset..offset + num_trees` (exclusive).
     */
    void run_bootstrap(size_t num_rows, size_t offset = 0);

    /**
     * Run the normalization step. This can only be done on the entire replicate matrix, it cannot be called on partial
     * matrices, so before this is called (on the master thread), all other threads need to be done.
     */
    void finalize_test_statistics();

    /**
     * Calculate the p-values from the previously generated bootstrap replicates.
     * These are cheap to compute compared to bootstrapping, but require finalized test statistics, so they can either
     * be calculated on the master worker which holds all bootstrap matrices, or the bootstrap matrices need to be
     * broadcasted to other workers.
     */
    void calculate_p_values();

    /**
     * Get the finished p-values after calling `calculate_p_values`.
     *
     * @return A vector of p values, in the order of the rows of the persite log-likelihood matrix
     */
    doubleVector &get_p_values();

    /**
     * Reset the test statistics to be able to re-run bootstrapping.
     */
    void reset_test_statistics();

    /**
     * @return true, if the p-values have been calculated
     */
    [[nodiscard]] bool is_finished() const;

private:
    /**
     * Shared pointer to the input MSA to obtain site weights and dimensions during bootstrapping.
     */
    std::shared_ptr<PartitionedMSA> msa;

    /**
     * A vector containing one per-site log-likelihood vector per partition of each input tree
     */
    std::vector<std::vector<const double *> > persite_loglh;

    /**
     * The bootstrap test statistics as generated by `run_bootstrap` and finalized by `finalize_test_statistics`.
     * When these change, the `p_values` become invalidated until `calculate_p_values` is called.
     */
    double **test_statistics;

    /**
     * The normalized test statistics generated by a call to normalize_test_statistics
     */
    double **normalized_statistics;

    /**
     * The finished AU test p values, which are calculated by `calculate_p_values`. These values are invalid as long
     * as `finished` is false.
     */
    doubleVector p_values;

    /**
     * True if calculate_p_values has been called and the test statistics have not been changed since then
     */
    bool finished;

    /**
     * Scaling factors for the multiscale bootstrap
     */
    doubleVector scales;

    /**
     * Number of bootstrap replicates to generate for each individual scaling factor
     */
    uintVector num_replicates;

    /**
     * Number of input trees
     */
    unsigned int num_trees;

    /**
     * Random seed
     */
    int seed;

    static std::vector<std::vector<const double *> > make_persite_vec(
        const std::vector<std::vector<doubleVector> > &persite_loglh) {
        std::vector<std::vector<const double *> > loglh_matrices;
        loglh_matrices.reserve(persite_loglh.size());

        for (auto &partitions: persite_loglh) {
            std::vector<const double *> partition_logh;
            partition_logh.reserve(partitions.size());
            for (auto &partition: partitions) {
                partition_logh.push_back(partition.data());
            }
            loglh_matrices.push_back(partition_logh);
        }

        return loglh_matrices;
    }
};

#endif //RAXML_AUTEST_HPP_
