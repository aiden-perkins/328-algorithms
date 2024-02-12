#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include "StrassenAlgorithm.h"
using namespace std;

vector<vector<int>> StrassenAlgorithm::parseInput(const string& filePath) {
    vector<vector<int>> matrix;
    ifstream file(filePath);
    string input;
    if (file.is_open()) {
        while (getline(file, input, '{')) {
            if (input.length() > 3) {
                input = input.substr(0, input.length() - 2);
                string value;
                stringstream ss(input);
                vector<int> row;
                while (getline(ss, value, ',')) {
                    row.push_back(stoi(value));
                }
                matrix.push_back(row);
            }
        }
        file.close();
    }
    int next2Power = static_cast<int>(pow(2, ceil(log2(matrix.size()))));
    matrix.resize(next2Power, vector<int>(next2Power, 0));
    for (vector<int> &row : matrix) {
        row.resize(next2Power, 0);
    }
    return matrix;
}

vector<vector<int>> StrassenAlgorithm::subtractMatrix(vector<vector<int>> matrixA, vector<vector<int>> matrixB) {
    vector<vector<int>> result;
    for (int i = 0; i < matrixA.size(); i++) {
        vector<int> newRow;
        for (int j = 0; j < matrixA.size(); j++) {
            newRow.push_back(matrixA[i][j] - matrixB[i][j]);
        }
        result.push_back(newRow);
    }
    return result;
}

vector<vector<int>> StrassenAlgorithm::addMatrix(vector<vector<int>> matrixA, vector<vector<int>> matrixB) {
    vector<vector<int>> result;
    for (int i = 0; i < matrixA.size(); i++) {
        vector<int> newRow;
        for (int j = 0; j < matrixA.size(); j++) {
            newRow.push_back(matrixA[i][j] + matrixB[i][j]);
        }
        result.push_back(newRow);
    }
    return result;
}

vector<vector<vector<int>>> StrassenAlgorithm::divideMatrix(vector<vector<int>> matrix) {
    int middle = static_cast<int>(matrix.size() / 2);
    vector<vector<vector<int>>> quadrants(4);
    for (int i = 0; i < matrix.size(); i++) {
        vector<int> leftHalf(matrix[i].begin(), matrix[i].begin() + middle);
        vector<int> rightHalf(matrix[i].begin() + middle, matrix[i].end());
        if (i < middle) {
            quadrants[0].push_back(leftHalf);
            quadrants[1].push_back(rightHalf);
        } else {
            quadrants[2].push_back(leftHalf);
            quadrants[3].push_back(rightHalf);
        }
    }
    return quadrants;
}

vector<vector<int>> StrassenAlgorithm::combineMatrix(vector<vector<int>> m1, vector<vector<int>> m2, vector<vector<int>> m3, vector<vector<int>> m4) {
    vector<vector<int>> result;
    int middle = static_cast<int>(m1.size());
    for (int i = 0; i < 2 * m1.size(); i++) {
        vector<int> row;
        if (i < middle) {
            row.insert(row.end(), m1[i].begin(), m1[i].end());
            row.insert(row.end(), m2[i].begin(), m2[i].end());
        } else {
            row.insert(row.end(), m3[i].begin(), m3[i].end());
            row.insert(row.end(), m4[i].begin(), m4[i].end());
        }
        result.push_back(row);
    }
    return result;
}

