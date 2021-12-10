#pragma once
#include "sort.h"

//see p167 2.1.14
template<typename T> 
class Node {
public:
	T e;
	Node* p;
	Node() :e(0), p(nullptr){};
	Node(T a) :e(a), p(nullptr) {};
};

template <typename T>
class Card  {
	typedef Node<T>   Node;
public:
	Card() {};
	~Card() {
		Delete();
	};
	int Size() { return size; };
	void sort() ;
	bool is_sorted();
	void push_back(int e);//the first interpolation
	void exchange() {
		assert(size >= 2);
		T tmp;
		tmp = head->e;
		head->e = head->p->e;
		head->p->e = tmp;
	};//exchange the first two cards

	void bottom() {
		Node* tmp;
		tmp = head;
		head = head->p;
		tail->p = tmp;
		tail = tmp;
		tail->p = nullptr;
	}//put the top card at the bottom

	void Delete() {
		Node* tmp;
		while (head) {
			tmp = head->p;
			delete head;
			head = tmp;
		}
	};

	void print() {
		Node* ptr=head;
		while (ptr) {
			cout << ptr->e << " ";
			ptr = ptr->p;
		}
		cout << endl;
	}

private:
	int size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;
};

template<typename T>
bool Card<T>::is_sorted() {
	Node* ptr = head;
	while (ptr->p) {
		if (ptr->e > ptr->p->e) {
			std::cout << "not sorted yet" << std::endl;
			return false;
		}
		ptr = ptr->p;
	}
	std::cout << "is well sorted" << std::endl;
	return true;
}

template<typename T>
void Card<T>::push_back(int e) {
	auto a = new Node(e);
	if (head) {
		a->p = head;
		head = a;
	}
	else {
		head = a;
		tail = a;
	}
	size++;
}

template<typename T>
void Card<T>::sort() {
	clock_t start, finish;
	start = clock();

	for (int i =1; i <= size-1 ; ++i) {
		for (int k = 1; k <= size-i; ++k) {
			if (head->e < head->p->e)
				bottom();
			else {
				exchange();
				bottom();
			}
		}
		for (int j = 1; j <= i; ++j)
			bottom();
	}

	finish = clock();
	cout << "totaltime: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}