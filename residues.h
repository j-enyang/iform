#pragma once
#include <vector>

class residues
{
 private:

  std::vector<std::vector<int>> r_classes;

  void build_r(const tableaux&, int);
  
 public:

  residues();

  residues(const tableaux&, int);  

  ~residues() = default;
  
  void append(int, int);

  void append(int);

  auto begin() const;

  auto end() const;

  int element(int, int) const;

  int num_classes() const;

  int class_size(int) const;
  
};
