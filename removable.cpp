
#include "removable.h"


removable::removable(const std::initializer_list<int>& src)
{
  initialize(src);
}

bool removable::contains_node(const node& target_node) const
{
  return std::find(nodes.begin(), nodes.end(), target_node) != nodes.end();
}

bool removable::is_inner(const removable& inner, int i) const
{
  return inner.contains_node(nodes[i]);
}

int removable::rank() const
{
  if (this->size() == 0)
    {
      return 1;
    }
  
  int p_rank = (nodes[0].row()) * (nodes[0].column());

  if (this->size() == 1)
    {
      return p_rank;
    }
  else
    {
      for (int i = 1; i < size(); ++i)
	{
	  p_rank += (nodes[i - 1].row() - nodes[i].row()) * nodes[i].column();
	}
    }
  return p_rank;
}

void removable::initialize(const std::initializer_list<int>& src)
{
  std::vector<int> parts{src};
  std::sort(parts.begin(), parts.end(), std::greater<int>());
  for (std::size_t i = 0; i < parts.size() - 1; i++)
    {
      if (parts[i] > parts[i + 1])
	{
	  append(node(i + 1, parts[i]));
	}
    }
  int k = parts.size() - 1;
  append(node(k + 1, parts[k]));
}

removable removable::delete_node(int index) const
{
  removable a_nodes = *this;
  int row = a_nodes[index].row();
  int column = a_nodes[index].column();
  int size = a_nodes.size();
    
  if (size == 1 && row == 1 && column == 1)		// only removable node (1,1)
    {
      a_nodes.erase(index);
      a_nodes.nodes.shrink_to_fit();
    }
  else if (size == 1 && row == 1)			// only removable node (1,j), j > 1
    {
      a_nodes.nodes[index] = node(row, column - 1);
    }
  else if (size == 1 && column == 1)			// only removable node (i, 1), i > 1
    {
      a_nodes.nodes[index] = node(row - 1, column);
    }
  else if (size == 1)					// only removable node (i,j), i > 1, j > 1
    {
      a_nodes.nodes[index] = node(row - 1, column);
      a_nodes.append(node(row, column-1));
    }
  else if (index == 0)                                  // removable node with smallest row_index
    {
      const node& next = a_nodes[index + 1];
      if (row == 1 && next.column() == column - 1)
	{
	  a_nodes.erase(index);
	}
      else if (row == 1)
	{
	  a_nodes.nodes[index] = node(row, column - 1);
	}
      else if (next.column() == column - 1)
	{
	  a_nodes.nodes[index] = node(row - 1, column);
	}
      else
	{
	  a_nodes.nodes[index] = node(row, column - 1);
	  a_nodes.insert(index, node(row - 1, column));
	}
    }
  else if (index == size - 1)	                	// removable node in the last row
    {
      const node& previous = a_nodes[index - 1];
      if (column == 1 && previous.row() < row - 1)
	{
	  a_nodes.nodes[index] = node(row - 1, column);
	}
      else if (column == 1 && previous.row() == row - 1)
	{
	  a_nodes.erase(index);
	}
      else if (column > 1 && previous.row() == row - 1)
	{
	  a_nodes.nodes[index] = node(row, column - 1);
	}
      else if (column > 1 && previous.row() < row - 1)
	{
	  a_nodes.nodes[index] = node(row - 1, column);
	  a_nodes.append(node(row, column - 1));
	}
    }
  else if (0 < index && index < size - 1)            // neither the first nor the last removable
    {
      const node& previous = a_nodes[index - 1];
      const node& next = a_nodes[index + 1];
      if (previous.row() == row - 1 && next.column() < column - 1)
	{
	  a_nodes.nodes[index] = node(row, column - 1);
	}
      else if (previous.row() < row - 1 && next.column() < column - 1)
	{
	  a_nodes.nodes[index] = node(row, column - 1);
	  a_nodes.insert(index, node(row - 1, column));
	}
      else if (previous.row() < row - 1)
	{
	  a_nodes[index] = node(row - 1, column);
	}
      else if (next.column() == column - 1)
	{
	  a_nodes.erase(index);
	}	
    }
  return a_nodes;
}


std::ostream& operator<<(std::ostream& out, removable const& src)
{
  std::ostringstream tmp{};
  int i = 0;
  int k = src.size();
  for (auto x : src)
    {
      ++i;
      
      if (k == 1)
	tmp << '(' << x << ')' << '\n' ;
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

