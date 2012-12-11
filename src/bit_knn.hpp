#ifndef __BIT_KNN_HPP__
#define __BIT_KNN_HPP__

#include <cstdint>
#include <vector>
#include "instances.hpp"

class BitKNN
{
public:
  Instances *instances;
  bool fvec_flag;

  BitKNN (Instances *inss) : fvec_flag( false ) {
    instances = inss;
  }

  size_t popcount (std::vector<uint64_t> &x_vec);
  size_t inner_prod (std::vector<uint64_t> &x_vec1, std::vector<uint64_t> &x_vec2);
  size_t inner_prod_fvec (std::vector<fpair_t> &fvec1, std::vector<fpair_t> &fvec2);

  int predict (Instance &ins);
};


#endif
