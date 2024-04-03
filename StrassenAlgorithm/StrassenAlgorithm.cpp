#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
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

int StrassenAlgorithm::strassen(const string &fileAPath, const string &fileBPath) {
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
    int** matrixC = runStrassen(matrixA, matrixB, matrixSize);
    int ans = matrixSum(matrixC, matrixSize);
    for (int i = 0; i < matrixSize; ++i) {
        delete [] matrixC[i];
    }
    delete [] matrixA;
    delete [] matrixB;
    delete [] matrixC;
    return ans;
}

int** StrassenAlgorithm::mergeMatrix(int** matrixA, int** matrixB, int matrixSize, int multiplier) {
    int** resultMatrix = new int*[matrixSize];
    for (int i = 0; i < matrixSize; ++i) {
        resultMatrix[i] = new int[matrixSize];
        for (int j = 0; j < matrixSize; ++j) {
            resultMatrix[i][j] = matrixA[i][j] + (matrixB[i][j] * multiplier);
        }
    }
    return resultMatrix;
}

int** StrassenAlgorithm::runStrassen(int** matrixA, int** matrixB, int matrixSize) {
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
    int** p1b = mergeMatrix(b12, b22, matrixSizeNew, -1);
    int** p2a = b22;
    int** p2b = mergeMatrix(a11, a12, matrixSizeNew);
    int** p3a = b11;
    int** p3b = mergeMatrix(a21, a22, matrixSizeNew);
    int** p4a = a22;
    int** p4b = mergeMatrix(b21, b11, matrixSizeNew, -1);
    int** p5a = mergeMatrix(a11, a22, matrixSizeNew);
    int** p5b = mergeMatrix(b11, b22, matrixSizeNew);
    int** p6a = mergeMatrix(a12, a22, matrixSizeNew, -1);
    int** p6b = mergeMatrix(b21, b22, matrixSizeNew);
    int** p7a = mergeMatrix(a11, a21, matrixSizeNew, -1);
    int** p7b = mergeMatrix(b11, b12, matrixSizeNew);
    delete [] a12;
    delete [] a21;
    delete [] b12;
    delete [] b21;
    int** p1 = runStrassen(p1a, p1b, matrixSizeNew);
    int** p2 = runStrassen(p2a, p2b, matrixSizeNew);
    int** p3 = runStrassen(p3a, p3b, matrixSizeNew);
    int** p4 = runStrassen(p4a, p4b, matrixSizeNew);
    int** p5 = runStrassen(p5a, p5b, matrixSizeNew);
    int** p6 = runStrassen(p6a, p6b, matrixSizeNew);
    int** p7 = runStrassen(p7a, p7b, matrixSizeNew);
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
    int** c11a = mergeMatrix(p4, p2, matrixSizeNew, -1);
    int** c11b = mergeMatrix(p5, p6, matrixSizeNew);
    int** c11 = mergeMatrix(c11a, c11b, matrixSizeNew);
    int** c12 = mergeMatrix(p1, p2, matrixSizeNew);
    int** c21 = mergeMatrix(p3, p4, matrixSizeNew);
    int** c22a = mergeMatrix(p5, p1, matrixSizeNew);
    int** c22b = mergeMatrix(c22a, p3, matrixSizeNew, -1);
    int** c22 = mergeMatrix(c22b, p7, matrixSizeNew, -1);
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

int** StrassenAlgorithm::splitAndSolve(int** matrixA, int** matrixB, int matrixSize) {

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

    int** c11a = splitAndSolve(a11, b11, matrixSizeNew);
    int** c11b = splitAndSolve(a12, b21, matrixSizeNew);
    int** c12a = splitAndSolve(a11, b12, matrixSizeNew);
    int** c12b = splitAndSolve(a12, b22, matrixSizeNew);
    int** c21a = splitAndSolve(a21, b11, matrixSizeNew);
    int** c21b = splitAndSolve(a22, b21, matrixSizeNew);
    int** c22a = splitAndSolve(a21, b12, matrixSizeNew);
    int** c22b = splitAndSolve(a22, b22, matrixSizeNew);
    delete [] a11;
    delete [] a12;
    delete [] a21;
    delete [] a22;
    delete [] b11;
    delete [] b12;
    delete [] b21;
    delete [] b22;
    int** c11 = mergeMatrix(c11a, c11b, matrixSizeNew);
    int** c12 = mergeMatrix(c12a, c12b, matrixSizeNew);
    int** c21 = mergeMatrix(c21a, c21b, matrixSizeNew);
    int** c22 = mergeMatrix(c22a, c22b, matrixSizeNew);
    for (int i = 0; i < matrixSizeNew; ++i) {
        delete [] c11a[i];
        delete [] c11b[i];
        delete [] c12a[i];
        delete [] c12b[i];
        delete [] c21a[i];
        delete [] c21b[i];
        delete [] c22a[i];
        delete [] c22b[i];
    }
    delete [] c11a;
    delete [] c11b;
    delete [] c12a;
    delete [] c12b;
    delete [] c21a;
    delete [] c21b;
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

int StrassenAlgorithm::divideAndConquer(const string &fileAPath, const string &fileBPath) {
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
    int** matrixC = splitAndSolve(matrixA, matrixB, matrixSize);
    int ans = matrixSum(matrixC, matrixSize);
    for (int i = 0; i < matrixSize; ++i) {
        delete [] matrixC[i];
    }
    delete [] matrixA;
    delete [] matrixB;
    delete [] matrixC;
    return ans;
}

int StrassenAlgorithm::bruteForce(const string &fileAPath, const string &fileBPath) {
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
    int** matrixC = new int*[matrixSize];
    for (int i = 0; i < matrixSize; ++i) {
        matrixC[i] = new int[matrixSize];
        for (int j = 0; j < matrixSize; ++j) {
            matrixC[i][j] = 0;
            for (int k = 0; k < matrixSize; ++k) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    int ans = matrixSum(matrixC, matrixSize);
    for (int i = 0; i < matrixSize; ++i) {
        delete [] matrixC[i];
    }
    delete [] matrixA;
    delete [] matrixB;
    delete [] matrixC;
    return ans;
}
