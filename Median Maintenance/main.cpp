#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;


vector<int> loadData() {
    // ifstream file("./small_sample.txt");
    ifstream file("./Median.txt");
    vector<int> Xs;
    string str;
    while (getline(file, str)) {
        int x = stoi(str);
        Xs.push_back(x);
    }
    return Xs;
}

template<typename T> void print_queue(T q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

vector<int> naiveMethod(vector<int> Xs) {
    vector<int> medians;
    vector<int> leading;
    for (int v : Xs) {
        leading.push_back(v);
        sort(leading.begin(), leading.end());

        int m;
        if (leading.size() % 2 == 0) {
            m = leading[leading.size() / 2 - 1];
        } else {
            m = leading[(leading.size() + 1) / 2 - 1];
        }
        medians.push_back(m);
    }

    return medians;
}

vector<int> computeMedians(vector<int> Xs) {
    priority_queue<int> lowHeap;  // max-heap.
    lowHeap.push(min(Xs[0], Xs[1]));

    priority_queue< int, vector<int>, greater<int> > highHeap;  // min-heap
    highHeap.push(max(Xs[0], Xs[1]));

    vector<int> medians;

    medians.push_back(Xs[0]);  // The first median is trivial.
    medians.push_back(min(Xs[0], Xs[1]));  // the second median is the lower value among two.

    for (vector<int>::iterator pxi = Xs.begin() + 2; pxi != Xs.end(); ++pxi) {
        int xi = *pxi;

        int lowerTop = lowHeap.top();
        int higherBottom = highHeap.top();

        if (xi <= lowerTop) {
            lowHeap.push(xi);
        } else if (xi >= higherBottom) {
            highHeap.push(xi);
        } else {
            lowHeap.push(xi);
        }

        // Rebalance.
        if (lowHeap.size() > highHeap.size() + 1) {
            // Move the greatest element of low heap to high heap.
            int largestFromLower = lowHeap.top();
            lowHeap.pop();
            highHeap.push(largestFromLower);
        } else if (highHeap.size() > lowHeap.size() + 1) {
            // Move the least element of high heap to low heap.
            int leastFromHigher = highHeap.top();
            highHeap.pop();
            lowHeap.push(leastFromHigher);
        }

        int k = medians.size() + 1;
        int target;

        if (k % 2 == 1) {
            // The current one is odd, take the (k + 1) / 2 th element.
            target = (k + 1) / 2;
        } else {
            target = k / 2;
        }

        if (lowHeap.size() == target) {
            medians.push_back(lowHeap.top());
        } else {
            medians.push_back(highHeap.top());
        }
    }

    return medians;
}

int main() {
    vector<int> Xs = loadData();

    vector<int> medians = computeMedians(Xs);
    // vector<int> medians = naiveMethod(Xs);

    int total = 0;

    for (int m : medians) {
        total += m;
    }

    cout << "Total = " << total << endl;

    return 0;
}