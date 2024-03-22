#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <algorithm>
#include "HuffmanEncoding.h"

using namespace std;

int HuffmanEncoding::huffman(const string &filePath) {
    ifstream file(filePath);
    file.seekg(0, ios::end);
    streamsize charCount = file.tellg();
    file.seekg(0, ios::beg);
    char letters[charCount];
    file.read(letters, charCount);
    int frequencies[26];
    for (int &i: frequencies) {
        i = 0;
    }
    for (int i = 0; i < charCount; i++) {
        frequencies[int(letters[i]) - 97]++;
    }
    int uniqueCharCount = 0;
    char uniqueChars[26];
    for (int i = 0; i < 26; i++) {
        if (frequencies[i]) {
            uniqueChars[uniqueCharCount] = char(i + 97);
            uniqueCharCount++;
        }
    }
    int weightNodes[uniqueCharCount];
    string strNodes[uniqueCharCount];
    for (int i = 0; i < uniqueCharCount; i++) {
        weightNodes[i] = frequencies[int(uniqueChars[i]) - 97];
        strNodes[i] = uniqueChars[i];
    }
    sort(&weightNodes[0], &weightNodes[0] + uniqueCharCount, [](int i, int j) { return i > j; });
    sort(&strNodes[0], &strNodes[0] + uniqueCharCount,
        [frequencies] (const string &i, const string &j) {
            return frequencies[int(i[0]) - 97] > frequencies[int(j[0]) - 97];
        }
    );
    string treeNodes[(uniqueCharCount * 2) - 1];
    int weightIdx = uniqueCharCount - 1;
    int treeNodeIdx = 0;
    while (weightIdx) {
        int weightMin = weightNodes[weightIdx];
        string firstMinStr = strNodes[weightIdx];
        weightIdx--;
        weightMin += weightNodes[weightIdx];
        string secondMinStr = strNodes[weightIdx];
        treeNodes[treeNodeIdx] = firstMinStr;
        treeNodeIdx++;
        treeNodes[treeNodeIdx] = secondMinStr;
        treeNodeIdx++;
        string strMin = firstMinStr + secondMinStr;
        weightNodes[weightIdx] = weightMin;
        strNodes[weightIdx] = strMin;
        for (int i = weightIdx; i > 0; i--) {
            if (weightNodes[i] > weightNodes[i - 1]) {
                swap(weightNodes[i], weightNodes[i - 1]);
                swap(strNodes[i], strNodes[i - 1]);
            }
        }
    }
    treeNodes[treeNodeIdx] = strNodes[0];
    treeNodeIdx++;
    int depths[26] = {0};
    for (int i = 0; i < treeNodeIdx; i++) {
        int strSize = int(treeNodes[i].size());
        if (strSize > 1) {
            for (int j = 0; j < strSize; j++) {
                depths[int(treeNodes[i][j]) - 97]++;
            }
        }
    }
    int totalBits = 0;
    for (int i = 0; i < 26; i++) {
        totalBits += depths[i] * frequencies[i];
    }
    return totalBits;
}
