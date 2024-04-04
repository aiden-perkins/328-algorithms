using namespace std;

#ifndef ALGORITHMS_CLOSESTPOINTPAIR_H
#define ALGORITHMS_CLOSESTPOINTPAIR_H

class ClosestPointPair {
    private:
        struct Point;
        static double splitAndSolve(Point*, int);
        static bool sortX(const Point&, const Point&);
        static void populatePoints(Point*, int, vector<string>);
        static vector<string> parseInput(const string&);
    public:
        static double divideAndConquer(const string&);
        static double bruteForce(const string&);
};

#endif //ALGORITHMS_CLOSESTPOINTPAIR_H
