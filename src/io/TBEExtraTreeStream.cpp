#include "file_io.hpp"

using namespace std;

char * newick_utree_recurse(const pll_unode_t * root, int level,
		pllmod_tbe_extra_info_t* extra_info,
		pllmod_tbe_split_info_t* split_info,
		const std::vector<unsigned int>& node_split_map
        )
{
  char * newick;
  int size_alloced = 0;
  assert(root != NULL);
  if (!root->next) // leaf node
  {
    size_alloced = asprintf(&newick, "%s:%f", root->label, root->length);
  }
  else
  {
    const pll_unode_t * start = root->next;
    const pll_unode_t * snode = start;
    char * cur_newick;
    do
    {
      char * subtree = newick_utree_recurse(snode->back, level+1, extra_info, split_info, node_split_map);
      if (subtree == NULL)
      {
        pll_errno = PLL_ERROR_MEM_ALLOC;
        snprintf(pll_errmsg, 200, "Unable to allocate enough memory.");
        return NULL;
      }

      if (snode == start)
      {
        cur_newick = subtree;
      }
      else
      {
        char * temp = cur_newick;
        size_alloced = asprintf(&cur_newick,
                                "%s,%s",
                                temp,
                                subtree);
        free(temp);
        free(subtree);
      }
      snode = snode->next;
    }
    while(snode != root);

    if (level > 0)
    {
      unsigned int id = node_split_map[root->clv_index];
      double avg_dist = extra_info->extra_avg_dist_array[id] / (double) extra_info->num_bs_trees;
      unsigned int depth = split_info[id].p;

      size_alloced = asprintf(&newick,
                                "(%s)%d|%f|%d:%f",
                                cur_newick,
                                id,
								avg_dist,
								depth,
                                root->length);
      free(cur_newick);
    }
    else
      newick = cur_newick;
  }

  if (size_alloced < 0)
  {
    pll_errno = PLL_ERROR_MEM_ALLOC;
    snprintf(pll_errmsg, 200, "memory allocation during newick export failed");
    return NULL;
  }

  return newick;
}

char * utree_export_newick(const pll_unode_t * root,
                           int export_rooted,
                           double root_brlen,
						   pllmod_tbe_extra_info_t* extra_info,
						   pllmod_tbe_split_info_t* split_info,
						   const std::vector<unsigned int>& node_split_map
                           )
{
  char * newick;
  char * subtree1;
  char * subtree2;
  int size_alloced;

  if (!root) return NULL;

  if (!root->next) root = root->back;

  unsigned int id = node_split_map[root->clv_index];
  double avg_dist = extra_info->extra_avg_dist_array[id] / (double) extra_info->num_bs_trees;
  unsigned int depth = split_info[id].p;

  if (export_rooted)
  {
    subtree1 = newick_utree_recurse(root->back, 1, extra_info, split_info, node_split_map);
    subtree2 = newick_utree_recurse(root, 0, extra_info, split_info, node_split_map);

    size_alloced = asprintf(&newick,
                            "(%s,(%s)%d|%f|%d:%f):0.0;",
                            subtree1,
                            subtree2,
                            id,
							avg_dist,
							depth,
                            root_brlen);
  }
  else
  {
    subtree1 = newick_utree_recurse(root->back, 1, extra_info, split_info, node_split_map);
    subtree2 = newick_utree_recurse(root, 0, extra_info, split_info, node_split_map);

    size_alloced = asprintf(&newick,
                            "(%s,%s)%d|%f|%d:0.0;",
                            subtree1,
                            subtree2,
                            id,
							avg_dist,
							depth);
  }

  free(subtree1);
  free(subtree2);

  if (size_alloced < 0)
  {
    pll_errno = PLL_ERROR_MEM_ALLOC;
    snprintf(pll_errmsg, 200, "memory allocation during newick export failed");
    return NULL;
  }

//  printf("newick: %s\n", newick);

  return (newick);
}

TBEExtraTreeStream& operator<<(TBEExtraTreeStream& stream, const TransferBootstrapTree& tree)
{
  pllmod_tbe_extra_info_t* extra_info = tree.get_extra_info();
  const std::vector<pll_unode_t*> split_node_map = tree.get_split_node_map();
  pllmod_tbe_split_info_t* split_info = tree.get_split_info();
  std::vector<unsigned int> node_split_map(split_node_map.size());
  for (size_t i = 0; i < split_node_map.size(); ++i) {
	  node_split_map[split_node_map[i]->clv_index] = i;
  }
  tree.pll_utree();

  char * newick_str = utree_export_newick(&tree.pll_utree_root(), 0, 0, extra_info, split_info, node_split_map);
  if (newick_str)
  {
    stream << newick_str << std::endl;
    free(newick_str);
  }
  else
  {
    assert(pll_errno);
    libpll_check_error("Failed to generate Newick");
  }
  return stream;
}


