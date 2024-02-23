#include <vector>
#include <string>
using namespace std;

#ifndef ALGORITHMS_DETERMINISTICORDERSELECTION_H
#define ALGORITHMS_DETERMINISTICORDERSELECTION_H

class DeterministicOrderSelection {
    private:
        static int* parseInput(const string&);
        static int partition(vector<int>, int, int);
        static int quickSelectRecursion(vector<int>, int);
    public:
        static int medianOfMedians(const string&);
        static int bruteForce(const string&);
        static int quickSelect(const string&);
        static int builtInSort(const string&);
};

#endif //ALGORITHMS_DETERMINISTICORDERSELECTION_H
