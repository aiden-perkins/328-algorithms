#include <string>
using namespace std;

#ifndef ALGORITHMS_STRASSENALGORITHM_H
#define ALGORITHMS_STRASSENALGORITHM_H

class StrassenAlgorithm {
    private:
        static vector<vector<int>> parseInput(const string&);
        static vector<vector<int>> runStrassen(vector<vector<int>>, vector<vector<int>>);
        static vector<vector<int>> splitAndSolve(vector<vector<int>>, vector<vector<int>>);
        static vector<vector<int>> addMatrix(vector<vector<int>>, vector<vector<int>>);
        static vector<vector<int>> subtractMatrix(vector<vector<int>>, vector<vector<int>>);
        static vector<vector<vector<int>>> divideMatrix(vector<vector<int>>);
        static vector<vector<int>> combineMatrix(vector<vector<int>>, vector<vector<int>>, vector<vector<int>>, vector<vector<int>>);
    public:
        static double strassen(const string&, const string&);
        static double divideAndConquer(const string&, const string&);
        static double bruteForce(const string&, const string&);
};

#endif //ALGORITHMS_STRASSENALGORITHM_H
