#pragma once

#include <initializer_list>
#include <vector>
#include <numeric>
#include <functional>
#include "removable.h"

class tableau
{
public:

  tableau();

  tableau(const std::initializer_list<int>&);

  tableau(const node&, const removable&&);
  
  tableau(const tableau&) = default;

  tableau(tableau&&) = default;
  
  tableau& operator=(tableau&&) = default;
  
  tableau& operator=(const tableau&) = default;

  ~tableau() = default;

  const node& operator[](const int i) const;

  bool is_inner(const removable&, int) const;

  int cont_diff(int i) const;
  
  tableau delete_node(int) const;

  void append(node&);

  int size() const
  {
    return nodes.size();
  }

  int num_removables() const
  {
    return removable_nodes.size();
  }
  
  auto begin() const
  {
    return nodes.cbegin();
  }

  auto end() const
  {
    return nodes.cend();
  }

  inline int content(int i) const
  {
    return nodes[i].content();
  }
  
  bool is_sim(const tableau&, int) const;

  bool row_eq(int) const;

  bool column_eq(int) const;

  bool dominant(int) const;

  //ranges::filter_view

private:

  removable removable_nodes;
  
  std::vector<node> nodes;

  void append(const node&);

};