vector<vector<int>> StrassenAlgorithm::runStrassen(vector<vector<int>> matrixA, vector<vector<int>> matrixB) {
    if (matrixA.size() < 64) {
        vector<vector<int>> bruteForceMatrix(matrixA.size(), vector<int>(matrixA.size(), 0));
        for (int i = 0; i < matrixA.size(); i++) {
            for (int j = 0; j < matrixA.size(); j++) {
                for (int k = 0; k < matrixA.size(); k++) {
                    bruteForceMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        return bruteForceMatrix;
    }
    vector<vector<vector<int>>> dividedMatrixA = divideMatrix(matrixA);
    vector<vector<vector<int>>> dividedMatrixB = divideMatrix(matrixB);
    vector<vector<int>> p1 = runStrassen(dividedMatrixA[0], subtractMatrix(dividedMatrixB[1], dividedMatrixB[3]));
    vector<vector<int>> p2 = runStrassen(addMatrix(dividedMatrixA[0], dividedMatrixA[1]), dividedMatrixB[3]);
    vector<vector<int>> p3 = runStrassen(addMatrix(dividedMatrixA[2], dividedMatrixA[3]), dividedMatrixB[0]);
    vector<vector<int>> p4 = runStrassen(dividedMatrixA[3], subtractMatrix(dividedMatrixB[2], dividedMatrixB[0]));
    vector<vector<int>> p5 = runStrassen(addMatrix(dividedMatrixA[0], dividedMatrixA[3]), addMatrix(dividedMatrixB[0], dividedMatrixB[3]));
    vector<vector<int>> p6 = runStrassen(subtractMatrix(dividedMatrixA[1], dividedMatrixA[3]), addMatrix(dividedMatrixB[2], dividedMatrixB[3]));
    vector<vector<int>> p7 = runStrassen(subtractMatrix(dividedMatrixA[0], dividedMatrixA[2]), addMatrix(dividedMatrixB[0], dividedMatrixB[1]));
    vector<vector<int>> c11 = addMatrix(subtractMatrix(addMatrix(p5, p4), p2), p6);
    vector<vector<int>> c12 = addMatrix(p1, p2);
    vector<vector<int>> c21 = addMatrix(p3, p4);
    vector<vector<int>> c22 = subtractMatrix(subtractMatrix(addMatrix(p1, p5), p3), p7);
    return combineMatrix(c11, c12, c21, c22);
}

double StrassenAlgorithm::strassen(const string& fileAPath, const string& fileBPath) {
    vector<vector<int>> matrixA = parseInput(fileAPath);
    vector<vector<int>> matrixB = parseInput(fileBPath);
    vector<vector<int>> result = runStrassen(matrixA, matrixB);
    double sum = 0;
    for (const vector<int> &row: result) {
        for (int v: row) {
            sum += v;
        }
    }
    return sum;
}

vector<vector<int>> StrassenAlgorithm::splitAndSolve(vector<vector<int>> matrixA, vector<vector<int>> matrixB) {
    if (matrixA.size() < 64) {
        vector<vector<int>> bruteForceMatrix(matrixA.size(), vector<int>(matrixA.size(), 0));
        for (int i = 0; i < matrixA.size(); i++) {
            for (int j = 0; j < matrixA.size(); j++) {
                for (int k = 0; k < matrixA.size(); k++) {
                    bruteForceMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        return bruteForceMatrix;
    }
    vector<vector<vector<int>>> dividedMatrixA = divideMatrix(matrixA);
    vector<vector<vector<int>>> dividedMatrixB = divideMatrix(matrixB);
    vector<vector<int>> c11 = addMatrix(splitAndSolve(dividedMatrixA[0], dividedMatrixB[0]), splitAndSolve(dividedMatrixA[1], dividedMatrixB[2]));
    vector<vector<int>> c12 = addMatrix(splitAndSolve(dividedMatrixA[0], dividedMatrixB[1]), splitAndSolve(dividedMatrixA[3], dividedMatrixB[3]));
    vector<vector<int>> c21 = addMatrix(splitAndSolve(dividedMatrixA[2], dividedMatrixB[0]), splitAndSolve(dividedMatrixA[1], dividedMatrixB[2]));
    vector<vector<int>> c22 = addMatrix(splitAndSolve(dividedMatrixA[2], dividedMatrixB[1]), splitAndSolve(dividedMatrixA[3], dividedMatrixB[3]));
    return combineMatrix(c11, c12, c21, c22);
}

double StrassenAlgorithm::divideAndConquer(const string& fileAPath, const string& fileBPath) {
    vector<vector<int>> matrixA = parseInput(fileAPath);
    vector<vector<int>> matrixB = parseInput(fileBPath);
    vector<vector<int>> result = splitAndSolve(matrixA, matrixB);
    double sum = 0;
    for (const vector<int> &row: result) {
        for (int v: row) {
            sum += v;
        }
    }
    return sum;
}

double StrassenAlgorithm::bruteForce(const string& fileAPath, const string& fileBPath) {
    vector<vector<int>> matrixA = parseInput(fileAPath);
    vector<vector<int>> matrixB = parseInput(fileBPath);
    vector<vector<int>> result(matrixA.size(), vector<int>(matrixA.size(), 0));
    for (int i = 0; i < matrixA.size(); i++) {
        for (int j = 0; j < matrixA.size(); j++) {
            for (int k = 0; k < matrixA.size(); k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    double sum = 0;
    for (const vector<int> &row: result) {
        for (int v: row) {
            sum += v;
        }
    }
    return sum;
}