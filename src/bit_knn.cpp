#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <smmintrin.h>

#include "bit_knn.hpp"

size_t
BitKNN::popcount (std::vector<uint64_t> &x_vec)
{
  size_t c = 0;
  for (int i = 0; i < (int)x_vec.size(); i++) {
    c += _mm_popcnt_u64( x_vec[ i ] );
  }
  return c;
}


size_t
BitKNN::inner_prod (std::vector<uint64_t> &x_vec1, std::vector<uint64_t> &x_vec2)
{
  /*
  if (x_vec1.size() != x_vec2.size()) {
    std::cerr << "ERROR: The size of two vectors are inconsistent." << std::endl;
    exit(1);
  }
  */

  size_t c = 0;
  for (int i = 0; i < (int)x_vec1.size(); i++) {
    uint64_t x = x_vec1[ i ] & x_vec2[ i ];
    c += _mm_popcnt_u64( x );
  }
  return c;
}


size_t
BitKNN::inner_prod_fvec (std::vector<fpair_t> &fvec1, std::vector<fpair_t> &fvec2)
{
  int cur_idx1 = 0;
  int cur_idx2 = 0;

  size_t sum = 0;

  while (cur_idx1 < (int)fvec1.size() &&
	 cur_idx2 < (int)fvec2.size()) {
    if (fvec1[ cur_idx1 ].first < fvec2[ cur_idx2 ].first) {
      cur_idx1++;
    } else if (fvec1[ cur_idx1 ].first > fvec2[ cur_idx2 ].first) {
      cur_idx2++;
    } else {
      sum++;
      cur_idx1++;
      cur_idx2++;
    }
  }

  return sum;
}


int
BitKNN::predict (Instance &ins)
{
  // 1-NN
  int cur_label = 0;
  size_t cur_max_value = 0;
  
  for (int i = 0; i < (int)instances->size(); i++) {
    Instance &cur_ins = instances->get( i );

    if (cur_ins.active_bit_num > cur_max_value) {
      size_t cur_value;

      if (fvec_flag) {
	cur_value = inner_prod_fvec( ins.fvec, cur_ins.fvec );
      } else {
	cur_value = inner_prod( ins.bit_vec, cur_ins.bit_vec );
      }

      // DEBUG
      // std::cout << cur_value << std::endl;

      if (cur_value > cur_max_value) {
	cur_max_value = cur_value;
	cur_label = cur_ins.label;
      }
    } else {
      // Ignore
      // std::cout << "ignore" << std::endl;
    }
  }

  return cur_label;
}


// int
// main (int argc, char *argv[])
// {
//   std::vector<uint64_t> x_vec1;
//   std::vector<uint64_t> x_vec2;
// 
//   x_vec1.push_back( (uint64_t) 1 );
//   x_vec1.push_back( (uint64_t) 1 );
// 
//   x_vec2.push_back( (uint64_t) 1 );
//   x_vec2.push_back( (uint64_t) 2 );
// 
//   std::cout << popcount( x_vec1 ) << std::endl;
//   std::cout << inner_prod( x_vec1, x_vec2 ) << std::endl;
// 
//   return 0;
// }
