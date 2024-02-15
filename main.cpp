#include <iostream>
#include <cmath>
#include <functional>
#include <map>
#include <algorithm>
#include "MaxContiguousSubsequence/MaxContiguousSubsequence.h"
#include "ClosestPointPair/ClosestPointPair.h"
#include "StrassenAlgorithm/StrassenAlgorithm.h"
using namespace std;

void display(double answer) {
    cout << round(answer * 1000) / 1000 << endl;
}

int main(int argc, char *argv[]) {
    map<string, function<double(string)>> singleFileInput = {
        {"ClosestPointPairbrute_force", &ClosestPointPair::bruteForce},
        {"ClosestPointPairdivide_and_conquer", &ClosestPointPair::divideAndConquer},
        {"ClosestPointPairfastest", &ClosestPointPair::divideAndConquer},
        {"MaxContiguousSubsequencebrute_force", &MaxContiguousSubsequence::bruteForce},
        {"MaxContiguousSubsequencedivide_and_conquer", &MaxContiguousSubsequence::divideAndConquer},
        {"MaxContiguousSubsequencekadane", &MaxContiguousSubsequence::kadane},
        {"MaxContiguousSubsequencefastest", &MaxContiguousSubsequence::kadane},
    };
    map<string, function<double(string, string)>> multiFileInputAlgorithms = {
        {"StrassenAlgorithmbrute_force", &StrassenAlgorithm::bruteForce},
        {"StrassenAlgorithmstrassen", &StrassenAlgorithm::strassen},
        {"StrassenAlgorithmfastest", &StrassenAlgorithm::strassen},
        {"StrassenAlgorithmdivide_and_conquer", &StrassenAlgorithm::divideAndConquer},
    };
    vector<string> multiFileInput = {"StrassenAlgorithm"};

    if (argc == 2) {
        // Best method, all test cases
        for (int i = 0; i < 11; i++) {
            if (find(multiFileInput.begin(), multiFileInput.end(), (string) argv[1]) != multiFileInput.end()) {
                string path1 = "../" + (string) argv[1] + "/tests/" + to_string(i) + "a.txt";
                string path2 = "../" + (string) argv[1] + "/tests/" + to_string(i) + "b.txt";
                display(multiFileInputAlgorithms[(string) argv[1] + "fastest"](path1, path2));
            } else {
                string path = "../" + (string) argv[1] + "/tests/" + to_string(i) + ".txt";
                display(singleFileInput[(string) argv[1] + "fastest"](path));
            }
        }
    } else if (argc == 3) {
        // Given method, all test cases
        for (int i = 0; i < 11; i++) {
            if (find(multiFileInput.begin(), multiFileInput.end(), (string) argv[1]) != multiFileInput.end()) {
                string path1 = "../" + (string) argv[1] + "/tests/" + to_string(i) + "a.txt";
                string path2 = "../" + (string) argv[1] + "/tests/" + to_string(i) + "b.txt";
                display(multiFileInputAlgorithms[(string) argv[1] + (string) argv[2]](path1, path2));
            } else {
                string path = "../" + (string) argv[1] + "/tests/" + to_string(i) + ".txt";
                display(singleFileInput[(string) argv[1] + (string) argv[2]](path));
            }
        }
    } else if (argc == 4) {
        // Given method, given test case
        if (find(multiFileInput.begin(), multiFileInput.end(), (string) argv[1]) != multiFileInput.end()) {
            string path1 = "../" + (string) argv[1] + "/tests/" + (string) argv[3] + "a.txt";
            string path2 = "../" + (string) argv[1] + "/tests/" + (string) argv[3] + "b.txt";
            display(multiFileInputAlgorithms[(string) argv[1] + (string) argv[2]](path1, path2));
        } else {
            string path = "../" + (string) argv[1] + "/tests/" + (string) argv[3] + ".txt";
            display(singleFileInput[(string) argv[1] + (string) argv[2]](path));
        }
    } else {
        cout << "Did not provide the correct parameters, exiting." << endl;
    }
    return 0;
}