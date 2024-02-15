#include <string>
#include <vector>
using namespace std;

#ifndef ALGORITHMS_MAXCONTIGUOUSSUBSEQUENCE_H
#define ALGORITHMS_MAXCONTIGUOUSSUBSEQUENCE_H

class MaxContiguousSubsequence {
    private:
        static vector<int> parseInput(const string&);
        static int splitAndSolve(vector<int>);
        static int solveMiddle(vector<int>, int);
    public:
        static int kadane(const string&);
        static int divideAndConquer(const string&);
        static int bruteForce(const string&);
};

#endif //ALGORITHMS_MAXCONTIGUOUSSUBSEQUENCE_H
