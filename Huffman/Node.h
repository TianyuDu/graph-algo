#pragma once

class Node {
    public:
        int idx;
        long freq;
        Node* left;
        Node* right;

        Node() {}
        
        Node(int idx, long freq) {
            this->idx = idx;
            this->freq = freq;
            this->left = nullptr;
            this->right = nullptr;
        }

        Node(int idx, long freq, Node* left, Node* right) {
            this->idx = idx;
            this->freq = freq;
            this->left = left;
            this->right = right;
        }
};
