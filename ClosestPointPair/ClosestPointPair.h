#include <string>
#include <vector>
using namespace std;

#ifndef INC_328_ALGORITHMS_CLOSESTPOINTPAIR_H
#define INC_328_ALGORITHMS_CLOSESTPOINTPAIR_H

class ClosestPointPair {
    private:
        struct Point;
        static double splitAndSolve(vector<Point>);
        static bool sortY(const Point &, const Point &);
        static bool sortX(const Point &, const Point &);
        static vector<Point> parseInput(const string&);
    public:
        static double divideAndConquer(const string&);
        static double bruteForce(const string&);
};

#endif //INC_328_ALGORITHMS_CLOSESTPOINTPAIR_H
