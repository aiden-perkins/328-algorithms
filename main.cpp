#include <iostream>
#include <cmath>
#include "ClosestPointPair/ClosestPointPair.h"
#include "StrassenAlgorithm/StrassenAlgorithm.h"
using namespace std;

void display(double answer) {
    cout << round(answer * 1000) / 1000 << endl;
}

int main(int argc, char *argv[]) {
    cout << argc << argv << endl;
    // TODO: Make arguments do similar thing to python main.py, not as complicated just so it works.
    // Currently it is just running the 4th test on the things I have made in c++.
    double a1 = ClosestPointPair::bruteForce("../ClosestPointPair/tests/4.txt");
    display(a1);
    double a2 = ClosestPointPair::divideAndConquer("../ClosestPointPair/tests/4.txt");
    display(a2);
    double a3 = StrassenAlgorithm::bruteForce("../StrassenAlgorithm/tests/5a.txt", "../StrassenAlgorithm/tests/5b.txt");
    display(a3);
    double a4 = StrassenAlgorithm::divideAndConquer("../StrassenAlgorithm/tests/4a.txt", "../StrassenAlgorithm/tests/4b.txt");
    display(a4);
    double a5 = StrassenAlgorithm::strassen("../StrassenAlgorithm/tests/4a.txt", "../StrassenAlgorithm/tests/4b.txt");
    display(a5);
    // Can't get any of the optimized strassen to run past test case 4.
    return 0;
}