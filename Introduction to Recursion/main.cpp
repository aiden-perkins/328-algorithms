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
    double min = 100;
    for (pair<double, double> p1: points) {
        for (pair<double, double> p2: points) {
            if (p1 != p2) {
                double distance = sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
                if (min > distance) {
                    min = distance;
                }
            }
        }
    }
    return min;
}

bool sortSecond(const std::pair<double, double> &a, const std::pair<double, double> &b) {
    return a.second < b.second;
}

double middle_section(double current_min, const vector<pair<double, double>>& points) {
    vector<pair<double, double>> only_middle;
    double min_distance = current_min;
    double middle_value_x = points[floor(points.size() / 2)].first;
    for (pair<double, double> point: points) {
        if (abs(middle_value_x - point.first) <= current_min) {
            only_middle.push_back(point);
        }
    }
    sort(only_middle.begin(), only_middle.end(), sortSecond);
    for (int i = 0; i < only_middle.size(); i++) {
        for (int j = 1; j <= 2; j++) {
            if (i + j < only_middle.size()) {
                double distance = sqrt(pow(only_middle[i].first - only_middle[i + j].first, 2) + pow(only_middle[i].second - only_middle[i + j].second, 2));
                if (distance < min_distance) {
                    min_distance = distance;
                }
            }
        }
    }
    return min_distance;
}

double split_and_solve(const vector<pair<double, double>>& points) {
    int right_s = floor(points.size() / 2);
    int right_e = static_cast<int>(points.size());
    int left_s = 0;
    int left_e = floor(points.size() / 2);
    double left_min, right_min;
    if (left_e - left_s > 4) {
        vector<pair<double, double>> left_points(points.begin() + left_s, points.begin() + left_e);
        left_min = split_and_solve(left_points);
    } else {
        vector<pair<double, double>> left_points(points.begin() + left_s, points.begin() + left_e);
        left_min = brute_force(left_points);
    }
    if (right_e - right_s > 4) {
        vector<pair<double, double>> right_points(points.begin() + right_s, points.begin() + right_e);
        right_min = split_and_solve(right_points);
    } else {
        vector<pair<double, double>> right_points(points.begin() + right_s, points.begin() + right_e);
        right_min = brute_force(right_points);
    }
    double m_m = min(right_min, left_min);
    return min(m_m, middle_section(m_m, points));
}

int main(int argc, char *argv[]) {
    string arg = argv[1];
    string filename = "./" + arg + ".txt";
    vector<pair<double, double>> input = parse_input(filename);
    sort(input.begin(), input.end());
    // double ans = round(brute_force(input) * 1000) / 1000;
    double ans = round(split_and_solve(input) * 1000) / 1000;
    cout << ans << endl;
    return 0;
}