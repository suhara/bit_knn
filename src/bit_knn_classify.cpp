#include <iostream>
#include <cstdlib>
#include <sys/time.h>

#include "bit_knn.hpp"


double
gettimeofday_sec ()
{
  struct timeval tv;
  gettimeofday( &tv, NULL );
  return tv.tv_sec + tv.tv_usec * 1e-6;
}


void
usage ()
{
  std::cout << std::endl;
  std::cout << "Usage: bit_knn_classify"
            << " <train filename> <test filename>" << std::endl
            << "     [-k knum] number of neighbors to be used for prediction (Default: 1)" << std::endl
            << "     [-f] using feature vector data structure instead of bit vectors. (Default: OFF)" << std::endl
            << "     [-q] Quiet mode, which does not diplay predict result. (Default: OFF)" << std::endl
            << std::endl;
}

int
main (int argc, char *argv[])
{
  int knum        = 1;
  bool fvec_flag  = false;
  bool quiet_mode = false;

  int result;
  while ((result = getopt(argc, argv, "k:fq")) != -1) {
    switch (result) {

    case 'k':
      knum = atoi( optarg );
      break;

    case 'f':
      fvec_flag = true;
      break;

    case 'q':
      quiet_mode = true;
      break;

    }
  }

  argc -= optind;
  argv += optind;

  if (argc < 2) {
    usage();
    exit(1);
  }

  bool bit_flag = true;
  if (fvec_flag) {
    bit_flag = false;
  }

  double t1 = gettimeofday_sec();
  Instances *train_inss = new Instances( argv[ 0 ], bit_flag );
  Instances *test_inss  = new Instances( argv[ 1 ], bit_flag );

  BitKNN *bknn = new BitKNN(train_inss);
  bknn->fvec_flag = fvec_flag;
  double t2 = gettimeofday_sec();

  std::cerr << "Load time: " << (t2 - t1) << " sec." << std::endl;

  double t3 = gettimeofday_sec();
  for (int i = 0; i < (int)test_inss->ins_vec.size(); i++) {
    int pred = bknn->predict( test_inss->ins_vec[ i ] );
    if (! quiet_mode) {
      std::cout << pred << std::endl;
    }
  }
  double t4 = gettimeofday_sec();  

  std::cerr << "Classification time: " << (t4 - t3) << " sec." << std::endl;

  return 0;
}

