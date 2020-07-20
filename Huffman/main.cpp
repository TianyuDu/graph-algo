/*
This file describes an instance of the problem. It has the following format:

[number_of_symbols]

[weight of symbol #1]

[weight of symbol #2]

...

For example, the third line of the file is "6852892," indicating that the weight of the second symbol of the alphabet is 6852892. (We're using weights instead of frequencies, like in the "A More Complex Example" video.)

Your task in this problem is to run the Huffman coding algorithm from lecture on this data set.
Q1:
What is the maximum length of a codeword in the resulting Huffman code?
Q2:
what is the minimum length of a codeword in your Huffman code?
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include "Node.h"

using namespace std;

int numSymbols;

vector<int> loadData() {
    fstream file("./huffman.txt");
    string line;
    getline(file, line);
    numSymbols = stoi(line);
    vector<int> vecW;
    while (getline(file, line)) {
        // int w;
        int w = stoi(line, nullptr, 10);
        vecW.push_back(w);
    }
    return vecW;
}

struct compNode{
    bool operator()(const Node* n1, const Node* n2) {
        return (n1->freq > n2->freq);
    }
};

Node* Huffman(const vector<int> & W) {
    // Create heap, lowest frequency first.
    priority_queue<Node*, vector<Node*>, compNode> q;
    for (int i = 0; i < W.size(); i ++) {
        long freq = W[i];
        Node *pn = new Node(i, freq);
        q.push(pn);
    }

    while (! q.empty()) {
        // Top 2 nodes with lowest frequencies.
        Node* n1 = q.top();
        q.pop();
        Node* n2 = q.top();
        q.pop();
        // Create the merged node: use idx = -1 to remark that it is an internal node.
        long mergedFreq = n1->freq + n2->freq;
        Node* merged = new Node(-1, mergedFreq, n1, n2);
        q.push(merged);
    }
    Node* root = q.top();
    return root;
}

int minimumDepth(Node * curr)
{
  // Null node has 0 depth.
  if(!curr) 
    return 0;
  
  // Leaf node reached.
  if (curr->left == nullptr && curr->right == nullptr) 
    return 1;

  // Current node has only right subtree.
  if(!curr->left) 
    return 1 + minimumDepth(curr->right);

  // Current node has only left subtree.
  else if (!curr->right) 
    return 1 + minimumDepth(curr->left);

  // if none of the above cases, then recur on both left and right subtrees.
  return 1 + min(minimumDepth(curr->right),
             minimumDepth(curr->left));
}

int maximumDepth(Node * curr)
{
  // Null node has 0 depth.
  if(!curr) 
    return 0;
  
  // Leaf node reached.
  if (curr->left == nullptr && curr->right == nullptr) 
    return 1;

  // Current node has only right subtree.
  if(!curr->left) 
    return 1 + maximumDepth(curr->right);

  // Current node has only left subtree.
  else if (!curr->right) 
    return 1 + maximumDepth(curr->left);

  // if none of the above cases, then recur on both left and right subtrees.
  return 1 + max(maximumDepth(curr->right),
             maximumDepth(curr->left));
}

int main() {
    vector<int> W = loadData();
    cout << "number of symbols = " << numSymbols << endl;
    Node* root = Huffman(W);
    int minDepth = minimumDepth(root);
    cout << minDepth - 1 << endl;
    int maxDepth = maximumDepth(root);
    cout << maxDepth - 1 << endl;
    return 0;
}
