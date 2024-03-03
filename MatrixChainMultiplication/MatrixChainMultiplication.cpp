#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "MatrixChainMultiplication.h"
using namespace std;

struct MatrixChainMultiplication::MatrixSize {
    int x;
    int y;
};

vector<MatrixChainMultiplication::MatrixSize> MatrixChainMultiplication::parseInput(const string& filePath) {
    vector<MatrixSize> matrices;
    ifstream file(filePath);
    string input;
    if (file.is_open()) {
        while (getline(file, input, '{')) {
            if (!input.empty()) {
                string pair;
                stringstream ss(input);
                MatrixSize matrixSize{};
                getline(ss, pair, ' ');
                matrixSize.x = stoi(pair.substr(0, pair.size() - 1));
                getline(ss, pair, ' ');
                matrixSize.y = stoi(pair.substr(0, pair.size() - 2));
                matrices.push_back(matrixSize);
            }
        }
        file.close();
    }
    return matrices;
}

int MatrixChainMultiplication::bfRecursion(MatrixSize* matrices, int i, int j) {
    if (i == j) {
        return 0;
    }
    int* values = new int[j - i];
    for (int k = 0; k < j - i; k++) {
        int m = matrices[i].x * matrices[k + i + 1].x * matrices[j].y;
        values[k] = bfRecursion(matrices, i, k + i) + bfRecursion(matrices, k + i + 1, j) + m;
    }
    int min = *min_element(values, values + (j - i));
    delete [] values;
    return min;
}

int MatrixChainMultiplication::bruteForce(const string& filePath) {
    vector<MatrixSize> matricesInput = parseInput(filePath);
    int matricesSize = int(matricesInput.size());
    MatrixSize matrices[matricesSize];
    for (int i = 0; i < matricesSize; i++) {
        matrices[i] = matricesInput[i];
    }
    return bfRecursion(matrices, 0, matricesSize - 1);
}

int MatrixChainMultiplication::dpRecursion(MatrixSize *matrices, int i, int j, int **cache) {
    if (i == j) {
        return 0;
    }
    if (cache[i][j] != 0) {
        return cache[i][j];
    }
    int* values = new int[j - i];
    for (int k = 0; k < j - i; k++) {
        int m = matrices[i].x * matrices[k + i + 1].x * matrices[j].y;
        values[k] = dpRecursion(matrices, i, k + i, cache) + dpRecursion(matrices, k + i + 1, j, cache) + m;
    }
    cache[i][j] = *min_element(values, values + (j - i));
    delete [] values;
    return cache[i][j];
}

int MatrixChainMultiplication::dynamicProgrammingRecursion(const string& filePath) {
    vector<MatrixSize> matricesInput = parseInput(filePath);
    int matricesSize = int(matricesInput.size());
    MatrixSize matrices[matricesSize];
    for (int i = 0; i < matricesSize; i++) {
        matrices[i] = matricesInput[i];
    }
    int** cache = new int*[matricesSize];
    for (int i = 0; i < matricesSize; i++) {
        cache[i] = new int[matricesSize];
        for (int j = 0; j < matricesSize; j++) {
            cache[i][j] = 0;
        }
    }
    int ans = dpRecursion(matrices, 0, matricesSize - 1, cache);
    for (int i = 0; i < matricesSize; i++) {
        delete [] cache[i];
    }
    delete [] cache;
    return ans;
}

int MatrixChainMultiplication::dynamicProgramming(const string& filePath) {
    vector<MatrixSize> matricesInput = parseInput(filePath);
    int matricesSize = int(matricesInput.size());
    MatrixSize matrices[matricesSize];
    for (int i = 0; i < matricesSize; i++) {
        matrices[i] = matricesInput[i];
    }
    int** cache = new int*[matricesSize];
    for (int i = 0; i < matricesSize; i++) {
        cache[i] = new int[matricesSize];
    }
    for (int a = 0; a < matricesSize; a++) {
        for (int i = 0; i < matricesSize - a; i++) {
            int j = a + i;
            if (j == i) {
                cache[i][j] = 0;
            } else {
                int* values = new int[j - i];
                for (int k = 0; k < j - i; k++) {
                    values[k] = cache[i][k + i] + cache[k + i + 1][j] + (matrices[i].x * matrices[k + i + 1].x * matrices[j].y);
                }
                cache[i][j] = *min_element(values, values + (j - i));
            }
        }
    }
    int ans = cache[0][matricesSize - 1];
    for (int i = 0; i < matricesSize; i++) {
        delete [] cache[i];
    }
    delete [] cache;
    return ans;
}
