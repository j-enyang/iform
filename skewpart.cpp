#pragma once

#include "skewpart.h"


skewpart::skewpart(const std::initializer_list<int>& i_src,
		   const std::initializer_list<int>& o_src):
  inner{i_src}, outer{o_src},
  t_rank{std::accumulate(o_src.begin(), o_src.end(), 0) -
	 std::accumulate(i_src.begin(), i_src.end(), 0)}
{
}

int skewpart::rank() const
{
  return t_rank;
}
