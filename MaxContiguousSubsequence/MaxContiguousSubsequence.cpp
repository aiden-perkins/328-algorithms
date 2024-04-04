#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "MaxContiguousSubsequence.h"

using namespace std;

vector<int> MaxContiguousSubsequence::parseInput(const string &filePath) {
    vector<int> nums;
    ifstream file(filePath);
    string input;
    while (getline(file, input, ',')) {
        nums.push_back(stoi(input.substr(1)));
    }
    return nums;
}

int MaxContiguousSubsequence::kadane(const string &filePath) {
    ifstream file(filePath);
    string input;
    int currentSum = 0;
    int maxContigSubseq = 0;
    while (getline(file, input, ',')) {
        int v = stoi(input.substr(1));
        currentSum = max(v, currentSum + v);
        if (currentSum > maxContigSubseq) {
            maxContigSubseq = currentSum;
        }
    }
    return maxContigSubseq;
}

int MaxContiguousSubsequence::splitAndSolve(int* nums, int numsCount) {
    if (numsCount == 1) {
        return nums[0];
    }
    int middle = numsCount / 2;
    int* left = nums;
    int* right = nums + middle;
    return max(max(splitAndSolve(left, middle), splitAndSolve(right, middle)), solveMiddle(nums, numsCount, middle));
}

int MaxContiguousSubsequence::solveMiddle(int* nums, int numsCount, int middle) {
    int currentSum = 0;
    int rightMaxSubseq = min_element(nums, nums + numsCount)[0];
    for (int i = middle; i < numsCount; ++i) {
        currentSum += nums[i];
        if (rightMaxSubseq < currentSum) {
            rightMaxSubseq = currentSum;
        }
    }
    currentSum = 0;
    int leftMaxSubseq = min_element(nums, nums + numsCount)[0];
    for (int i = middle; i > -1; --i) {
        currentSum += nums[i];
        if (leftMaxSubseq < currentSum) {
            leftMaxSubseq = currentSum;
        }
    }
    return max(max(leftMaxSubseq, rightMaxSubseq), leftMaxSubseq + rightMaxSubseq - nums[middle]);
}

int MaxContiguousSubsequence::divideAndConquer(const string &filePath) {
    vector<int> numsInput = parseInput(filePath);
    int numsCount = int(numsInput.size());
    int nums[numsCount];
    for (int i = 0; i < numsCount; ++i) {
        nums[i] = numsInput[i];
    }
    return splitAndSolve(nums, numsCount);
}

int MaxContiguousSubsequence::bruteForce(const string &filePath) {
    vector<int> numsInput = parseInput(filePath);
    int numsCount = int(numsInput.size());
    int nums[numsCount];
    for (int i = 0; i < numsCount; ++i) {
        nums[i] = numsInput[i];
    }
    int maxContigSubseq = 0;
    for (int i = 0; i < numsCount; i++) {
        for (int j = i + 1; j <= numsCount; j++) {
            int currentSum = 0;
            for (int k = i; k < j; ++k) {
                currentSum += nums[k];
            }
            if (currentSum > maxContigSubseq) {
                maxContigSubseq = currentSum;
            }
        }
    }
    return maxContigSubseq;
}
