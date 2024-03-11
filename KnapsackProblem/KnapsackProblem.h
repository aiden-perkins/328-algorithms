using namespace std;

#ifndef ALGORITHMS_KNAPSACKPROBLEM_H
#define ALGORITHMS_KNAPSACKPROBLEM_H

class KnapsackProblem {
    private:
        struct Brick;
        static vector<Brick> parseInput(const string&);
        static int bfRecursion(Brick*, int, int);
        static int dpRecursion(Brick*, int, int, int**);
    public:
        static int dynamicProgrammingRecursion(const string&);
        static int dynamicProgramming(const string&);
        static int bruteForce(const string&);
};

#endif //ALGORITHMS_KNAPSACKPROBLEM_H
