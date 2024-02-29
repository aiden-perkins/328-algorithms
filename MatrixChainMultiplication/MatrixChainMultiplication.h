#include <vector>
#include <string>
using namespace std;

#ifndef ALGORITHMS_MATRIXCHAINMULTIPLICATION_H
#define ALGORITHMS_MATRIXCHAINMULTIPLICATION_H

class MatrixChainMultiplication {
    private:
        static vector<int> parseInput(const string&);
        static int bfRecursion();
        static int dpRecursion();
    public:
        static int bruteForce(const string&);
        static int dynamicProgrammingRecursion(const string&);
        static int dynamicProgramming(const string&);
};

#endif //ALGORITHMS_MATRIXCHAINMULTIPLICATION_H
