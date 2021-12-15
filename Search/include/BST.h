#pragma once
#include <assert.h>
#include <stack>

//see p250

template<typename Key,typename Value>
struct Node {
    Node(Key a, Value b) :key(a), value(b) {};
    Node() :key(Key()),value(Value()) {};
    //we return Node& in BST::function , so in order to prevent 
    //destroying the tree , we use const Key here

    //IMPORTANT!!!
    //accroding to Effective C++ , it's not always wise to return
    //a reference , our user may change the public members of Node,
    //so it's a failed attempt
    const Key key;
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
    static Node null_node;
public:
    ~BST() {};
    Node& put(const Key& key,const Value& value);
    Value& get(Key key)const;
    void Delete(Key key);
    //void show_pre();//show the tree in pre order
    Node& max()const {
        if (!size) {
            cout << "Empty!" << endl;
            return null_value;
        }
        Node* tmp = head;
        while (tmp->left)
            tmp = tmp->left;
        return *tmp;
    };

    Node& min()const {
        if (!size) {
            cout << "Empty!" << endl;
            return null_value;
        }
        Node* tmp = head;
        while (tmp->right)
            tmp = tmp->right;
        return *tmp;
    };

    Node& floor(Key key)const {
        return floor(head, key);
    }

    Node& floor(Node* ptr,Key key) const{
        Node* tmp = ptr;
        while (tmp) {
            if (tmp->key == key)
                return *tmp;
            else if (tmp->key<key) {
                if (tmp->right)
                    if (tmp->right->key < key)
                        tmp = tmp->right;
                    else
                        break;
                else
                    break;
            }
            else if (tmp->key>key) {
                if (tmp->left)
                    tmp = tmp->left;
                else
                    break;
            }
         }
        if (tmp)
            if(tmp->key <= key)
            return *tmp;
        cout << "floor not found!" << endl;
        return null_node;
    }

    Node& ceil(Key key) const {
        return ceil(head, key);
    }

    Node& ceil(Node* ptr,Key key) const {
        Node* tmp = ptr;
        while (tmp) {
            if (tmp->key == key)
                return *tmp;
            else if (tmp->key > key) {
                if (tmp->left)
                    if (tmp->left->key > key)
                        tmp = tmp->left;
                    else
                        break;
                else
                    break;
            }
            else if (tmp->key < key) {
                if (tmp->right)
                    tmp = tmp->right;
                else
                    break;
            }
        }
        if (tmp)
            if(tmp->key >= key)
            return *tmp;
        cout << "ceil not found!";
        return null_node;
    }

    inline int count(Node* ptr) const {
        return ptr ? ptr->count : 0;
    }

    Node& select(int k) const {
        return select(head, k);
    }

    Node& select(Node* ptr,int k) const {
        Node* tmp = ptr;
        while (tmp) {
            if (count(tmp) == k)
                return *tmp;
            else if (count(tmp->left) > k) 
                tmp = tmp->left;
            else if (count(tmp->right) >= k - count(tmp->left) - 1) 
                tmp = tmp->right;
            else
                break;
        }
        cout << "Error!" << endl;
        return null_node;
    }

    int rank(Key k) {
        return rank(head, k);
    }

    int rank(Node* ptr,Key k) {
        Node* tmp = ptr;
        int rank = 0;
        while (tmp) {
            if (tmp->key == k)
                return count(tmp);
            else if (tmp->key > k)
                tmp = tmp->left;
            else if (tmp->key < k) {
                tmp = tmp->right;
                    rank += 1 + count(tmp->left);
            }
            else
                break;
        }
        cout << "Error!" << endl;
        return 0;
    }

    void test() {
        Node* tmp = head;
        //cout << tmp->key << " ";

        while (tmp) {
            cout << tmp->key <<" count: "<<count(tmp)<< " ";
            tmp = tmp->right;
        }
        cout << endl;
    }

    void deleteMin() {
        if (head) {
            Node* tmp = head;
            if (!tmp->left) {
                tmp = tmp->right;
                delete head;
                head = tmp;
            }
            else {
                tmp->count--;
                while (tmp->left->left) {
                    tmp = tmp->left;
                    tmp->count--;
                }
                Node* tmp2;
                tmp2 = tmp->left->right;
                delete tmp->left;
                tmp->left = tmp2;
            }
            size--;
        }
    }
private:
    Node* head = nullptr;
    int size = 0;
};

template<typename Key, typename Value>
void BST<Key, Value>::Delete(Key key) {
    if (size == 0)
        cout << "not found!";
    else if (size == 1) {
        delete head;
        head = nullptr;
    }
    else {
        Node* ptr = head;
        do{
            
        } while (ptr);
    }
}

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
    cout << "not found!" ;
    return null_value;
}

template<typename Key, typename Value>
Node<Key,Value>& BST<Key,Value>::put(const Key& key,const Value& value) {
    Node* ptr = new Node(key, value);
    assert(ptr);
    stack stk;
    if (!size) {
        head = ptr;
    }
    else {
        Node* tmp = head;
        stk.push(tmp);
        while (tmp->count > 1) {
            if (tmp->left && ptr->key < tmp->key)
                tmp = tmp->left;
            else if (tmp->right && ptr->key > tmp->key)
                tmp = tmp->right;
            else
                break;
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
            stk.top()->count++;
            stk.pop();
        }
    }
    size++;
    ptr->count++;
    return *ptr;
}

//initialize the static variable null_value and null_node
template<typename Key, typename Value>
Value BST<Key, Value>::null_value = Value();

template<typename Key, typename Value>
Node<Key,Value> BST<Key, Value>::null_node = Node();