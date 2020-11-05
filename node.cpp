#include "node.h"


node::node(int i_val, int j_val) : row_index{i_val}, column_index{j_val}
{
}

node::node(const node& src): row_index{src.row_index}, column_index{src.column_index}
{
}


