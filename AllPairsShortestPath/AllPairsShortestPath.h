using namespace std;

#ifndef ALGORITHMS_ALLPAIRSSHORTESTPATH_H
#define ALGORITHMS_ALLPAIRSSHORTESTPATH_H

class AllPairsShortestPath {
    private:
        struct compare;
        static pair<int, int> parseInput(const string&);
        static vector<string> parseGraph();
    public:
        static int dijkstrasMinHeap(const string&);
        static int dijkstrasArray(const string&);
        static int floydWarshall(const string&);
};

#endif //ALGORITHMS_ALLPAIRSSHORTESTPATH_H
