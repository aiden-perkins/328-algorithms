#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <iostream>
#include "StrassenAlgorithm.h"

using namespace std;

vector<string> StrassenAlgorithm::rawMatrix(const string &filePath) {
    vector<string> rawMatrix;
    ifstream file(filePath);
    string input;
    while (getline(file, input, '{')) {
        if (input.length() > 3) {
            rawMatrix.push_back(input.substr(0, input.length() - 2));
        }
    }
    return rawMatrix;
}

void StrassenAlgorithm::populateMatrix(int** matrix, int matrixSize, vector<string> rawMatrix, int rawSize) {
    for (int i = 0; i < matrixSize; ++i) {
        if (i < rawSize) {
            string value;
            stringstream ss(rawMatrix[i]);
            for (int j = 0; j < matrixSize; ++j) {
                if (j < rawSize) {
                    getline(ss, value, ',');
                    matrix[i][j] = stoi(value);
                } else {
                    matrix[i][j] = 0;
                }
            }
        } else {
            for (int j = 0; j < matrixSize; ++j) {
                matrix[i][j] = 0;
            }
        }
    }
}

int StrassenAlgorithm::matrixSum(int** matrix, int matrixSize) {
    int sum = 0;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

int StrassenAlgorithm::strassenV2(const string &fileAPath, const string &fileBPath) {
    vector<string> rawMatrixA = rawMatrix(fileAPath);
    vector<string> rawMatrixB = rawMatrix(fileBPath);
    int rawSize = int(rawMatrixA.size());
    int matrixSize = int(pow(2, ceil(log2(rawSize))));
    int** matrixA = new int*[matrixSize];
    int** matrixB = new int*[matrixSize];
    for (int i = 0; i < matrixSize; ++i) {
        matrixA[i] = new int[matrixSize];
        matrixB[i] = new int[matrixSize];
    }
    populateMatrix(matrixA, matrixSize, rawMatrixA, rawSize);
    populateMatrix(matrixB, matrixSize, rawMatrixB, rawSize);
    int** matrixC = runStrassenV2(matrixA, matrixB, matrixSize);
    int ans = matrixSum(matrixC, matrixSize);
    for (int i = 0; i < matrixSize; ++i) {
        delete [] matrixC[i];
    }
    delete [] matrixA;
    delete [] matrixB;
    delete [] matrixC;
    return ans;
}

int** mergeMatrixV2(int** matrixA, int** matrixB, int matrixSize, int multiplier = 1) {
    int** resultMatrix = new int*[matrixSize];
    for (int i = 0; i < matrixSize; ++i) {
        resultMatrix[i] = new int[matrixSize];
        for (int j = 0; j < matrixSize; ++j) {
            resultMatrix[i][j] = matrixA[i][j] + (matrixB[i][j] * multiplier);
        }
    }
    return resultMatrix;
}

int** StrassenAlgorithm::runStrassenV2(int** matrixA, int** matrixB, int matrixSize) {
    if (matrixSize <= 64) {
        int** resultMatrix = new int*[matrixSize];
        for (int i = 0; i < matrixSize; ++i) {
            resultMatrix[i] = new int[matrixSize];
            for (int j = 0; j < matrixSize; ++j) {
                resultMatrix[i][j] = 0;
                for (int k = 0; k < matrixSize; ++k) {
                    resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        return resultMatrix;
    }
    int matrixSizeNew = matrixSize / 2;
    int** a11 = new int*[matrixSizeNew];
    int** a12 = new int*[matrixSizeNew];
    int** a21 = new int*[matrixSizeNew];
    int** a22 = new int*[matrixSizeNew];
    int** b11 = new int*[matrixSizeNew];
    int** b12 = new int*[matrixSizeNew];
    int** b21 = new int*[matrixSizeNew];
    int** b22 = new int*[matrixSizeNew];
    for (int i = 0; i < matrixSizeNew; ++i) {
        a11[i] = matrixA[i];
        a12[i] = matrixA[i] + matrixSizeNew;
        a21[i] = matrixA[i + matrixSizeNew];
        a22[i] = matrixA[i + matrixSizeNew] + matrixSizeNew;
        b11[i] = matrixB[i];
        b12[i] = matrixB[i] + matrixSizeNew;
        b21[i] = matrixB[i + matrixSizeNew];
        b22[i] = matrixB[i + matrixSizeNew] + matrixSizeNew;
    }
    int** p1a = a11;
    int** p1b = mergeMatrixV2(b12, b22, matrixSizeNew, -1);
    int** p2a = b22;
    int** p2b = mergeMatrixV2(a11, a12, matrixSizeNew);
    int** p3a = b11;
    int** p3b = mergeMatrixV2(a21, a22, matrixSizeNew);
    int** p4a = a22;
    int** p4b = mergeMatrixV2(b21, b11, matrixSizeNew, -1);
    int** p5a = mergeMatrixV2(a11, a22, matrixSizeNew);
    int** p5b = mergeMatrixV2(b11, b22, matrixSizeNew);
    int** p6a = mergeMatrixV2(a12, a22, matrixSizeNew, -1);
    int** p6b = mergeMatrixV2(b21, b22, matrixSizeNew);
    int** p7a = mergeMatrixV2(a11, a21, matrixSizeNew, -1);
    int** p7b = mergeMatrixV2(b11, b12, matrixSizeNew);
    delete [] a12;
    delete [] a21;
    delete [] b12;
    delete [] b21;
    int** p1 = runStrassenV2(p1a, p1b, matrixSizeNew);
    int** p2 = runStrassenV2(p2a, p2b, matrixSizeNew);
    int** p3 = runStrassenV2(p3a, p3b, matrixSizeNew);
    int** p4 = runStrassenV2(p4a, p4b, matrixSizeNew);
    int** p5 = runStrassenV2(p5a, p5b, matrixSizeNew);
    int** p6 = runStrassenV2(p6a, p6b, matrixSizeNew);
    int** p7 = runStrassenV2(p7a, p7b, matrixSizeNew);
    for (int i = 0; i < matrixSizeNew; ++i) {
        delete [] p1b[i];
        delete [] p2b[i];
        delete [] p3b[i];
        delete [] p4b[i];
        delete [] p5a[i];
        delete [] p5b[i];
        delete [] p6a[i];
        delete [] p6b[i];
        delete [] p7a[i];
        delete [] p7b[i];
    }
    delete [] a11;
    delete [] a22;
    delete [] b11;
    delete [] b22;
    delete [] p1b;
    delete [] p2b;
    delete [] p3b;
    delete [] p4b;
    delete [] p5a;
    delete [] p5b;
    delete [] p6a;
    delete [] p6b;
    delete [] p7a;
    delete [] p7b;
    int** c11a = mergeMatrixV2(p4, p2, matrixSizeNew, -1);
    int** c11b = mergeMatrixV2(p5, p6, matrixSizeNew);
    int** c11 = mergeMatrixV2(c11a, c11b, matrixSizeNew);
    int** c12 = mergeMatrixV2(p1, p2, matrixSizeNew);
    int** c21 = mergeMatrixV2(p3, p4, matrixSizeNew);
    int** c22a = mergeMatrixV2(p5, p1, matrixSizeNew);
    int** c22b = mergeMatrixV2(c22a, p3, matrixSizeNew, -1);
    int** c22 = mergeMatrixV2(c22b, p7, matrixSizeNew, -1);
    for (int i = 0; i < matrixSizeNew; ++i) {
        delete [] p1[i];
        delete [] p2[i];
        delete [] p3[i];
        delete [] p4[i];
        delete [] p5[i];
        delete [] p6[i];
        delete [] p7[i];
        delete [] c11a[i];
        delete [] c11b[i];
        delete [] c22a[i];
        delete [] c22b[i];
    }
    delete [] p1;
    delete [] p2;
    delete [] p3;
    delete [] p4;
    delete [] p5;
    delete [] p6;
    delete [] p7;
    delete [] c11a;
    delete [] c11b;
    delete [] c22a;
    delete [] c22b;
    int** resultMatrix = new int*[matrixSize];
    for (int i = 0; i < matrixSizeNew; ++i) {
        resultMatrix[i] = new int[matrixSize];
        resultMatrix[i + matrixSizeNew] = new int[matrixSize];
        for (int j = 0; j < matrixSizeNew; ++j) {
            resultMatrix[i][j] = c11[i][j];
            resultMatrix[i][j + matrixSizeNew] = c12[i][j];
            resultMatrix[matrixSizeNew + i][j] = c21[i][j];
            resultMatrix[i + matrixSizeNew][j + matrixSizeNew] = c22[i][j];
        }
    }
    for (int i = 0; i < matrixSizeNew; ++i) {
        delete [] c11[i];
        delete [] c12[i];
        delete [] c21[i];
        delete [] c22[i];
    }
    delete [] c11;
    delete [] c12;
    delete [] c21;
    delete [] c22;
    return resultMatrix;
}

vector<vector<int>> StrassenAlgorithm::parseInput(const string &filePath) {
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
    int next2Power = int(pow(2, ceil(log2(matrix.size()))));
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

int StrassenAlgorithm::strassen(const string &fileAPath, const string &fileBPath) {
    vector<vector<int>> matrixA = parseInput(fileAPath);
    vector<vector<int>> matrixB = parseInput(fileBPath);
    int sum = 0;
    for (const vector<int> &row: runStrassen(matrixA, matrixB, int(matrixA.size()))) {
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

int StrassenAlgorithm::divideAndConquer(const string &fileAPath, const string &fileBPath) {
    vector<vector<int>> matrixA = parseInput(fileAPath);
    vector<vector<int>> matrixB = parseInput(fileBPath);
    int sum = 0;
    for (const vector<int> &row: splitAndSolve(matrixA, matrixB, int(matrixA.size()))) {
        for (int v: row) {
            sum += v;
        }
    }
    return sum;
}

int StrassenAlgorithm::bruteForce(const string &fileAPath, const string &fileBPath) {
    vector<vector<int>> matrixA = parseInput(fileAPath);
    vector<vector<int>> matrixB = parseInput(fileBPath);
    int matrixSize = int(matrixA.size());
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