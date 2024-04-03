using namespace std;

#ifndef ALGORITHMS_STRASSENALGORITHM_H
#define ALGORITHMS_STRASSENALGORITHM_H

class StrassenAlgorithm {
    private:
        static vector<string> rawMatrix(const string&);
        static void populateMatrix(int**, int, vector<string>, int);
        static int** runStrassen(int**, int**, int);
        static int matrixSum(int**, int);
        static int** splitAndSolve(int**, int**, int);
        static int** mergeMatrix(int**, int**, int, int = 1);
    public:
        static int strassen(const string&, const string&);
        static int divideAndConquer(const string&, const string&);
        static int bruteForce(const string&, const string&);
};

#endif //ALGORITHMS_STRASSENALGORITHM_H
