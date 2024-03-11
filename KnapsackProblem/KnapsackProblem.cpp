#include <vector>
#include <string>
#include <fstream>
#include "KnapsackProblem.h"

using namespace std;

struct KnapsackProblem::Brick {
    int value;
    int weight;
};

vector<KnapsackProblem::Brick> KnapsackProblem::parseInput(const string &filePath) {
    ifstream file(filePath);
    string input;
    vector<Brick> bricks;
    Brick capacity{};
    if (file.is_open()) {
        while (getline(file, input, '{')) {
            if (!input.empty()) {
                if (input.size() > 7) {
                    bricks.push_back(
                        {stoi(input.substr(0, input.size() - 9)), stoi(input.substr(3, input.size() - 7))}
                    );
                } else {
                    capacity.value = stoi(input);
                }
            }
        }
        file.close();
    }
    bricks.push_back(capacity);
    return bricks;
}

int KnapsackProblem::bfRecursion(Brick* bricks, int bricksSize, int capacity) {
    if (!bricksSize || !capacity) {
        return 0;
    }
    if (bricks[bricksSize - 1].weight > capacity) {
        return bfRecursion(bricks, bricksSize - 1, capacity);
    }
    return max(
        bfRecursion(bricks, bricksSize - 1, capacity),
        bfRecursion(bricks, bricksSize - 1, capacity - bricks[bricksSize - 1].weight) + bricks[bricksSize - 1].value
    );
}

int KnapsackProblem::bruteForce(const string &filePath) {
    vector<Brick> bricksInput = parseInput(filePath);
    int capacity = bricksInput.back().value;
    bricksInput.pop_back();
    int bricksSize = int(bricksInput.size());
    Brick bricks[bricksSize];
    for (int i = 0; i < bricksSize; i++) {
        bricks[i] = bricksInput[i];
    }
    return bfRecursion(bricks, bricksSize, capacity);
}

int KnapsackProblem::dpRecursion(Brick* bricks, int bricksSize, int capacity, int** cache) {
    if (!bricksSize || !capacity) {
        return 0;
    }
    if (cache[capacity][bricksSize] != 0) {
        return cache[capacity][bricksSize];
    }
    if (bricks[bricksSize - 1].weight > capacity) {
        cache[capacity][bricksSize] = dpRecursion(bricks, bricksSize - 1, capacity, cache);
        return cache[capacity][bricksSize];
    }
    cache[capacity][bricksSize] = max(
        dpRecursion(bricks, bricksSize - 1, capacity, cache),
        dpRecursion(bricks, bricksSize - 1, capacity - bricks[bricksSize - 1].weight, cache) + bricks[bricksSize - 1].value
    );
    return cache[capacity][bricksSize];
}

int KnapsackProblem::dynamicProgrammingRecursion(const string &filePath) {
    vector<Brick> bricksInput = parseInput(filePath);
    int capacity = bricksInput.back().value;
    bricksInput.pop_back();
    int bricksSize = int(bricksInput.size());
    Brick bricks[bricksSize];
    for (int i = 0; i < bricksSize; i++) {
        bricks[i] = bricksInput[i];
    }
    int** cache = new int*[capacity + 1];
    for (int i = 0; i < capacity + 1; i++) {
        cache[i] = new int[bricksSize + 1];
        for (int j = 0; j < bricksSize + 1; j++) {
            cache[i][j] = 0;
        }
    }
    int ans = dpRecursion(bricks, bricksSize, capacity, cache);
    for (int i = 0; i <= capacity; i++) {
        delete [] cache[i];
    }
    delete [] cache;
    return ans;
}

int KnapsackProblem::dynamicProgramming(const string &filePath) {
    vector<Brick> bricksInput = parseInput(filePath);
    int capacity = bricksInput.back().value;
    bricksInput.pop_back();
    int bricksSize = int(bricksInput.size());
    Brick bricks[bricksSize];
    for (int i = 0; i < bricksSize; i++) {
        bricks[i] = bricksInput[i];
    }
    int** cache = new int*[capacity + 1];
    for (int i = 0; i < capacity + 1; i++) {
        cache[i] = new int[bricksSize + 1];
    }
    for (int x = 0; x < capacity + 1; x++) {
        for (int y = 0; y < bricksSize + 1; y++) {
            if (!x || !y) {
                cache[x][y] = 0;
            } else if (bricks[y - 1].weight > x) {
                cache[x][y] = cache[x][y - 1];
            } else {
                cache[x][y] = max(cache[x][y - 1], cache[x - bricks[y - 1].weight][y - 1] + bricks[y - 1].value);
            }
        }
    }
    int ans = cache[capacity][bricksSize];
    for (int i = 0; i < capacity + 1; i++) {
        delete [] cache[i];
    }
    delete [] cache;
    return ans;
}
