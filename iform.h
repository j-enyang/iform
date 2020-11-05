#pragma once

#include "sform.h"
#include "residues.h"

template <typename F, typename T>
class iform
{
 private:

  const int s_rank;

  const int s_dim;

  const int p;

  sform<F, T> s_gens;
  
  residues p_classes;
    
  T p_basis;

  T p_inverse;

  matrices<T> p_gens;

  matrices<T> p_jels;

  const T m_basis();

  void i_basis();
  
  void j_elems(const tableaux&);
  
  void clear();
  
public:

  iform();

  iform(const tableaux&, int prime);
  
  ~iform() = default;

};

template<typename F, typename T>
inline iform<F, T>::iform()
  : s_rank{0},
    s_dim{0}, p{2},
    s_gens{sform<F, T>()},
    p_classes{residues()},
    p_basis{T()},
    p_inverse{T()},
    p_jels{matrices<T>()},
    p_gens{matrices<T>()}
{
}

template<typename F, typename T>
inline iform<F, T>::iform(const tableaux& src, int prime)
  : s_rank{src.rank()},
    s_dim{src.size()}, p{prime},
    s_gens{sform<F, T>(src)},
    p_classes{residues(src, p)},
    p_basis{T(s_dim, s_dim)},
    p_inverse{T(s_dim, s_dim)},
    p_jels{matrices<T>(s_rank, s_dim)},
    p_gens{matrices<T>(s_rank - 1, s_dim)}
{
  i_basis();
  j_elems(src);
  Eigen::SparseLU<T, Eigen::COLAMDOrdering<int>> solver;
  solver.analyzePattern(p_basis);
  solver.factorize(p_basis);
  tbb::parallel_for(0, p_gens.size(), 1, [&](int i){
      p_gens[i] = solver.solve(s_gens[i + 1] * p_basis);
    });
  tbb::parallel_for(0, p_jels.size(), 1, [&](int i){
      T x = solver.solve(p_jels[i] * p_basis);
      p_jels[i] = x;
    }); 
}

template<typename F, typename T>
inline void iform<F, T>::j_elems(const tableaux& src)
{
  tbb::parallel_for(0, s_rank, 1, [&](int i){
      std::vector<qtriplet> triplets{};
      triplets.reserve(s_dim);
      for (int j = 0; j < s_dim; ++j)
	{
	  const auto& path{src[j]};
	  triplets.push_back({j, j, {path.content(s_rank - 1 - i), 1}});
	}
        p_jels[i].setFromTriplets(triplets.begin(), triplets.end());
	p_jels[i].makeCompressed();
    });
}

template<typename F, typename T>
inline const T iform<F, T>::m_basis()
{
  T mbasis{T(s_dim, s_dim)};
  std::vector<qtriplet> triplets{{0, 0, {1, 1}}};
  mbasis.setFromTriplets(triplets.begin(), triplets.end());
  mbasis.makeCompressed();
  auto m_data{s_gens.mat_data};
  for (int i{1}; i < s_dim; ++i)
    {
      bool flag{true};
      int k{0};
      do
	{
	  const auto& src = m_data[k];
	  auto iterp{src.find(i)};
	  if (iterp != src.end())
	    {
	      auto j{iterp->second};
	      mbasis.col(i) = s_gens[k+1] * mbasis.col(j);
	      flag = false;
	    }
	  ++k;
	} while(flag); 
    }
  return mbasis;
}

template<typename F, typename T>
inline void iform<F, T>::i_basis()
{
  const auto mbasis{m_basis()};
  T A{T(s_dim, s_dim)};
  std::vector<qtriplet> triplets{};
  for (int i = 0; i < p_classes.num_classes(); ++i)
    {
      for (int j = 0; j < p_classes.class_size(i); ++j)
	{
	  for (int k = 0; k <= j; ++k)
	    {
	      auto row{p_classes.element(i, k)};
	      auto col{p_classes.element(i, j)};
	      triplets.push_back({row, col, {1, 1}});
	    }
	}
    }
  A.setFromTriplets(triplets.begin(), triplets.end());
  A.makeCompressed();
  p_basis = mbasis.cwiseProduct(A);
}

