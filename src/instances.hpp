#ifndef __INSTANCES_HPP__
#define __INSTANCES_HPP__

#include <vector>
#include <map>
#include <string>
#include <cstdint>

const uint64_t UINT64_BIT_ARRAY[64] = {1UL,2UL,4UL,8UL,16UL,32UL,64UL,128UL,256UL,512UL,1024UL,2048UL,4096UL,8192UL,16384UL,32768UL,65536UL,131072UL,262144UL,524288UL,1048576UL,2097152UL,4194304UL,8388608UL,16777216UL,33554432UL,67108864UL,134217728UL,268435456UL,536870912UL,1073741824UL,2147483648UL,4294967296UL,8589934592UL,17179869184UL,34359738368UL,68719476736UL,137438953472UL,274877906944UL,549755813888UL,1099511627776UL,2199023255552UL,4398046511104UL,8796093022208UL,17592186044416UL,35184372088832UL,70368744177664UL,140737488355328UL,281474976710656UL,562949953421312UL,1125899906842624UL,2251799813685248UL,4503599627370496UL,9007199254740992UL,18014398509481984UL,36028797018963968UL,72057594037927936UL,144115188075855872UL,288230376151711744UL,576460752303423488UL,1152921504606846976UL,2305843009213693952UL,4611686018427387904UL,9223372036854775808UL};

typedef float fval_t; // Assume binary feature in this case
typedef std::pair<int, fval_t> fpair_t;

class Instance
{
public:

  int label;
  size_t active_bit_num;
  std::vector<uint64_t> bit_vec;
  std::vector<fpair_t> fvec;

  Instance () {}
  Instance (std::string &line, bool bit_flag = false) {
    parse_line( line, bit_flag );
  }

  void parse_line (std::string &line, bool bit_flag = false);
  void print_bit_vec ();
};


class Instances
{
public:
  std::vector<Instance> ins_vec;

  Instances (const char *filename, bool bit_flag = false) {
    load_file( filename, bit_flag );
  }

  Instance &get (int i) {
    if (i >= (int)ins_vec.size()) {
      std::cerr << "ERROR: ins_vec() is out of bounds." << std::endl;
      exit(1);
    }
    return ins_vec[ i ];
  }

  size_t size () { return ins_vec.size(); }
  void load_file(const char *filename, bool bit_flag = false);
  void print_bit_vecs ();
};

#endif
