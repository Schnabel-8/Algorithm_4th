#pragma once
#include <cmath>
#include <stack>
#include <queue>
//see p210 2.4.24
namespace Heap_List{//we use namespace to prevent name conflicts , eg:Node in card.h
	template<typename T>
	struct Node
	{
		Node() :e(0) {};
		Node(T a) :e(a) {};
		T e;
		Node* front = nullptr;
		Node* left = nullptr;
		Node* right = nullptr;
	};

	template<typename T>
	class Heap_list {
		typedef Node<T> Node;
		typedef std::stack<Node*> stack;
		typedef std::queue<Node*> queue;
	public:
		~Heap_list() {
			if (size) {
				queue que;
				que.push(head);
				Node* tmp;
				while (!que.empty()) {
					tmp = que.front();
					que.pop();
					if (tmp->left)
						que.push(tmp->left);
					if (tmp->right)
						que.push(tmp->right);
					delete tmp;
				}
			}
		};
		void show_pre();
		void show();
		void test();
		T max() {
			if (head) {
				cout << "Empty!";
				return T();
			}
			else
				return head->e;
		}

		void exchange(Node* a, Node* b) {
			T tmp;
			tmp = b->e;
			b->e = a->e;
			a->e = tmp;
		}

		void swim(Node* ptr) {
			Node* tmp = ptr;
			while (tmp->front) {
				if (tmp->e > tmp->front->e)
					exchange(tmp, tmp->front);
				tmp = tmp->front;
			}
		};

		void sink(Node* ptr) {
			Node* tmp = ptr;
			Node* children;
				if (size) {
					while (tmp->left)
					{
						children = tmp->left;
						if (tmp->right)
							children = tmp->left->e > tmp->right->e ? tmp->left : tmp->right;
						if (tmp->e < children->e) {
							exchange(tmp, children);
							tmp = children;
						}
						else
							break;
					}
				}
				else
					cout << "Empty!"<<endl;
		};


		void push_back(T a);

		T delMax();

	private:
		Node* head = nullptr;
		Node* tail = nullptr;
		int size = 0;
	};
    
	inline int level(int& a) {
		return log2(a + 1);
	}

	template<typename T>
	void Heap_list<T>::push_back(T a) {
		Node* ptr = new Node(a);
		if (size) {
			int lv = level(size);
			if (pow(2, lv) - 1 == size) {
				Node* v = head;
				while (v->left)v = v->left;
				v->left = ptr;
				ptr->front = v;
				tail = ptr;
			}
			else if ((size % 2)) {
				Node* v = tail;

				//while (v->front&&v == v->front->right) { v = v->front; };
				while (v->front) {
					if (v == v->front->right)
						v = v->front;
					else
						break;
				}
				if (v->front)v = v->front->right;
				while (v->left) { v = v->left; };
				v->left = ptr;
				ptr->front = v;
				tail = ptr;
			}
			else {
				ptr->front = tail->front;
				tail->front->right = ptr;
				tail = ptr;
			}
		}
		else {
			head = ptr;
			tail = ptr;
		}
		size++;
		 swim(tail);
	}

	template<typename T>
	void Heap_list<T>::show_pre() {//pre_order
		stack stk;
		Node* tmp;
		if (size) {
			stk.push(head);
			while (!stk.empty()) {
				tmp = stk.top();
				stk.pop();
				cout << tmp->e << " " ;
				if (tmp->left) {
					if (tmp->right)
						stk.push(tmp->right);
					stk.push(tmp->left);
				}
			}
			cout << endl;
		}
		else
			cout << "Empty!" << endl;
	}

	template<typename T>
	void Heap_list<T>::show() {//from left to right
		queue que_1;
		queue que_2;
		queue* que;
		queue* que_;
		Node* tmp;
		if (size) {
			que_1.push(head);
			for (int k = 0; k < (level(size) + 1); ++k) {
				que = que_1.empty() ? &que_2 : &que_1;
				que_ = que_1.empty() ? &que_1 : &que_2;
				while (!que->empty()) {
					tmp = que->front();
					cout << tmp->e << " ";
					que->pop();
					if (tmp->left)
						que_->push(tmp->left);
					if (tmp->right)
						que_->push(tmp->right);
				}
			}
			cout << endl;
		}
		else
			cout << "Empty!" << endl;
	}

	template<typename T>
	T Heap_list<T>::delMax() {
		if (head) {
			T tmp=head->e;
			head->e = tail->e;
			//then we just delete the Node to which the tail points
			if (size==1) {
				delete head;
				head = tail = nullptr;
			}
			else {
				Node* v=tail;
				if (v == v->front->left) {
					if (pow(2, level(size)) == size) {
						Node* u;
						u = v->front;
						delete v;
						u->left = nullptr;
						v = head;
						while (v->right)v = v->right;
						tail = v;
					}
					else {
						Node* ptr=v->front;
						delete v;
						ptr->left = nullptr;
						while (ptr->front) {
							if (ptr == ptr->front->left) {
								ptr = ptr->front;
							}
							else
								break;
						}
						//ptr->front == nullptr is impossible
						ptr = ptr->front->left;
						while (ptr->right) ptr = ptr->right;
						tail = ptr;
					}
				}
				else {
					v->front->right = nullptr;
					tail = v->front->left;
					delete v;
				}
			}
			size--;
			sink(head);
			return tmp;
		}
		else {
			cout << "Empty!";
			return T();
		}
	}

	template<typename T>
	void Heap_list<T>::test() {//from left to right
		//Node* a = nullptr;
			//Node* b = nullptr;
		Node* a;
		//a = head->left;
		//cout << a->left->e;
		a = head->left;
		//v = head->right;
		cout << head->e << " " << a->e << " ";
		a = head->right;
		cout<< a->e << " ";
		a = head->left->left;
		cout << a->e << " " ;
		a = head->left->right;
		cout  << a->e ;//<< a->right->e << " ";
		//a = head->right->left;
		//cout << " " << a->e;
		//a = head->right->right;
		//cout<<" " << a->e;
		a = head->left->left->left;
		cout << " " << a->e;
		a = head->left->left->right;
		cout <<" " << a->e;
		a= head->left->right->left;
		cout << " " << a->e;
		a = head->left->right->right;
		cout << " " << a->e;
		a = head->left->left->right->left;
		cout << " " << a->e;
		cout << endl;
	}
}