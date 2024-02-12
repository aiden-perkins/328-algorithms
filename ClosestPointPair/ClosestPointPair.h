#include <string>
#include <vector>
using namespace std;

#ifndef INC_328_ALGORITHMS_CLOSESTPOINTPAIR_H
#define INC_328_ALGORITHMS_CLOSESTPOINTPAIR_H

class ClosestPointPair {
    private:
        static double splitAndSolve(vector<pair<double, double>>);
        static bool sortSecond(const pair<double, double> &, const pair<double, double> &);
        static vector<pair<double, double>> parseInput(const string&);
    public:
        static double divideAndConquer(const string&);
        static double bruteForce(const string&);
};

#endif //INC_328_ALGORITHMS_CLOSESTPOINTPAIR_H
