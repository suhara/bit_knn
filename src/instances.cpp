#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "instances.hpp"

void
Instance::parse_line (std::string &line, bool bit_flag)
{
  std::istringstream iss( line );
  if (! (iss >> label) ) {
    std::cerr << "ERROR: Failed to parse label" << std::endl;
    exit(1);
  }

  active_bit_num = 0;

  int fid, fval;
  char sep;

  uint64_t cur_64bit = 0;
  int cur_block_max_fid = 64;
  
  while (iss >> fid >> sep >> fval) {
    active_bit_num++;

    if (bit_flag) {
      // use bit vector
      while (cur_block_max_fid < fid) {
	bit_vec.push_back( cur_64bit );
	cur_block_max_fid += 64;
	cur_64bit = 0;
      }
      int idx = (fid - 1) % 64;
      cur_64bit = (cur_64bit | UINT64_BIT_ARRAY[ idx ]);

    } else {
      // use fvec
      fvec.push_back( fpair_t( fid, fval ) );
    }

  }

  if (bit_flag) {
    bit_vec.push_back( cur_64bit );
  }
}


void
Instance::print_bit_vec ()
{
  std::cout << label << " ";
  for (int i = 0; i < (int)bit_vec.size(); i++) {
    for (int j = 0; j < 64; j++) {
      if ( (bit_vec[ i ] & UINT64_BIT_ARRAY[ j ]) != 0) {
	std::cout << "1";
      } else {
	std::cout << "0";
      }

      if (j > 0 && j % 8 == 0) {
	std::cout << " ";
      }
    }
    std::cout << "  ";
  }
  std::cout << std::endl;
}


void
Instances::load_file (const char *filename, bool bit_flag)
{
  std::ifstream fin( filename );
  if (! fin) {
    std::cerr << "ERROR: Failed to open " << filename << std::endl;
    exit(1);
  }

  std::string buff;
  while (fin && getline( fin, buff )) {
    ins_vec.push_back( Instance( buff, bit_flag ) );
  }
}

void
Instances::print_bit_vecs ()
{
  for (int i = 0; i < (int)ins_vec.size(); i++) {
    ins_vec[ i ].print_bit_vec();
  }
}
