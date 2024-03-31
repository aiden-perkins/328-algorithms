using namespace std;

#ifndef ALGORITHMS_MINIMUMSPANNINGTREES_H
#define ALGORITHMS_MINIMUMSPANNINGTREES_H

class MinimumSpanningTrees {
    private:
        struct Node;
        static vector<string> parseInput(const string&);
    public:
        static double primMinHeap(const string&);
        static double primArray(const string&);
        static double kruskal(const string&);
};

#endif //ALGORITHMS_MINIMUMSPANNINGTREES_H
