# bit_knn - bit vector + popcnt k-Nearest Neighbor

## 注意点

SSE4.2が必要です．

## コンパイル
    % cd src && make

## 使い方

    Usage: bit_knn_classify <train filename> <test filename>
         [-k knum] number of neighbors to be used for prediction (Default: 1)
         [-f] using feature vector data structure instead of bit vectors. (Default: OFF)
         [-q] Quiet mode, which does not diplay predict result. (Default: OFF)

## TODO

*  1-NNになっているのでkに変更する

