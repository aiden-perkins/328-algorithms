#include <vector>
#include <string>
#include <fstream>
#include "KnapsackProblem.h"
using namespace std;

struct KnapsackProblem::Brick {
    int value;
    int weight;
};

vector<KnapsackProblem::Brick> KnapsackProblem::parseInput(const string& filePath) {
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

int KnapsackProblem::bfRecursion(vector<Brick> bricks, int x, int y) {
    if (!x || !y) {
        return 0;
    }
    if (bricks[y - 1].weight > x) {
        return bfRecursion(bricks, x, y - 1);
    }
    return max(
        bfRecursion(bricks, x, y - 1),
        bfRecursion(bricks, x - bricks[y - 1].weight, y - 1) + bricks[y - 1].value
    );
}

int KnapsackProblem::bruteForce(const string& filePath) {
    vector<Brick> bricks = parseInput(filePath);
    int capacity = bricks.back().value;
    bricks.pop_back();
    return bfRecursion(bricks, capacity, int(bricks.size()));
}

int KnapsackProblem::dpRecursion(vector<Brick> bricks, vector<vector<int>> &cache, int x, int y) {
    if (!x || !y) {
        return 0;
    }
    if (cache[x][y] != 0) {
        return cache[x][y];
    }
    if (bricks[y - 1].weight > x) {
        cache[x][y] = dpRecursion(bricks, cache, x, y - 1);
        return cache[x][y];
    }
    cache[x][y] = max(
        dpRecursion(bricks, cache, x, y - 1),
        dpRecursion(bricks, cache, x - bricks[y - 1].weight, y - 1) + bricks[y - 1].value
    );
    return cache[x][y];
}

int KnapsackProblem::dynamicProgrammingRecursion(const string& filePath) {
    vector<Brick> bricks = parseInput(filePath);
    int capacity = bricks.back().value;
    bricks.pop_back();
    vector<vector<int>> cache;
    cache.resize(capacity + 1, vector<int>(bricks.size() + 1, 0));
    return dpRecursion(bricks, cache, capacity, int(bricks.size()));
}

int KnapsackProblem::dynamicProgramming(const string& filePath) {
    vector<Brick> bricks = parseInput(filePath);
    int capacity = bricks.back().value;
    bricks.pop_back();
    vector<vector<int>> cache;
    cache.resize(capacity + 1, vector<int>(bricks.size() + 1, 0));
    for (int x = 0; x < capacity + 1; x++) {
        for (int y = 0; y < bricks.size() + 1; y++) {
            if (!x || !y) {
                cache[x][y] = 0;
            } else if (bricks[y - 1].weight > x) {
                cache[x][y] = cache[x][y - 1];
            } else {
                cache[x][y] = max(cache[x][y - 1], cache[x - bricks[y - 1].weight][y - 1] + bricks[y - 1].value);
            }
        }
    }
    return cache.back().back();
}
