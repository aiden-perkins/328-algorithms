#include <vector>
#include <string>
using namespace std;

#ifndef ALGORITHMS_MATRIXCHAINMULTIPLICATION_H
#define ALGORITHMS_MATRIXCHAINMULTIPLICATION_H

class MatrixChainMultiplication {
    private:
        struct MatrixSize;
        static vector<MatrixSize> parseInput(const string&);
        static int bfRecursion(MatrixSize*, int, int);
        static int dpRecursion(MatrixSize*, int, int, int**);
    public:
        static int bruteForce(const string&);
        static int dynamicProgrammingRecursion(const string&);
        static int dynamicProgramming(const string&);
};

#endif //ALGORITHMS_MATRIXCHAINMULTIPLICATION_H
