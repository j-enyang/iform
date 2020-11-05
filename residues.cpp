
#include "residues.h"

residues::residues() : r_classes({}) {}

residues::residues(const tableaux& src, int p) : r_classes({{0}})
{
  build_r(src, p);
}

void residues::append(int i, int j)
  {
    r_classes[i].push_back(j);
  }

void residues::append(int j)
{
  r_classes.push_back(std::vector<int>{j});
}

auto residues::begin() const
  {
    return r_classes.cbegin();
  }

auto residues::end() const
  {
    return r_classes.cend();
  }

int residues::element(int i, int j) const
{
  return r_classes[i][j];
}

int residues::num_classes() const
{
  return r_classes.size();
}

int residues::class_size(int i) const
{
  return r_classes[i].size();
}

void residues::build_r(const tableaux& src, int p)
{
  int s_rank = src[0].size();
  int s_dim = src.size();
  std::vector<std::vector<int>> p_contents(s_dim);
  for (int i = 0; i < s_dim; ++i)
    {
      p_contents[i] = std::vector<int>(s_rank);
      for (int j = 0; j < s_rank; ++j)
	{
	  p_contents[i][j] = src[i].content(j) % p;
	  if (p_contents[i][j] < 0)
	    {
	      p_contents[i][j] += p;
	    }
	}
    }
  for (int i = 1; i < s_dim; ++i)
    {
      bool trip{false};
      for (int j = 0; j < r_classes.size(); ++j)
	{
	  if (p_contents[i] == p_contents[r_classes[j][0]])
	    {
	      r_classes[j].push_back(i);
	      trip = true;
	      break;
	    }
	}
      if (trip == false)
	{
	  r_classes.push_back(std::vector<int>{i});
	}
    }
}
