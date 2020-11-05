#pragma once
#include <algorithm>
#include <vector>
#include <iterator>
#include <initializer_list>
#include "node.h"



class removable
{
  
public:
  
  removable() = default;
  
  removable(const std::initializer_list<int>&);
  
  removable(const removable&) = default;

  removable(removable&&) = default;
  
  removable& operator=(removable&&) = default;

  removable& operator=(const removable&) =default;
  
  ~removable() = default;

  int rank() const;

  bool contains_node(const node&) const;

  bool is_inner(const removable&, int) const;

  node& operator[](const int i)
  {
    return nodes[i];
  }
  
  removable delete_node(int) const;
  
  const node& operator[](int index) const
  {
    return nodes[index];
  }
    
  int size() const
  {
    return nodes.size();
  }

  auto begin() const
  {
    return nodes.crbegin();
  }
  auto end() const
  {
    return nodes.crend();
  }
  
private:

  std::vector<node> nodes;
 
  void initialize(const std::initializer_list<int>&);

  void insert(const int index, const node& src)
  {
    auto iter = nodes.begin();
    iter += index;
    nodes.insert(iter, src);
  }
  
  void append(const node& src)
  {
    nodes.push_back(src);
  }

  void erase(const int index)
  {
    auto iter = nodes.cbegin();
    iter += index;
    nodes.erase(iter);
  }	

};
