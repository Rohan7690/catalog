#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

// Function to convert a string to a cpp_int with a given base
cpp_int convert_to_cpp_int(const string& str, int base) {
    cpp_int value = 0;
    cpp_int power = 1;
    for (int i = str.length() - 1; i >= 0; i--) {
        int digit = (str[i] >= '0' && str[i] <= '9') ? (str[i] - '0') : (str[i] - 'A' + 10);
        value += digit * power;
        power *= base;
    }
    return value;
}

// Function to calculate the Lagrange interpolation polynomial
cpp_int lagrange_interpolation(const vector<int>& x_values, const vector<cpp_int>& y_values, int x) {
    cpp_int result = 0;
    for (int i = 0; i < x_values.size(); i++) {
        cpp_int term = y_values[i];
        for (int j = 0; j < x_values.size(); j++) {
            if (j != i) {
                term *= (x - x_values[j]) / (x_values[i] - x_values[j]);
            }
        }
        result += term;
    }
    return result;
}

// Function to find the constant term (c) of the polynomial
cpp_int find_constant_term(const map<int, pair<int, string>>& roots) {
    vector<int> x_values;
    vector<cpp_int> y_values;

    for (const auto& root : roots) {
        x_values.push_back(root.first);
        y_values.push_back(convert_to_cpp_int(root.second.second, root.second.first));
    }

    cpp_int constant_term = lagrange_interpolation(x_values, y_values, 0);
    return constant_term;
}

int main() {
    // Read the input JSON data
    string json_data = R"({"keys":{"n":9,"k":6},"1":{"base":10,"value":"28735619723837"},"2":{"base":16,"value":"1A228867F0CA"},"3":{"base":12,"value":"32811A4AA0B7B"},"4":{"base":11,"value":"917978721331A"},"5":{"base":16,"value":"1A22886782E1"},"6":{"base":10,"value":"28735619654702"},"7":{"base":14,"value":"71AB5070CC4B"},"8":{"base":9,"value":"122662581541670"},"9":{"base":8,"value":"642121030037605"}})"; // Replace with your actual JSON data
    json j = json::parse(json_data);

    // Extract the roots
    map<int, pair<int, string>> roots;
    for (const auto& root : j["roots"]) {
        roots[root.key()] = {root["base"], root["value"]};
    }

    // Find the constant term
    cpp_int constant_term = find_constant_term(roots);

    cout << "Constant term: " << constant_term << endl;

    return 0;
}