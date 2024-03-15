using namespace std;

#ifndef ALGORITHMS_MINIMUMSPANNINGTREES_H
#define ALGORITHMS_MINIMUMSPANNINGTREES_H

class MinimumSpanningTrees {
    private:
        static vector<string> parseInput(const string&);
    public:
        static double prim(const string&);
        static double kruskal(const string&);
};

#endif //ALGORITHMS_MINIMUMSPANNINGTREES_H
