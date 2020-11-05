#pragma once

#include </usr/include/tbb/tbb.h>
#include "matrices.h"
#include "mdata.h"



typedef Eigen::Triplet<mpq_class> qtriplet;

template <typename F, typename T>
class sform
{
 private:

  const int rank;

  const int s_dim;

  matrices<T> transp;

public:
  
  mdata mat_data;
  
  sform();

  sform(const tableaux&);
  
  ~sform() = default;

  const T& operator[](int i)
  {
    return transp[i - 1];
  }

  void erase(int);

  void clear();

};


template<typename F, typename T>
inline sform<F, T>::sform():
  rank{0}, s_dim{0}, transp{matrices<T>(rank - 1, s_dim)}, mat_data{mdata()}
{
}

template<typename F, typename T>
inline sform<F, T>::sform(const tableaux& src)
  : rank{src.rank()},
    s_dim{src.size()},
    transp{matrices<T>(rank - 1, s_dim)},
    mat_data{mdata(rank - 1)}
{
  tbb::parallel_for(0,
		    rank - 1,
		    1,
		    [&](int k){
		      std::vector<qtriplet> triplets{};
		      auto r{rank - 2 - k};
		      auto& mat = transp[r];
		      for (int j = 0; j < s_dim; ++j)
			{
			  if (src[j].row_eq(k+1))
			    {
			      triplets.push_back({j, j, {1, 1}});
			    }
			  else if (src[j].column_eq(k+1))
			    {
			      triplets.push_back({j, j, {-1, 1}});
			    }
			  else if (src[j].dominant(k+1))
			    {
			      int i = src.get_sim(j, k+1);
			      int c_diff = src[j].cont_diff(k+1);
			      triplets.push_back({j, j, {-1, c_diff}});
			      triplets.push_back({i, j, {1, 1}});
			      triplets.push_back({j, i, {c_diff * c_diff - 1, c_diff * c_diff}});
			      triplets.push_back({i, i, {1, c_diff}});
			      mat_data.emplace(r, i, j);
			    }
			}
		      mat.setFromTriplets(triplets.begin(), triplets.end());
		      mat.makeCompressed();
		    });
}

template<typename F, typename T>
inline void sform<F, T>::erase(int i)
{
  transp.erase(i);
}

template<typename F, typename T>
inline void sform<F, T>::clear()
{
  transp.clear();
}











