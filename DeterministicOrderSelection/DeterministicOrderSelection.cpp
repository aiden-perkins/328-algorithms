#include <fstream>
#include <iostream>
#include <algorithm>
#include "DeterministicOrderSelection.h"
using namespace std;

vector<string> DeterministicOrderSelection::parseInput(const string& filePath) {
    ifstream file(filePath);
    string input;
    vector<string> inputVector;
    if (file.is_open()) {
        while (getline(file, input, ' ')) {
            if (!input.empty()) {
                inputVector.push_back(input);
            }
        }
        file.close();
    }
    swap(inputVector.front(), inputVector.back());
    swap(inputVector.front(), inputVector[1]);
    return inputVector;
}

int DeterministicOrderSelection::partition(int* nums, int left, int right) {
    int pivotValue = nums[right - 1];
    int swapIndex = left;
    for (int i = left; i < right - 1; i++) {
        if (nums[i] <= pivotValue) {
            swap(nums[swapIndex], nums[i]);
            swapIndex++;
        }
    }
    swap(nums[swapIndex], nums[right - 1]);
    return swapIndex;
}

int DeterministicOrderSelection::select(int* nums, int numsSize, int k) {
    if (numsSize <= 100) {
        sort(nums, nums + numsSize);
        return nums[k - 1];
    }
    vector<int> medians;
    for (int i = 0; i < ((numsSize - 1) / 5) + 1; i++) {
        // TODO
    }
}

int DeterministicOrderSelection::medianOfMedians(const string& filePath) {
    // TODO
    return 0;
}

void DeterministicOrderSelection::quickSort(int* nums, int left, int right) {
    if (right - left <= 1) {
        return;
    }
    int pivot = partition(nums, left, right);
    quickSort(nums, left, pivot);
    quickSort(nums, pivot + 1, right);
}

int DeterministicOrderSelection::bruteForce(const string& filePath) {
    vector<string> input = parseInput(filePath);
    int numsSize = int(input.size()) - 1;
    int* nums = new int[numsSize];
    int k = stoi(input[numsSize].substr(1)) - 1;
    for (int i = 0; i < numsSize; i++) {
        if (i < 1) {
            nums[i] = stoi(input[i].substr(1));
        } else {
            nums[i] = stoi(input[i]);
        }
    }
    quickSort(nums, 0, numsSize);
    int ans = nums[k];
    delete[] nums;
    return ans;
}

int DeterministicOrderSelection::quickSelectRecursion(int* nums, int numsSize, int k) {
    if (numsSize == 1) {
        return nums[0];
    }
    int pivot = partition(nums, 0, numsSize);
    if (pivot == k) {
        return nums[k];
    } else if (k < pivot) {
        // TODO
        return quickSelectRecursion();
    } else if (k > pivot) {
        // TODO
        return quickSelectRecursion();
    }
}

int DeterministicOrderSelection::quickSelect(const string& filePath) {
    vector<string> input = parseInput(filePath);
    int numsSize = int(input.size()) - 1;
    int* nums = new int[numsSize];
    int k = stoi(input[numsSize].substr(1));
    for (int i = 0; i < numsSize; i++) {
        if (i < 1) {
            nums[i] = stoi(input[i].substr(1));
        } else {
            nums[i] = stoi(input[i]);
        }
    }
    int ans = quickSelectRecursion(nums, numsSize, k);
    delete[] nums;
    return ans;
}

int DeterministicOrderSelection::builtInSort(const string& filePath) {
    vector<string> input = parseInput(filePath);
    int numsSize = int(input.size()) - 1;
    int* nums = new int[numsSize];
    int k = stoi(input[numsSize].substr(1)) - 1;
    for (int i = 0; i < numsSize; i++) {
        if (i < 1) {
            nums[i] = stoi(input[i].substr(1));
        } else {
            nums[i] = stoi(input[i]);
        }
    }
    sort(nums, nums + numsSize);
    int ans = nums[k];
    delete[] nums;
    return ans;
}

