#include <iostream>
#include <ftream>
#include <utilities>
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
    vector< pair<int, int> > edgeList;
    ifstream infile(fileDir);

    infile >> totalWeight >> numItems;

    int value, weight;
    while (infile >> a >> b) {
        pair<int, int> pair(a, b);
        edgeList.push_back(pair);
    }
}

int maximumValue(const vector< pair<int, int> > Pairs) {
    
}

int main() {
    return 0;
}
