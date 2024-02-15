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

vector<vector<int>> StrassenAlgorithm::mergeMatrix(vector<vector<int>> matrixA, vector<vector<int>> matrixB, int matrixSize, int multiplier) {
    vector<int> rowVector(matrixSize, 0);
    vector<vector<int> > result(matrixSize, rowVector);
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            result[i][j] += matrixA[i][j] + (multiplier * matrixB[i][j]);
        }
    }
    return result;
}

vector<vector<int>> StrassenAlgorithm::runStrassen(vector<vector<int>> matrixA, vector<vector<int>> matrixB, int matrixSize) {
    if (matrixSize <= 64) {
        vector<vector<int>> bruteForceMatrix(matrixSize, vector<int>(matrixSize, 0));
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                for (int k = 0; k < matrixSize; k++) {
                    bruteForceMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        return bruteForceMatrix;
    }
    int newMatrixSize = matrixSize / 2;
    vector<int> rowVector(matrixSize, 0);
    vector<vector<int>> a11(matrixSize, rowVector);
    vector<vector<int>> a12(matrixSize, rowVector);
    vector<vector<int>> a21(matrixSize, rowVector);
    vector<vector<int>> a22(matrixSize, rowVector);
    vector<vector<int>> b11(matrixSize, rowVector);
    vector<vector<int>> b12(matrixSize, rowVector);
    vector<vector<int>> b21(matrixSize, rowVector);
    vector<vector<int>> b22(matrixSize, rowVector);
    for (int i = 0; i < newMatrixSize; i++) {
        for (int j = 0; j < newMatrixSize; j++) {
            a11[i][j] = matrixA[i][j];
            a12[i][j] = matrixA[i][j + newMatrixSize];
            a21[i][j] = matrixA[newMatrixSize + i][j];
            a22[i][j] = matrixA[i + newMatrixSize][j + newMatrixSize];
            b11[i][j] = matrixB[i][j];
            b12[i][j] = matrixB[i][j + newMatrixSize];
            b21[i][j] = matrixB[newMatrixSize + i][j];
            b22[i][j] = matrixB[i + newMatrixSize][j + newMatrixSize];
        }
    }
    vector<vector<int>> p1 = runStrassen(a11, mergeMatrix(b12, b22, newMatrixSize, -1), newMatrixSize);
    vector<vector<int>> p2 = runStrassen(mergeMatrix(a11, a12, newMatrixSize, 1), b22, newMatrixSize);
    vector<vector<int>> p3 = runStrassen(mergeMatrix(a21, a22, newMatrixSize, 1), b11, newMatrixSize);
    vector<vector<int>> p4 = runStrassen(a22, mergeMatrix(b21, b11, newMatrixSize, -1), newMatrixSize);
    vector<vector<int>> p5 = runStrassen(mergeMatrix(a11, a22, newMatrixSize, 1), mergeMatrix(b11, b22, newMatrixSize, 1), newMatrixSize);
    vector<vector<int>> p6 = runStrassen(mergeMatrix(a12, a22, newMatrixSize, -1), mergeMatrix(b21, b22, newMatrixSize, 1), newMatrixSize);
    vector<vector<int>> p7 = runStrassen(mergeMatrix(a11, a21, newMatrixSize, -1), mergeMatrix(b11, b12, newMatrixSize, 1), newMatrixSize);
    vector<vector<int>> c11 = mergeMatrix(mergeMatrix(mergeMatrix(p5, p4, newMatrixSize, 1), p2, newMatrixSize, -1), p6, newMatrixSize, 1);
    vector<vector<int>> c12 = mergeMatrix(p1, p2, newMatrixSize, 1);
    vector<vector<int>> c21 = mergeMatrix(p3, p4, newMatrixSize, 1);
    vector<vector<int>> c22 = mergeMatrix(mergeMatrix(mergeMatrix(p1, p5, newMatrixSize, 1), p3, newMatrixSize, -1), p7, newMatrixSize, -1);
    vector<vector<int> > result(matrixSize, vector<int>(matrixSize, 0));
    for (int i = 0; i < newMatrixSize; i++) {
        for (int j = 0; j < newMatrixSize; j++) {
            result[i][j] = c11[i][j];
            result[i][j + newMatrixSize] = c12[i][j];
            result[newMatrixSize + i][j] = c21[i][j];
            result[i + newMatrixSize][j + newMatrixSize] = c22[i][j];
        }
    }
    return result;
}

int StrassenAlgorithm::strassen(const string& fileAPath, const string& fileBPath) {
    vector<vector<int>> matrixA = parseInput(fileAPath);
    vector<vector<int>> matrixB = parseInput(fileBPath);
    int sum = 0;
    for (const vector<int> &row: runStrassen(matrixA, matrixB, static_cast<int>(matrixA.size()))) {
        for (int v: row) {
            sum += v;
        }
    }
    return sum;
}

vector<vector<int>> StrassenAlgorithm::splitAndSolve(vector<vector<int>> matrixA, vector<vector<int>> matrixB, int matrixSize) {
    if (matrixSize <= 64) {
        vector<vector<int>> bruteForceMatrix(matrixSize, vector<int>(matrixSize, 0));
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                for (int k = 0; k < matrixSize; k++) {
                    bruteForceMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        return bruteForceMatrix;
    }
    int newMatrixSize = matrixSize / 2;
    vector<int> rowVector(matrixSize, 0);
    vector<vector<int>> a11(matrixSize, rowVector);
    vector<vector<int>> a12(matrixSize, rowVector);
    vector<vector<int>> a21(matrixSize, rowVector);
    vector<vector<int>> a22(matrixSize, rowVector);
    vector<vector<int>> b11(matrixSize, rowVector);
    vector<vector<int>> b12(matrixSize, rowVector);
    vector<vector<int>> b21(matrixSize, rowVector);
    vector<vector<int>> b22(matrixSize, rowVector);
    for (int i = 0; i < newMatrixSize; i++) {
        for (int j = 0; j < newMatrixSize; j++) {
            a11[i][j] = matrixA[i][j];
            a12[i][j] = matrixA[i][j + newMatrixSize];
            a21[i][j] = matrixA[newMatrixSize + i][j];
            a22[i][j] = matrixA[i + newMatrixSize][j + newMatrixSize];
            b11[i][j] = matrixB[i][j];
            b12[i][j] = matrixB[i][j + newMatrixSize];
            b21[i][j] = matrixB[newMatrixSize + i][j];
            b22[i][j] = matrixB[i + newMatrixSize][j + newMatrixSize];
        }
    }
    vector<vector<int>> c11 = mergeMatrix(splitAndSolve(a11, b11, newMatrixSize), splitAndSolve(a12, b21, newMatrixSize), newMatrixSize, 1);
    vector<vector<int>> c12 = mergeMatrix(splitAndSolve(a11, b12, newMatrixSize), splitAndSolve(a12, b22, newMatrixSize), newMatrixSize, 1);
    vector<vector<int>> c21 = mergeMatrix(splitAndSolve(a21, b11, newMatrixSize), splitAndSolve(a22, b21, newMatrixSize), newMatrixSize, 1);
    vector<vector<int>> c22 = mergeMatrix(splitAndSolve(a21, b12, newMatrixSize), splitAndSolve(a22, b22, newMatrixSize), newMatrixSize, 1);
    vector<vector<int> > result(matrixSize, vector<int>(matrixSize, 0));
    for (int i = 0; i < newMatrixSize; i++) {
        for (int j = 0; j < newMatrixSize; j++) {
            result[i][j] = c11[i][j];
            result[i][j + newMatrixSize] = c12[i][j];
            result[newMatrixSize + i][j] = c21[i][j];
            result[i + newMatrixSize][j + newMatrixSize] = c22[i][j];
        }
    }
    return result;
}

int StrassenAlgorithm::divideAndConquer(const string& fileAPath, const string& fileBPath) {
    vector<vector<int>> matrixA = parseInput(fileAPath);
    vector<vector<int>> matrixB = parseInput(fileBPath);
    int sum = 0;
    for (const vector<int> &row: splitAndSolve(matrixA, matrixB, static_cast<int>(matrixA.size()))) {
        for (int v: row) {
            sum += v;
        }
    }
    return sum;
}

int StrassenAlgorithm::bruteForce(const string& fileAPath, const string& fileBPath) {
    vector<vector<int>> matrixA = parseInput(fileAPath);
    vector<vector<int>> matrixB = parseInput(fileBPath);
    int matrixSize = static_cast<int>(matrixA.size());
    vector<vector<int>> result(matrixSize, vector<int>(matrixSize, 0));
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            for (int k = 0; k < matrixSize; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    int sum = 0;
    for (const vector<int> &row: result) {
        for (int v: row) {
            sum += v;
        }
    }
    return sum;
}