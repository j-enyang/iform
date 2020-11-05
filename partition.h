#pragma once

#include "removable.h"



class partition
{
public:
  
  partition() = default;
  
  partition(std::initializer_list<int> src);

  auto begin() const;

  auto end() const;

  auto rank() const;

  removable removable_nodes;

private:

  std::vector<int> parts;		

  const int t_rank;
  
};



