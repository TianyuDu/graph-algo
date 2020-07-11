#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

typedef pair<int, int> Tuple;
// Define the hash function for pairs.
struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2> &pair) const
	{
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

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

int getMaximumValue(const vector< pair<int, int> > & data) {
    // V[i, x] := maximum value attained by choosing from the first i elements subject to total weight capacity x.
    map< pair<int, int>, int> V;
    for (int x = 0; x <= totalWeight; x ++) {
        V[make_pair(0, x)] = 0;  // for the first zero item, can get 0.
    }

    for (int x = 0; x <= totalWeight; x++) {
        for (int i = 0; i <= numItems; i ++) {
            /*
            Recurrence:
            Choosing from {1,2,...,i} s.t. total weight <= x.
            Let S[i, x] be the optimal set.
            Case 1: i not in S[i, x], then S[i, x] = S[i-1, x], so V[i, x] = V[i-1, x].
            Case 2: i in S[i, x], then S\{i} = S[i-1, x-wi].
            */
            int value = data[i].first;
            int weight = data[i].second;
            if (weight > x) {
                // the current item is infeasible.
                V[make_pair(i, x)] = V[make_pair(i - 1, x)];
            } else {
                V[make_pair(i, x)] = max(
                    V[make_pair(i - 1, x)],
                    V[make_pair(i - 1, x - weight)] + value
                 );
            }
        }
    }

    return V[make_pair(numItems, totalWeight)];
}

// unordered_map< pair<int, int>, int> Vr;
unordered_map<Tuple, int, pair_hash> Vr;

int recursiveFindMaxmumValue(const vector< pair<int, int> > & data, int i, int x) {
    // Check if cached before.
    auto got = Vr.find(make_pair(i, x));
    if (got != Vr.end()) {
        return got->second;
    }

    int curValue = data.at(i - 1).first;
    int curWeight = data.at(i - 1).second;

    int maxVal;
    if (i == 0) {
        // Base case.
        maxVal = 0;
    } else if (curWeight > x) {
        // i-th element is infeasible.
        maxVal = recursiveFindMaxmumValue(data, i - 1, x);
    } else {
        // The general case.
        maxVal = max(
            recursiveFindMaxmumValue(data, i-1, x),
            recursiveFindMaxmumValue(data, i-1, x-curWeight) + curValue
        );
    }
    // Cache the solution to subproblem.
    Vr[make_pair(i, x)] = maxVal;
    return maxVal;
}

int main() {
    cout << "Smaller Problem" << endl;
    auto data = loadData("./knapsack_small.txt");
    cout << "Total weight = " << totalWeight << endl;
    cout << "Number of items = " << numItems << endl;
    cout << "Processing..." << endl;
    int maxVal = getMaximumValue(data);
    cout << "Solution = " << maxVal << endl;

    // cout << "Larger Problem" << endl;
    // auto data = loadData("./knapsack_large.txt");
    // cout << "Total weight = " << totalWeight << endl;
    // cout << "Number of items = " << numItems << endl;
    // cout << "Processing..." << endl;
    // int maxVal = recursiveFindMaxmumValue(data, numItems, totalWeight);
    // cout << "Solution = " << maxVal << endl;
    // return 0;
}
