#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

vector<long> loadData() {
    ifstream file("./data.txt");
    vector<long> arr;
    string str;
    while (getline(file, str)) {
        long x = stol(str);
        arr.push_back(x);
    }
    return arr;
}

int twoSum(vector<long> & A) {
    sort(A.begin(), A.end());

    unordered_set<long> s;

    int i = 0;
    int j = A.size() - 1;

    while (i < j) {
        long sum = A[i] + A[j];
        if (sum < -10000) {
            i ++;
        } else if (sum > 10000) {
            j --;
        } else {
            for (auto k = j; k > i; k --) {
                long total = A[k] + A[i];
                if (total >= -10000) {
                    s.insert(total);
                } else {
                    break;
                }
            }
            i ++;
        }
    }
    return s.size();
}

int main() {
    cout << "Loading Data" << endl;
    vector<long> arr = loadData();
    cout << "Computing" << endl;
    int c = twoSum(arr);
    cout << "final counter = " << c << endl;
}