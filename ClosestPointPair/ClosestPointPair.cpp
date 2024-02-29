#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "ClosestPointPair.h"
using namespace std;

struct ClosestPointPair::Point {
    double x;
    double y;
};

vector<ClosestPointPair::Point> ClosestPointPair::parseInput(const string& filePath) {
    vector<Point> points;
    ifstream file(filePath);
    string input;
    if (file.is_open()) {
        while (getline(file, input, '}')) {
            if (input.length() > 3) {
                if (input.find("{{") != string::npos) {
                    input = input.substr(2);
                } else {
                    input = input.substr(3);
                }
                Point point{};
                string part;
                istringstream iss(input);
                getline(iss, part, ',');
                point.x = stod(part);
                getline(iss, part, ',');
                point.y = stod(part.substr(1));
                points.push_back(point);
            }
        }
        file.close();
    }
    return points;
}

bool ClosestPointPair::sortX(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool ClosestPointPair::sortY(const Point &a, const Point &b) {
    return a.y < b.y;
}

double ClosestPointPair::splitAndSolve(vector<Point> points) {
    if (points.size() < 10) {
        double bruteForceMin = sqrt(
            pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2)
        );
        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
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
    int middleIndex = int(points.size() / 2);
    vector<Point> leftPoints(points.begin(), points.begin() + middleIndex);
    vector<Point> rightPoints(points.begin() + middleIndex, points.end());
    double newMin = min(splitAndSolve(leftPoints), splitAndSolve(rightPoints));
    int leftIndex = middleIndex;
    double leftMin = points[middleIndex].x - newMin;
    while (points[leftIndex].x >= leftMin && leftIndex > 0) {
        leftIndex--;
    }
    int rightIndex = middleIndex;
    double rightMax = points[middleIndex].x + newMin;
    while (points[rightIndex].x <= rightMax && rightIndex < points.size()) {
        rightIndex++;
    }
    vector<Point> middlePoints(points.begin() + leftIndex, points.begin() + rightIndex);
    sort(middlePoints.begin(), middlePoints.end(), sortY);
    for (int i = 0; i < middlePoints.size(); i++) {
        for (int j = 1; j <= 2; j++) {
            if (i + j < middlePoints.size()) {
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

double ClosestPointPair::divideAndConquer(const string& filePath) {
    vector<Point> points = parseInput(filePath);
    sort(points.begin(), points.end(), sortX);
    return splitAndSolve(points);
}

double ClosestPointPair::bruteForce(const string& filePath) {
    vector<Point> points = parseInput(filePath);
    sort(points.begin(), points.end(), sortX);
    double bruteForceMin = sqrt(
        pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2)
    );
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
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