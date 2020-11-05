#include "partition.h"`


partition::partition(std::initializer_list<short> src) :
  parts{ src }, removable_nodes{removable(src)}
{
}


auto partition::begin() const
{
  return parts.cbegin();
}

auto partition::end() const
{
  return parts.cend();
}
