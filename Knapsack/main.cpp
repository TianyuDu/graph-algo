#include <iostream>
#include <fstream>
#include <utility>
#include<vector>

using namespace std;

/*
This file describes a knapsack instance, and it has the following format:

[knapsack_size][number_of_items]

[value_1] [weight_1]

[value_2] [weight_2]

...

For example, the third line of the file is "50074 659", indicating that the second item has value 50074 and size 659, respectively.

You can assume that all numbers are positive. You should assume that item weights and the knapsack capacity are integers
*/

int totalWeight, numItems;

vector< pair<int, int> > loadData(string fileDir) {
    vector< pair<int, int> > data;
    ifstream infile(fileDir);

    infile >> totalWeight >> numItems;

    int value, weight;
    while (infile >> value >> weight) {
        pair<int, int> pair(value, weight);
        data.push_back(pair);
    }
    return data;
}

int maximumValue(const vector< pair<int, int> > Pairs) {
    throw exception("NotImplemented");
}

int main() {
    auto data = loadData("./knapsack_small.txt");
    cout << "Total weight = " << totalWeight << endl;
    cout << "Number of items = " << numItems << endl;
    return 0;
}
