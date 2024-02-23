#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "DeterministicOrderSelection.h"
using namespace std;

int* DeterministicOrderSelection::parseInput(const string& filePath) {
    int count = 0;
    ifstream file(filePath);
    string input;
    vector<string> inputVector;
    if (file.is_open()) {
        while (getline(file, input, ' ')) {
            if (!input.empty()) {
                count++;
                inputVector.push_back(input);
            }
        }
        file.close();
    }
    int nums[count];
    for (int i = 0; i < count; i++) {
        if (i < 2) {
            nums[i] = stoi(inputVector[i].substr(1));
        } else {
            nums[i] = stoi(inputVector[i]);
        }
    }
    return nums;
}

int DeterministicOrderSelection::partition(vector<int> nums, int left, int right) {
    return 0;
}

int DeterministicOrderSelection::medianOfMedians(const string& filePath) {
    return 0;
}

int DeterministicOrderSelection::bruteForce(const string& filePath) {
    return 0;
}

int DeterministicOrderSelection::quickSelectRecursion(vector<int> nums, int k) {
    return 0;
}

int DeterministicOrderSelection::quickSelect(const string& filePath) {
    return 0;
}

int DeterministicOrderSelection::builtInSort(const string& filePath) {
    int* numsAndK = parseInput(filePath);
//    vector<vector<int>> numsAndK = parseInput(filePath);
//    vector<int> nums = numsAndK[0];
//    int k = numsAndK[1][0] - 1;
//    sort(nums.begin(), nums.end());
//    return nums[k];
    return 0;
}

