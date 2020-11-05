#pragma once

#include "removable.h"



class skewpart
{
  
 public:
  
  skewpart() = default;

  skewpart(const std::initializer_list<int>&, const std::initializer_list<int>&);

  ~skewpart() = default;

  removable inner;

  removable outer;

  int rank() const;

 private:

  int t_rank;

 };
