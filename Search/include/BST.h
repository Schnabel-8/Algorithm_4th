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
    static Value null_value;
public:
    ~BST() {};
    Node& put(const Key& key,const Value& value);
    Value& get(Key key)const;
    //void show_pre();//show the tree in pre order
    void test() {
        Node* tmp = head;
        //cout << tmp->key << " ";
        while (tmp) {
            cout << tmp->key << " ";
            tmp = tmp->right;
        }
        cout << endl;
    }
private:
    Node* head = nullptr;
    int size = 0;
};

template<typename Key, typename Value>
Value& BST<Key, Value>::get(Key key) const{
    Node* ptr = head;
    while (ptr) {
        if (key == ptr->key)
            return ptr->value;
        else if (key < ptr->key) {
            if (ptr->left)
                ptr = ptr->left;
            else 
                break;
        }
        else {
            if (ptr->right)
                ptr = ptr->right;
            else
                break;
        }
    }
    cout << "not found!" << endl;
    return null_value;
}

template<typename Key, typename Value>
Node<Key,Value>& BST<Key,Value>::put(const Key& key,const Value& value) {
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
            //if the new node have the same key with an existed
            //node , then the value of latter would be updated
            if (tmp->key == key) {
                tmp->value = value;
                break;
            }
        }
        if(tmp->key!=key)
        ptr->key > tmp->key ? tmp->right = ptr : tmp->left = ptr;
        while (!stk.empty()) {
            k++;
            stk.top()->count+=k;
            stk.pop();
        }
    }
    size++;
    ptr->count++;
    return *ptr;
}

//initialize the static variable null_value
template<typename Key, typename Value>
Value BST<Key, Value>::null_value = Value();