#include <fstream>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <climits>
#include <vector>
#include <string>
#include "AllPairsShortestPath.h"

using namespace std;

struct AllPairsShortestPath::Compare {
    bool operator() (pair<int, int> const &p1, pair<int, int> const &p2) {
        return p1.first > p2.first;
    }
};

struct AllPairsShortestPath::VertexPair {
    int start;
    int end;
};

AllPairsShortestPath::VertexPair AllPairsShortestPath::parseInput(const string &filePath) {
    string input;
    ifstream file(filePath);
    VertexPair ansPair{};
    if (file.is_open()) {
        getline(file, input, ',');
        ansPair.start = stoi(input.substr(1));
        getline(file, input, ',');
        ansPair.end = stoi(input.substr(1, input.size() - 2));
    }
    return ansPair;
}

vector<string> AllPairsShortestPath::parseGraph() {
    vector<string> edgeStrings;
    ifstream file("./AllPairsShortestPath/graph.txt");
    string input;
    if (file.is_open()) {
        while (getline(file, input, '{')) {
            if (input.length() > 3) {
                edgeStrings.push_back(input.substr(0, input.length() - 2));
            }
        }
        file.close();
    }
    return edgeStrings;
}

int AllPairsShortestPath::dijkstrasArray(const string &filePath) {
    vector<string> edgeStrings = parseGraph();
    VertexPair ansPair = parseInput(filePath);
    int edgeCount = int(edgeStrings.size());
    int edges[edgeCount][3];
    set<int> vertices;
    for (int i = 0; i < edgeCount; i++) {
        string value;
        stringstream ss(edgeStrings[i]);
        getline(ss, value, ',');
        edges[i][0] = stoi(value);
        vertices.insert(stoi(value));
        getline(ss, value, ',');
        edges[i][1] = stoi(value);
        vertices.insert(stoi(value));
        getline(ss, value, ',');
        edges[i][2] = stoi(value);
    }
    int vertexCount = int(vertices.size());
    int adjMatrix[vertexCount][vertexCount];
    int distanceMins[vertexCount];
    bool finished[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        distanceMins[i] = INT_MAX;
        finished[i] = false;
        for (int j = 0; j < vertexCount; j++) {
            adjMatrix[i][j] = 0;
        }
    }
    for (int i = 0; i < edgeCount; i++) {
        adjMatrix[edges[i][0] - 1][edges[i][1] - 1] = edges[i][2];
        adjMatrix[edges[i][1] - 1][edges[i][0] - 1] = edges[i][2];
    }
    distanceMins[ansPair.start - 1] = 0;
    for (int _ = 0; _ < vertexCount; _++) {
        int currentIdx = -1;
        int nextMinDistance = INT_MAX;
        for (int i = 0; i < vertexCount; i++) {
            if (distanceMins[i] < nextMinDistance && !finished[i]) {
                nextMinDistance = distanceMins[i];
                currentIdx = i;
            }
        }
        if (currentIdx == -1) {
            throw runtime_error("finished is complete");
        }
        finished[currentIdx] = true;
        for (int i = 0; i < vertexCount; i++) {
            if (!finished[i] && adjMatrix[currentIdx][i]) {
                int costNew = distanceMins[currentIdx] + adjMatrix[currentIdx][i];
                if (costNew < distanceMins[i]) {
                    distanceMins[i] = costNew;
                }
            }
        }
    }
    return distanceMins[ansPair.end - 1];
}

int AllPairsShortestPath::dijkstrasMinHeap(const string &filePath) {
    vector<string> edgeStrings = parseGraph();
    VertexPair ansPair = parseInput(filePath);
    int edgeCount = int(edgeStrings.size());
    int edges[edgeCount][3];
    set<int> vertices;
    for (int i = 0; i < edgeCount; i++) {
        string value;
        stringstream ss(edgeStrings[i]);
        getline(ss, value, ',');
        edges[i][0] = stoi(value);
        vertices.insert(stoi(value));
        getline(ss, value, ',');
        edges[i][1] = stoi(value);
        vertices.insert(stoi(value));
        getline(ss, value, ',');
        edges[i][2] = stoi(value);
    }
    int vertexCount = int(vertices.size());
    map<pair<int, int>, int> cost;
    int adjList[vertexCount][vertexCount];
    int vertexNeighborCount[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        vertexNeighborCount[i] = 0;
    }
    for (int i = 0; i < edgeCount; i++) {
        int vertex1Idx = edges[i][0] - 1;
        int vertex2Idx = edges[i][1] - 1;
        int edgeCost = edges[i][2];
        adjList[vertex1Idx][vertexNeighborCount[vertex1Idx]] = vertex2Idx;
        vertexNeighborCount[vertex1Idx]++;
        adjList[vertex2Idx][vertexNeighborCount[vertex2Idx]] = vertex1Idx;
        vertexNeighborCount[vertex2Idx]++;
        cost[pair<int, int>(vertex1Idx, vertex2Idx)] = edgeCost;
        cost[pair<int, int>(vertex2Idx, vertex1Idx)] = edgeCost;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> queue;
    queue.emplace(0, ansPair.start - 1);
    map<int, int> distanceMins;
    for (int i = 0; i < vertexCount; i++) {
        distanceMins[i] = INT_MAX;
    }
    distanceMins[ansPair.start - 1] = 0;
    while (!queue.empty()) {
        pair<int, int> currentNode = queue.top();
        queue.pop();
        for (int i = 0; i < vertexNeighborCount[currentNode.second]; i++) {
            int newVertex = adjList[currentNode.second][i];
            int newCost = currentNode.first + cost[pair<int, int>(currentNode.second, newVertex)];
            if (newCost < distanceMins[newVertex]) {
                distanceMins[newVertex] = newCost;
                queue.emplace(newCost, newVertex);
            }
        }
    }
    return distanceMins[ansPair.end - 1];
}

int AllPairsShortestPath::floydWarshall(const string &filePath) {
    vector<string> edgeStrings = parseGraph();
    int edgeCount = int(edgeStrings.size());
    int edges[edgeCount][3];
    set<int> vertices;
    int totalWeight = 0;
    for (int i = 0; i < edgeCount; i++) {
        string value;
        stringstream ss(edgeStrings[i]);
        getline(ss, value, ',');
        edges[i][0] = stoi(value);
        vertices.insert(stoi(value));
        getline(ss, value, ',');
        edges[i][1] = stoi(value);
        vertices.insert(stoi(value));
        getline(ss, value, ',');
        edges[i][2] = stoi(value);
        totalWeight += stoi(value);
    }
    int vertexCount = int(vertices.size());
    int adjMatrix[vertexCount][vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            adjMatrix[i][j] = totalWeight;
        }
        adjMatrix[i][i] = 0;
    }
    for (int i = 0; i < edgeCount; i++) {
        adjMatrix[edges[i][0] - 1][edges[i][1] - 1] = edges[i][2];
        adjMatrix[edges[i][1] - 1][edges[i][0] - 1] = edges[i][2];
    }
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            for (int k = j + 1; k < vertexCount; k++) {
                int possible = adjMatrix[j][i] + adjMatrix[i][k];
                if (adjMatrix[j][k] > possible) {
                    adjMatrix[j][k] = possible;
                    adjMatrix[k][j] = possible;
                }
            }
        }
    }
    VertexPair ansPair = parseInput(filePath);
    return adjMatrix[ansPair.start - 1][ansPair.end - 1];
}
