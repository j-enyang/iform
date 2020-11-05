#pragma once
#include <algorithm>
#include <iostream>
#include <sstream>

class node
{
public:
  node() = default;

  node(int i_val,int j_val);  

  node(const node&);     	               	

  node(node&&) = default;                       
  
  node& operator=(node&&) = default;            
  
  node& operator=(const node&) = default;	

  bool operator==(const node& other) const
  {
    return column_index == other.column_index && row_index == other.row_index;
  }
  bool operator!=(const node& other) const
  {
    return !(*this == other);
  }

  inline bool row_eq(const node& other) const
  {
    return row_index == other.row_index;
  }

  inline bool column_eq(const node& other) const
  {
    return column_index == other.column_index;
  }
  
  inline bool operator>(const node& other) const
  {
    return (row_index < other.row_index);
  }
  
  inline bool operator<(const node& other) const
  {
     return (row_index > other.row_index);
  }
  
  inline int content() const 
  {
    return column_index - row_index;
  }
  
  inline int row() const
  {
    return row_index;
  }
  
  inline int column() const 
  {
    return column_index;
  }
    
  ~node() = default;

private:
	
  int row_index;
  int column_index;

};

