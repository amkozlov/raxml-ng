#ifndef MODELTEST_HPP_
#define MODELTEST_HPP_
#include "../TreeInfo.hpp"
#include "../Optimizer.hpp"


class ModelTest {
public:
    ModelTest(TreeInfo &treeinfo, const Tree &tree, Optimizer& optimizer);

    void optimize_model();
private:

    TreeInfo &treeinfo;
    const Tree &tree;
    Optimizer& optimizer;

};



#endif //MODELTEST_HPP_
