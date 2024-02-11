#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

vector<pair<double, double>> parse_input(const string& file_name) {
    vector<pair<double, double>> points;
    ifstream file(file_name);
    string input;
    if (file.is_open()) {
        while (getline(file, input, '}')) {
            if (input.length() > 3) {
                if (input.find("{{") != string::npos) {
                    input = input.substr(2);
                } else {
                    input = input.substr(3);
                }
                pair<double, double> point;
                string part;
                istringstream iss(input);
                getline(iss, part, ',');
                point.first = stod(part);
                getline(iss, part, ',');
                point.second = stod(part.substr(1));
                points.push_back(point);
            }
        }
        file.close();
    }
    return points;
}

double brute_force(const vector<pair<double, double>>& points) {
    double bruteForceMin = 100;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            double distance = sqrt(
                pow(points[i].first - points[j].first, 2) +
                pow(points[i].second - points[j].second, 2)
            );
            if (bruteForceMin > distance) {
                bruteForceMin = distance;
            }
        }
    }
    return bruteForceMin;
}

bool sortSecond(const std::pair<double, double> &a, const std::pair<double, double> &b) {
    return a.second < b.second;
}

double divideAndConquer(const vector<pair<double, double>>& points) {
    if (points.size() < 10) {
        double bruteForceMin = 100;
        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
                double distance = sqrt(
                    pow(points[i].first - points[j].first, 2) +
                    pow(points[i].second - points[j].second, 2)
                );
                if (bruteForceMin > distance) {
                    bruteForceMin = distance;
                }
            }
        }
        return bruteForceMin;
    }
    int middleIndex = floor(points.size() / 2);
    vector<pair<double, double>> leftPoints(points.begin(), points.begin() + middleIndex);
    vector<pair<double, double>> rightPoints(points.begin() + middleIndex, points.end());
    double newMin = min(divideAndConquer(leftPoints), divideAndConquer(rightPoints));
    int leftIndex = middleIndex;
    double leftMin = points[middleIndex].first - newMin;
    while (points[leftIndex].first >= leftMin && leftIndex > 0) {
        leftIndex--;
    }
    int rightIndex = middleIndex;
    double rightMax = points[middleIndex].first + newMin;
    while (points[rightIndex].first <= rightMax && rightIndex < points.size()) {
        rightIndex++;
    }
    vector<pair<double, double>> middlePoints(points.begin() + leftIndex, points.begin() + rightIndex);
    sort(middlePoints.begin(), middlePoints.end(), sortSecond);
    for (int i = 0; i < middlePoints.size(); i++) {
        for (int j = 1; j <= 2; j++) {
            if (i + j < middlePoints.size()) {
                double distance = sqrt(
                    pow(middlePoints[i].first - middlePoints[i + j].first, 2) +
                    pow(middlePoints[i].second - middlePoints[i + j].second, 2)
                );
                if (distance < newMin) {
                    newMin = distance;
                }
            }
        }
    }
    return newMin;
}

int main(int argc, char *argv[]) {
    double ans;
    if (argc > 1) {
        string arg = argv[1];
        string fileName = "./ClosestPointPair/" + arg + ".txt";
        vector<pair<double, double>> input = parse_input(fileName);
        sort(input.begin(), input.end());
        if (argc > 2) {
            ans = round(brute_force(input) * 1000) / 1000;
        } else {
            ans = round(divideAndConquer(input) * 1000) / 1000;
        }
        cout << ans << endl;
    } else {
        for (int i = 0; i <= 10; i++) {
            string fileName = "./ClosestPointPair/" + to_string(i) + ".txt";
            vector<pair<double, double>> input = parse_input(fileName);
            sort(input.begin(), input.end());
            ans = round(divideAndConquer(input) * 1000) / 1000;
            cout << to_string(i) << ". " << ans << endl;
        }
    }
    return 0;
}