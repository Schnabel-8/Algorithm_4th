#pragma once
#include "sort.h"

//see p206
template<typename T>
class Heap_sort :public Sort_base<T> {
public:
	void sort() override;
	void sort_Floyd();//see p208
	Heap_sort() : Sort_base<T>() { this->push_back(T()); };
	void sink(int k, int N);
	void swim(int k);

	void show() const {
		if (this->v.size() == 1) {
			cout << "Empty!" << endl;
		}
		else {
			for (int i = 1; i < this->v.size(); ++i)
				cout << this->v[i] << " ";
			cout << endl;
		}
	}

    bool is_sorted() const {
		if (this->v.size() > 2)
			for (int i = 1; i < this->v.size() - 1; ++i) {
				if (this->v[i + 1] < this->v[i]) {
					cout << "not sorted yet" << endl;
					return false;
				}
			}
		cout << "is well sorted" << endl;
		return true;
	}
};

template<typename T>
void Heap_sort<T>::sink(int k,int N) {
	int tmp = k - 1;
	int bound = N - tmp;
	int j = 1;
	while (j * 2 <= bound) {
		j = j * 2;
		if (j + 1 <= bound && this->v[tmp+j] < this->v[tmp+j + 1])
			j++;
		if (this->v[k] < this->v[tmp + j])
			this->exchange(k, tmp + j);
		k = j;
	}
}

template<typename T>
void Heap_sort<T>::swim(int k) {
	int tmp = k;
	while (tmp/2 >= 1) {
		if (this->v[tmp] > this->v[tmp / 2]) {
			this->exchange(tmp, tmp / 2);
			tmp = tmp / 2;
		}
		else break;
	}
}

template<typename T>
void Heap_sort<T>::sort_Floyd() {
	clock_t start, finish;
	start = clock();

	int N = this->v.size() - 1;
	for (int k = N / 2; k >= 1; --k)
		sink(k, N);
	T tmp;
	int flag;
	while (N > 1) {
		flag = 1;
		tmp = this->v[N];
		this->v[N] = this->v[1];
		while (2 * flag < N) {
			if (2 * flag + 1 < N) {
				if (this->v[2 * flag + 1] > this->v[2 * flag]) {
					this->v[flag] = this->v[2 * flag + 1];
					flag = 2 * flag + 1;
				}
				else {
					this->v[flag] = this->v[2 * flag];
					flag *= 2;
				}
			}
			else {
				this->v[flag] = this->v[2 * flag];
				flag *= 2;
			}
		}
		this->v[flag] = tmp;
		N--;
		swim(flag);
	}

	finish = clock();
	cout << "totaltime: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}

template<typename T>
void Heap_sort<T>::sort() {
	clock_t start, finish;
	start = clock();

	int N = this->v.size() - 1;
	for (int k = N / 2; k >= 1; --k)
		sink(k, N);
	while (N > 1) {
		this->exchange(1, N--);
		sink(1, N);
	}

	finish = clock();
	cout << "totaltime: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}