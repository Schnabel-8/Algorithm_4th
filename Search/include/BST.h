#pragma once
template<typename T>
struct Node {
    int key;
    T value;
    int count = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};

template<typename T>
class BST {
    typedef Node<T> Node;
public:

private:
    Node* head = nullptr;
    size = 0;
};