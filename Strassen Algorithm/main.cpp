#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

vector<vector<int>> parse_input(const string& file_name) {
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

int main(int argc, char *argv[]) {
    double ans;
    if (argc > 1) {
        string arg = argv[1];
        vector<vector<int>> matrixA = parse_input("./Strassen Algorithm/" + arg + "a.txt");
        vector<vector<int>> matrixB = parse_input("./Strassen Algorithm/" + arg + "b.txt");
        int next2Multiple = static_cast<int>(pow(2, ceil(log2(matrixA.size()))));
        matrixA.resize(next2Multiple, vector<int>(next2Multiple, 0));
        matrixB.resize(next2Multiple, vector<int>(next2Multiple, 0));

//        sort(input.begin(), input.end());
//        if (argc > 2) {
//            ans = round(brute_force(input) * 1000) / 1000;
//        } else {
//            ans = round(divideAndConquer(input) * 1000) / 1000;
//        }
//        cout << ans << endl;
    } else {
        for (int i = 0; i <= 10; i++) {
            string fileName = "./Strassen Algorithm/" + to_string(i) + ".txt";
            vector<pair<double, double>> input = parse_input(fileName);
            sort(input.begin(), input.end());
            ans = round(divideAndConquer(input) * 1000) / 1000;
            cout << to_string(i) << ". " << ans << endl;
        }
    }
    return 0;
}