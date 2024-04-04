#include <iostream>
#include <cmath>
#include <functional>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include "ClosestPointPair/ClosestPointPair.h"
#include "StrassenAlgorithm/StrassenAlgorithm.h"
#include "MaxContiguousSubsequence/MaxContiguousSubsequence.h"
#include "DeterministicOrderSelection/DeterministicOrderSelection.h"
#include "KnapsackProblem/KnapsackProblem.h"
#include "MatrixChainMultiplication/MatrixChainMultiplication.h"
#include "AllPairsShortestPath/AllPairsShortestPath.h"
#include "MinimumSpanningTrees/MinimumSpanningTrees.h"
#include "HuffmanEncoding/HuffmanEncoding.h"

using namespace std;

void display(double answer) {
    cout << fixed;
    cout << round(answer * 10000) / 10000 << endl;
}

int main(int argc, char* argv[]) {
    map<string, function<double(string)>> singleFileInput = {
        {"ClosestPointPairbrute_force", &ClosestPointPair::bruteForce},
        {"ClosestPointPairdivide_and_conquer", &ClosestPointPair::divideAndConquer},
        {"ClosestPointPairfastest", &ClosestPointPair::divideAndConquer},
        {"MaxContiguousSubsequencebrute_force", &MaxContiguousSubsequence::bruteForce},
        {"MaxContiguousSubsequencedivide_and_conquer", &MaxContiguousSubsequence::divideAndConquer},
        {"MaxContiguousSubsequencekadane", &MaxContiguousSubsequence::kadane},
        {"MaxContiguousSubsequencefastest", &MaxContiguousSubsequence::kadane},
        {"DeterministicOrderSelectionbrute_force", &DeterministicOrderSelection::bruteForce},
        {"DeterministicOrderSelectionbuilt_in_sort", &DeterministicOrderSelection::builtInSort},
        {"DeterministicOrderSelectionfastest", &DeterministicOrderSelection::quickSelect},
        {"DeterministicOrderSelectionmedian_of_medians", &DeterministicOrderSelection::medianOfMedians},
        {"DeterministicOrderSelectionquick_select", &DeterministicOrderSelection::quickSelect},
        {"KnapsackProblembrute_force", &KnapsackProblem::bruteForce},
        {"KnapsackProblemdynamic_programming_recursion", &KnapsackProblem::dynamicProgrammingRecursion},
        {"KnapsackProblemdynamic_programming", &KnapsackProblem::dynamicProgramming},
        {"KnapsackProblemfastest", &KnapsackProblem::dynamicProgramming},
        {"MatrixChainMultiplicationbrute_force", &MatrixChainMultiplication::bruteForce},
        {
            "MatrixChainMultiplicationdynamic_programming_recursion",
            &MatrixChainMultiplication::dynamicProgrammingRecursion
        },
        {"MatrixChainMultiplicationdynamic_programming", &MatrixChainMultiplication::dynamicProgramming},
        {"MatrixChainMultiplicationfastest", &MatrixChainMultiplication::dynamicProgramming},
        {"AllPairsShortestPathfastest", &AllPairsShortestPath::dijkstrasArray},
        {"AllPairsShortestPathdijkstras_min_heap", &AllPairsShortestPath::dijkstrasMinHeap},
        {"AllPairsShortestPathdijkstras_array", &AllPairsShortestPath::dijkstrasArray},
        {"AllPairsShortestPathfloyd_warshall", &AllPairsShortestPath::floydWarshall},
        {"MinimumSpanningTreesfastest", &MinimumSpanningTrees::kruskal},
        {"MinimumSpanningTreesprim_min_heap", &MinimumSpanningTrees::primMinHeap},
        {"MinimumSpanningTreesprim_array", &MinimumSpanningTrees::primArray},
        {"MinimumSpanningTreeskruskal", &MinimumSpanningTrees::kruskal},
        {"HuffmanEncodingfastest", &HuffmanEncoding::huffman},
        {"HuffmanEncodinghuffman", &HuffmanEncoding::huffman},
    };
    map<string, function<double(string, string)>> multiFileInput = {
        {"StrassenAlgorithmbrute_force", &StrassenAlgorithm::bruteForce},
        {"StrassenAlgorithmstrassen", &StrassenAlgorithm::strassen},
        {"StrassenAlgorithmfastest", &StrassenAlgorithm::strassen},
        {"StrassenAlgorithmdivide_and_conquer", &StrassenAlgorithm::divideAndConquer},
    };
    vector<string> multiFileList = {"StrassenAlgorithm"};

    if ((string) argv[1] == "strassen_sub_one_second") {
        cout << "One second strassen is in progress" << endl;
        return 0;
    } else if ((string) argv[1] == "time") {
        // Check if there is a specific algorithm in the arguments
        // Check if there is a specific method in the arguments
        // Check if there is a specific test case in the arguments
        // Run the algorithm with the specific method on the specific test case either 1000 times or for 1 hour whatever
        // happens first.
        // This should eventually replace the rest of the code, so you shouldn't need to put 'test' as an argument but
        // as it's a WIP for now right here is fine.
        cout << "Time is in progress" << endl;
        return 0;
    }
    vector<double> answers;
    ifstream ansFile("./" + (string) argv[1] + "/ans.txt");
    string ansLine;
    if (ansFile.is_open()) {
        while (getline(ansFile, ansLine)) {
            answers.push_back(stod(ansLine));
        }
    }
    bool multiFile = find(multiFileList.begin(), multiFileList.end(), (string) argv[1]) != multiFileList.end();
    string method = "fastest";
    int firstTest = 0;
    int lastTest = 10;
    if (argc >= 3) {
        method = argv[2];
        if (argc >= 4) {
            firstTest = stoi(argv[3]);
            lastTest = stoi(argv[3]);
        }
    }
    for (int i = firstTest; i < lastTest + 1; i++) {
        double ans;
        if (multiFile) {
            string path1 = "./" + (string) argv[1] + "/tests/" + to_string(i) + "a.txt";
            string path2 = "./" + (string) argv[1] + "/tests/" + to_string(i) + "b.txt";
            ans = multiFileInput[(string) argv[1] + method](path1, path2);
        } else {
            string path = "./" + (string) argv[1] + "/tests/" + to_string(i) + ".txt";
            ans = singleFileInput[(string) argv[1] + method](path);
        }
        if (ans != answers[i]) {
            cout << "WRONG ANSWER" << endl;
        }
        display(ans);
    }
    return 0;
}
