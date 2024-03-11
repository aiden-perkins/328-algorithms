using namespace std;

#ifndef ALGORITHMS_DETERMINISTICORDERSELECTION_H
#define ALGORITHMS_DETERMINISTICORDERSELECTION_H

class DeterministicOrderSelection {
    private:
        static vector<string> parseInput(const string&);
        static int partition(int*, int, int);
        static int quickSelectRecursion(int*, int, int);
        static void quickSort(int*, int, int);
        static int select(int*, int, int);
    public:
        static int medianOfMedians(const string&);
        static int bruteForce(const string&);
        static int quickSelect(const string&);
        static int builtInSort(const string&);
};

#endif //ALGORITHMS_DETERMINISTICORDERSELECTION_H
