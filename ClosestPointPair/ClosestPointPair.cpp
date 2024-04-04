#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "ClosestPointPair.h"

using namespace std;

struct ClosestPointPair::Point {
    double x;
    double y;

    bool operator<(Point const &other) const {
        return y < other.y;
    }
};

bool ClosestPointPair::sortX(const Point &a, const Point &b) {
    return a.x < b.x;
}

vector<string> ClosestPointPair::parseInput(const string &filePath) {
    vector<string> rawPoints;
    ifstream file(filePath);
    string input;
    while (getline(file, input, '}')) {
        if (input.length() > 3) {
            if (input.find("{{") != string::npos) {
                input = input.substr(2);
            } else {
                input = input.substr(3);
            }
            rawPoints.push_back(input);
        }
    }
    return rawPoints;
}

void ClosestPointPair::populatePoints(Point* points, int pointsCount, vector<string> rawPoints) {
    for (int i = 0; i < pointsCount; ++i) {
        Point point{};
        string part;
        stringstream ss(rawPoints[i]);
        getline(ss, part, ',');
        point.x = stod(part);
        getline(ss, part, ',');
        point.y = stod(part.substr(1));
        points[i] = point;
    }
}

double ClosestPointPair::splitAndSolve(Point* points, int pointsCount) {
    if (pointsCount < 10) {
        double bruteForceMin = sqrt(
            pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2)
        );
        for (int i = 0; i < pointsCount; i++) {
            for (int j = i + 1; j < pointsCount; j++) {
                double distance = sqrt(
                    pow(points[i].x - points[j].x, 2) +
                    pow(points[i].y - points[j].y, 2)
                );
                if (bruteForceMin > distance) {
                    bruteForceMin = distance;
                }
            }
        }
        return bruteForceMin;
    }
    int middleIndex = pointsCount / 2;
    Point* leftPoints = points;
    Point* rightPoints = points + middleIndex;  // Might need a +1 here
    double newMin = min(splitAndSolve(leftPoints, middleIndex), splitAndSolve(rightPoints, middleIndex));
    int leftIndex = middleIndex;
    double leftMin = points[middleIndex].x - newMin;
    while (points[leftIndex].x >= leftMin && leftIndex > 0) {
        leftIndex--;
    }
    int rightIndex = middleIndex;
    double rightMax = points[middleIndex].x + newMin;
    while (points[rightIndex].x <= rightMax && rightIndex < pointsCount) {
        rightIndex++;
    }
    Point* middlePoints = points + leftIndex;
    int middleSize = rightIndex - leftIndex;
    sort(middlePoints, middlePoints + middleSize);
    for (int i = 0; i < middleSize; i++) {
        for (int j = 1; j <= 2; j++) {
            if (i + j < middleSize) {
                double distance = sqrt(
                    pow(middlePoints[i].x - middlePoints[i + j].x, 2) +
                    pow(middlePoints[i].y - middlePoints[i + j].y, 2)
                );
                if (distance < newMin) {
                    newMin = distance;
                }
            }
        }
    }
    return newMin;
}

double ClosestPointPair::divideAndConquer(const string &filePath) {
    vector<string> rawPoints = parseInput(filePath);
    int pointsCount = int(rawPoints.size());
    auto* points = new Point[pointsCount];
    populatePoints(points, pointsCount, rawPoints);
    sort(points, points + pointsCount, sortX);
    double ans = round(splitAndSolve(points, pointsCount) * 1000) / 1000;
    delete [] points;
    return ans;
}

double ClosestPointPair::bruteForce(const string &filePath) {
    vector<string> rawPoints = parseInput(filePath);
    int pointsCount = int(rawPoints.size());
    auto* points = new Point[pointsCount];
    populatePoints(points, pointsCount, rawPoints);
    double bruteForceMin = sqrt(
        pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2)
    );
    for (int i = 0; i < pointsCount; i++) {
        for (int j = i + 1; j < pointsCount; j++) {
            double distance = sqrt(
                pow(points[i].x - points[j].x, 2) +
                pow(points[i].y - points[j].y, 2)
            );
            if (bruteForceMin > distance) {
                bruteForceMin = distance;
            }
        }
    }
    delete [] points;
    return round(bruteForceMin * 1000) / 1000;
}
