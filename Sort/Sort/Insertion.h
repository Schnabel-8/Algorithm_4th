#pragma once
#include "sort.h"

//see p157
template <typename T>
class Insertion :public Sort_base<T> {
public:
	void sort() override;
	Insertion() : Sort_base<T>() {};
	void sort_flag();
	void sort_without_exchange();
};

template<typename T>
void Insertion<T>::sort_flag() {
	clock_t start, finish;
	start = clock();

	int size = this->v.size();
	assert(size > 1);
	for (int i = size - 1; i > 0; i--) {
		if (this->v[i] < this->v[i - 1])
			this->exchange(i, i - 1);
	}
	for (int i = 2; i < this->v.size(); ++i)
		for (int j = i;  (this->v[j] < this->v[j - 1]); --j) {
			this->exchange(j, j - 1);
		}

	finish = clock();
	cout << "totaltime: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}

template<typename T>
void Insertion<T>::sort_without_exchange() {
	clock_t start, finish;
	start = clock();

	int size = this->v.size();
	T tmp;
	int j;
	assert(size > 1);
	for (int i = size - 1; i > 0; i--) {
		if (this->v[i] < this->v[i - 1])
			this->exchange(i, i - 1);
	}
	for (int i = 2; i < size; ++i) {
		tmp = this->v[i];
		for (j = i; (this->v[j] < this->v[j - 1]); --j) {
			this->v[j] = this->v[j - 1];
		}
		this->v[j] = tmp;
	}

	finish = clock();
	cout << "totaltime: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}

template<typename T>
void Insertion<T>::sort() {
	clock_t start, finish;
	start = clock();

	int size = this->v.size();
	assert(size > 1);
	for (int i = 1; i < this->v.size(); ++i) 
		for (int j = i ; j >0 && (this->v[j]<this->v[j-1]); --j) {
			this->exchange(j, j - 1);
		}

	finish = clock();
	cout << "totaltime: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}