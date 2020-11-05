#include "tableaux.h"


tableaux::tableaux() : paths{}, inner_nodes{}, outer_nodes{}, t_rank{0}
{
}

tableaux::tableaux(const skewpart& src)
  : paths{},
    inner_nodes{src.inner},
    outer_nodes{src.outer}, 
    t_rank{src.rank()}
{
  build_tableaux();
}

const tableau& tableaux::operator[](int i) const
{
  return paths[i];
}

int tableaux::rank() const
{
  return t_rank;
}

int tableaux::size() const
{
  return paths.size();
}

void tableaux::initialize()
{
  for (int i = outer_nodes.size() - 1; i >= 0; --i)
    {
      if (!outer_nodes.is_inner(inner_nodes, i))
	{
	  append(tableau(outer_nodes[i], outer_nodes.delete_node(i)));
	}
    }
}

void tableaux::build_tableaux()
{
  initialize();
  auto tmp = *this;
    for (int i = 1; i < rank(); ++i)
    {
      tmp = extend_tableaux(tmp);
    }
  tmp.paths.shrink_to_fit();     
  *this = tmp;
}

tableaux tableaux::extend_tableaux(const tableaux& src) const
{
  auto new_paths = tableaux();
  new_paths.t_rank = rank();
  for (auto& path : src)
    {
      for (int i = path.num_removables() - 1; i >= 0; --i)
        {
	  if (!path.is_inner(inner_nodes, i))
	    {
	      new_paths.append(path.delete_node(i));
	    }
        }
    }
  return new_paths;
}

int tableaux::get_sim(int t, int i) const
{
  const auto& tmp = *this;
  for (int k = t + 1; k < size(); ++k)
    {
      if (tmp[t].is_sim(tmp[k], i))
	{
	  return k;
	}
    }
  return -1;  // calling functions guard against this value ever being returned
}

