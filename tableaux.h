#pragma once
#include "tableau.h"
#include "skewpart.h"

class tableaux
{

public:

  tableaux();

  tableaux(const skewpart&);

  tableaux(const tableaux&) = default;

  tableaux(tableaux&&) = default;

  tableaux& operator=(const tableaux&) = default;

  tableaux& operator=(tableaux&&) = default;
  
  ~tableaux() = default;

  const tableau& operator[](int) const;
  
  auto begin() const
  {
    return paths.cbegin();
  }
  
  auto end() const
  {
    return paths.cend();
  }

  int rank() const;
  
  int size() const;
  
  int get_sim(int, int) const;

 private:

  int t_rank;

  removable inner_nodes;

  removable outer_nodes;
  
  std::vector<tableau> paths;

  void initialize();
  
  tableaux extend_tableaux(const tableaux&) const;

  void build_tableaux();
  
  void append(const tableau& src)
  {
    paths.push_back(src);
  }
 
};

