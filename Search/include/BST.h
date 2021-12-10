#pragma once
#include <assert.h>
#include <stack>

//see p250

template<typename Key,typename Value>
struct Node {
    Node(Key a, Value b) :key(a), value(b) {};

    Key key;
    Value value;
    int count = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};

template<typename Key,typename Value>
class BST {
    typedef Node<Key,Value> Node;
    typedef std::stack<Node*> stack;
public:
    ~BST() {};
    Node& put(Key key, Value value);

private:
    Node* head = nullptr;
    int size = 0;
};

template<typename Key, typename Value>
Node<Key,Value>& BST<Key,Value>::put(Key key, Value value) {
    Node* ptr = new Node(key, value);
    assert(ptr);
    int k = 0;
    stack stk;
    if (!size) {
        head = ptr;
    }
    else {
        Node* tmp = head;
        stk.push(tmp);
        while (tmp->count > 1) {
            if (tmp->left)
                if (ptr->key < tmp->key)
                    tmp = tmp->left;
            if (tmp->right)
                if (ptr->key > tmp->key)
                    tmp = tmp->right;
            stk.push(tmp);
        }
        ptr->key > tmp->key ? tmp->right = ptr : tmp->left = ptr;
        while (!stk.empty()) {
            k++;
            Node* a;
            stk.top()->count+=k;
            stk.pop();
        }
    }
    size++;
    ptr->count++;
    return *ptr;
}