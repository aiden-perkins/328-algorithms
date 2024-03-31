using namespace std;

#ifndef ALGORITHMS_MINIMUMSPANNINGTREES_H
#define ALGORITHMS_MINIMUMSPANNINGTREES_H

class MinimumSpanningTrees {
    private:
        struct Node;
        struct Edge;
        static int kFind(int*, int);
        static void kUnion(int*, int*, int, int);
        static vector<string> parseInput(const string&);
    public:
        static double primMinHeap(const string&);
        static double primArray(const string&);
        static double kruskal(const string&);
};

#endif //ALGORITHMS_MINIMUMSPANNINGTREES_H
