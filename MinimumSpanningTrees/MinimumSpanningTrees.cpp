#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <cmath>
#include <queue>
#include <algorithm>
#include "MinimumSpanningTrees.h"

using namespace std;

struct MinimumSpanningTrees::Node {
    int vertex;
    double weight;

    bool operator<(Node const &other) const {
        return weight > other.weight;
    }
};

struct MinimumSpanningTrees::Edge {
    double weight;
    int start;
    int end;

    bool operator<(Edge const &other) const {
        return weight < other.weight;
    }
};

vector<string> MinimumSpanningTrees::parseInput(const string &filePath) {
    vector<string> edgeStrings;
    ifstream file(filePath);
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

double MinimumSpanningTrees::primMinHeap(const string &filePath) {
    vector<string> edgeStrings = parseInput(filePath);
    int edgeCount = int(edgeStrings.size());
    double edges[edgeCount][3];
    set<double> vertices;
    for (int i = 0; i < edgeCount; i++) {
        string value;
        stringstream ss(edgeStrings[i]);
        getline(ss, value, ',');
        double start = stod(value);
        getline(ss, value, ',');
        double end = stod(value);
        getline(ss, value, ',');
        edges[i][0] = stod(value);
        edges[i][1] = start - 1;
        edges[i][2] = end - 1;
        vertices.insert(start);
        vertices.insert(end);
    }
    int vertexCount = int(vertices.size());
    Node** adjList = new Node*[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        adjList[i] = new Node[vertexCount];
    }
    int adjListLengths[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        adjListLengths[i] = 0;
    }
    for (int i = 0; i < edgeCount; i++) {
        double edgeW = edges[i][0];
        int edgeS = int(edges[i][1]);
        int edgeE = int(edges[i][2]);
        adjList[edgeS][adjListLengths[edgeS]] = Node{edgeE, edgeW};
        adjListLengths[edgeS]++;
        adjList[edgeE][adjListLengths[edgeE]] = Node{edgeS, edgeW};
        adjListLengths[edgeE]++;
    }
    priority_queue<Node, vector<Node>> queue;
    queue.push(Node{0, 0});
    bool visited[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
    }
    int visitedCount = 0;
    double totalWeight = 0;
    while (visitedCount != vertexCount) {
        Node current = queue.top();
        queue.pop();
        if (!visited[current.vertex]) {
            visited[current.vertex] = true;
            visitedCount++;
            totalWeight += current.weight;
            Node* nextVertices = adjList[current.vertex];
            for (int i = 0; i < adjListLengths[current.vertex]; i++) {
                Node next = nextVertices[i];
                if (!visited[next.vertex]) {
                    queue.push(next);
                }
            }
        }
    }
    delete [] adjList;
    return round(totalWeight * 10000) / 10000;
}

double MinimumSpanningTrees::primArray(const string &filePath) {
    vector<string> edgeStrings = parseInput(filePath);
    int edgeCount = int(edgeStrings.size());
    double edges[edgeCount][3];
    set<double> vertices;
    for (int i = 0; i < edgeCount; i++) {
        string value;
        stringstream ss(edgeStrings[i]);
        getline(ss, value, ',');
        double start = stod(value);
        getline(ss, value, ',');
        double end = stod(value);
        getline(ss, value, ',');
        edges[i][0] = stod(value);
        edges[i][1] = start - 1;
        edges[i][2] = end - 1;
        vertices.insert(start);
        vertices.insert(end);
    }
    int vertexCount = int(vertices.size());
    Node** adjList = new Node*[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        adjList[i] = new Node[vertexCount];
    }
    int adjListLengths[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        adjListLengths[i] = 0;
    }
    for (int i = 0; i < edgeCount; i++) {
        double edgeW = edges[i][0];
        int edgeS = int(edges[i][1]);
        int edgeE = int(edges[i][2]);
        adjList[edgeS][adjListLengths[edgeS]] = Node{edgeE, edgeW};
        adjListLengths[edgeS]++;
        adjList[edgeE][adjListLengths[edgeE]] = Node{edgeS, edgeW};
        adjListLengths[edgeE]++;
    }
    bool visited[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
    }
    int visitedCount = 0;
    Node queue[edgeCount * 2];
    int queueIdx = 0;
    queue[0] = Node{0, 0};
    int queueSize = 1;
    double totalWeight = 0;
    while (visitedCount != vertexCount) {
        Node current = queue[queueIdx];
        queueIdx++;
        if (!visited[current.vertex]) {
            visited[current.vertex] = true;
            visitedCount++;
            totalWeight += current.weight;
            Node* nextVertices = adjList[current.vertex];
            for (int i = 0; i < adjListLengths[current.vertex]; i++) {
                Node next = nextVertices[i];
                if (!visited[next.vertex]) {
                    // The following code is bubbling up the node I just added to the correct spot, this is slow and is
                    // the reason why my array implementation of prim is slower than using vectors with a priority heap.
                    queue[queueSize] = next;
                    for (int j = queueSize; j > queueIdx; j--) {
                        if (queue[j].weight < queue[j - 1].weight) {
                            Node temp = queue[j];
                            queue[j] = queue[j - 1];
                            queue[j - 1] = temp;
                        } else {
                            break;
                        }
                    }
                    queueSize++;
                }
            }
        }
    }
    delete [] adjList;
    return round(totalWeight * 10000) / 10000;
}

int MinimumSpanningTrees::kFind(int* parent, int x) {
    if (parent[x] != x) {
        parent[x] = kFind(parent, parent[x]);
    }
    return parent[x];
}

void MinimumSpanningTrees::kUnion(int* rank, int* parent, int x, int y) {
    int px = kFind(parent, x);
    int py = kFind(parent, y);
    if (rank[px] < rank[py]) {
        parent[px] = py;
    } else {
        parent[py] = px;
        if (rank[px] == rank[py]) {
            rank[px]++;
        }
    }
}

double MinimumSpanningTrees::kruskal(const string &filePath) {
    vector<string> edgeStrings = parseInput(filePath);
    int edgeCount = int(edgeStrings.size());
    Edge edges[edgeCount];
    set<double> vertices;
    for (int i = 0; i < edgeCount; i++) {
        string value;
        stringstream ss(edgeStrings[i]);
        getline(ss, value, ',');
        int start = stoi(value);
        getline(ss, value, ',');
        int end = stoi(value);
        getline(ss, value, ',');
        edges[i] = Edge{stod(value), start - 1, end - 1};
        vertices.insert(start);
        vertices.insert(end);
    }
    int vertexCount = int(vertices.size());
    double totalWeight = 0;
    sort(edges, edges + edgeCount);
    int parent[vertexCount];
    int rank[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    for (Edge edge: edges) {
        if (kFind(parent, edge.start) != kFind(parent, edge.end)) {
            kUnion(rank, parent, edge.start, edge.end);
            totalWeight += edge.weight;
        }
    }
    return round(totalWeight * 10000) / 10000;
}
