#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include "MinimumSpanningTrees.h"

using namespace std;

vector<string> MinimumSpanningTrees::parseInput(const string &filePath) {
    vector<string> edgeStrings;
    ifstream file(filePath);
    string input;
    if (file.is_open()) {
        while (getline(file, input, '{')) {
            if (input.length() > 3) {
                edgeStrings.push_back(input.substr(0, input.length() - 2));
            }
        }
        file.close();
    }
    return edgeStrings;
}

double MinimumSpanningTrees::prim(const string &filePath) {
    vector<string> edgeStrings = parseInput(filePath);
    for (string v: edgeStrings) {
        cout << v << endl;
    }
    return 0;
}

double MinimumSpanningTrees::kruskal(const string &filePath) {
    return 0;
}
