
#include "tableau.h"

tableau::tableau()
{
  nodes = {};
  removable_nodes = removable();
}

tableau::tableau(const std::initializer_list<int>& src):
  nodes{{}}, removable_nodes{removable(src)}
{
  nodes.reserve(std::accumulate(src.begin(), src.end(), 0));
}

tableau::tableau(const node& n_src, const removable&& r_src):
  nodes{n_src}, removable_nodes{removable(r_src)} {}

const node& tableau::operator[](int i) const
{
  return nodes[i];
}

void tableau::append(const node& src)
{
  nodes.push_back(src);
}

int tableau::cont_diff(int i) const
{
  return content(i) - content(i-1);
}

tableau tableau::delete_node(int index) const
{
  auto tmp = *this;
  tmp.append(removable_nodes[index]);
  tmp.removable_nodes = tmp.removable_nodes.delete_node(index);
  return tmp;
}

bool tableau::is_inner(const removable& inner, int i) const
{
  return inner.contains_node(removable_nodes[i]);
}

bool tableau::is_sim(const tableau& other, int i) const
{
  const auto& tmp = *this;
  for (int k = 0; k < size(); ++k)
    {
      if (other[k] != tmp[k])
	{
	  if (k == i - 1 || k == i)
	    {
	    }
	  else
	    {
	      return false;
	    }
	}
    }
  return true;
}

bool tableau::row_eq(int i) const
{
  const auto& tmp = *this;
  return tmp[i].row_eq(tmp[i-1]);
}

bool tableau::column_eq(int i) const
{
  const auto& tmp = *this;
  return tmp[i].column_eq(tmp[i-1]);
}

bool tableau::dominant(int i) const
{
  const auto& tmp = *this;
  return tmp[i - 1] < tmp[i];
}

std::ostream& operator<<(std::ostream& out, tableau const& src)
{
  std::ostringstream tmp{};
  int i = 0;
  int k = src.size();
  for (const auto& x : src)
    {
      ++i;
      if (k==1)
	{
	  tmp << '(' << x << ')' << '\n';
	}
      else if (i == 1)
	{
	  tmp << '(' << x << ',';
	}
      else if (i < k)
	{
	  tmp << x << ',';
	}
      else
	{
	  tmp << x << ')' << '\n';
	}
    }
  out << tmp.str();

  return out;
}
