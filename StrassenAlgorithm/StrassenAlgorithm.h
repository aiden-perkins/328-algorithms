using namespace std;

#ifndef ALGORITHMS_STRASSENALGORITHM_H
#define ALGORITHMS_STRASSENALGORITHM_H

class StrassenAlgorithm {
    private:
        static vector<vector<int>> parseInput(const string&);
        static vector<string> rawMatrix(const string&);
        static void populateMatrix(int**, int, vector<string>, int);
        static int** runStrassenV2(int**, int**, int);
        static int matrixSum(int**, int);
        static vector<vector<int>> runStrassen(vector<vector<int>>, vector<vector<int>>, int);
        static vector<vector<int>> splitAndSolve(vector<vector<int>>, vector<vector<int>>, int);
        static vector<vector<int>> mergeMatrix(vector<vector<int>>, vector<vector<int>>, int, int);
    public:
        static int strassen(const string&, const string&);
        static int strassenV2(const string&, const string&);
        static int divideAndConquer(const string&, const string&);
        static int bruteForce(const string&, const string&);
};

#endif //ALGORITHMS_STRASSENALGORITHM_H
