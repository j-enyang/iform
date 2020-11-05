#pragma once
#include <vector>


template<typename T>
class matrices
{
 private:

  std::vector<T> stored;

 public:

  matrices();
  
  matrices(int, int);

  ~matrices() = default;

  T& operator[](int);

  const T& operator[](int) const;

  int size() const;

  void erase(int);

  void clear();

};

template<typename T>
inline matrices<T>::matrices() : stored{{}}
{
}

template<typename T>
inline matrices<T>::matrices(int n, int dim) : stored{std::vector<T>(n,T(dim,dim))}
{
}

template<typename T>
T& matrices<T>::operator[](int i)
{
  return stored[i];
}

template<typename T>
const T& matrices<T>::operator[](int i) const
{
  return stored[i];
}

template<typename T>
inline void matrices<T>::erase(int index)
{
  auto iter = stored.begin();
  iter += index;             
  stored.erase(stored.begin(),iter);
  stored.shrink_to_fit();
}

template<typename T>
inline void matrices<T>::clear()
{
  stored = std::vector<T>(0);
}

template<typename T>
inline int matrices<T>::size() const
{
  return stored.size();
}
