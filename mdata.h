#pragma once

#include <map>


class mdata
{

  typedef std::vector<std::map<int,int>> d_type;
  
 private:
  
  d_type mat_data;
  
 public:

  mdata() = default;

  mdata(int);
  
  ~mdata() = default;

  std::map<int,int>& operator[](int);

  int size() const;

  void emplace(int, int, int);
  
};

inline mdata::mdata(const int len) : mat_data{d_type(len)}
{
  for (int i{0}; i < len; ++i)
    mat_data[i] = {};
}
  
inline std::map<int,int>& mdata::operator[](int i)
{
  return mat_data[i];
}

inline int mdata::size() const
{
  return mat_data.size();
}

inline void mdata::emplace(int k, int i, int j)
{
  mat_data[k].emplace(i, j);
}
