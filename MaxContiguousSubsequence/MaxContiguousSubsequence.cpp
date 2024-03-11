#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include <algorithm>
#include "MaxContiguousSubsequence.h"

using namespace std;

vector<int> MaxContiguousSubsequence::parseInput(const string &filePath) {
    vector<int> nums;
    ifstream file(filePath);
    string input;
    if (file.is_open()) {
        while (getline(file, input, ',')) {
            nums.push_back(stoi(input.substr(1)));
        }
        file.close();
    }
    return nums;
}

int MaxContiguousSubsequence::kadane(const string &filePath) {
    vector<int> nums = parseInput(filePath);
    int currentSum = 0;
    int maxContigSubseq = nums[0];
    for (int num: nums) {
        currentSum = max(num, currentSum + num);
        if (currentSum > maxContigSubseq) {
            maxContigSubseq = currentSum;
        }
    }
    return maxContigSubseq;
}

int MaxContiguousSubsequence::splitAndSolve(vector<int> nums) {
    if (nums.size() == 1) {
        return nums[0];
    }
    int middle = int(nums.size() / 2);
    vector<int> left(nums.begin(), nums.begin() + middle);
    vector<int> right(nums.begin() + middle, nums.end());
    return max(max(splitAndSolve(left), splitAndSolve(right)), solveMiddle(nums, middle));
}

int MaxContiguousSubsequence::solveMiddle(vector<int> nums, int middle) {
    int currentSum = 0;
    int rightMaxSubseq = min_element(nums.begin(), nums.end())[0];
    for (int num: vector<int>(nums.begin() + middle, nums.end())) {
        currentSum += num;
        if (rightMaxSubseq < currentSum) {
            rightMaxSubseq = currentSum;
        }
    }
    currentSum = 0;
    int leftMaxSubseq = min_element(nums.begin(), nums.end())[0];
    vector<int> left(nums.begin(), nums.begin() + middle + 1);
    for (int num: vector<int>(left.rbegin(), left.rend())) {
        currentSum += num;
        if (leftMaxSubseq < currentSum) {
            leftMaxSubseq = currentSum;
        }
    }
    return max(max(leftMaxSubseq, rightMaxSubseq), leftMaxSubseq + rightMaxSubseq - nums[middle]);
}

int MaxContiguousSubsequence::divideAndConquer(const string &filePath) {
    vector<int> nums = parseInput(filePath);
    return splitAndSolve(nums);
}

int MaxContiguousSubsequence::bruteForce(const string &filePath) {
    vector<int> nums = parseInput(filePath);
    int maxContigSubseq = 0;
    int numsSize = int(nums.size());
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j <= numsSize; j++) {
            int currentSum = accumulate(nums.begin() + i, nums.begin() + j, 0);
            if (currentSum > maxContigSubseq) {
                maxContigSubseq = currentSum;
            }
        }
    }
    return maxContigSubseq;
}
