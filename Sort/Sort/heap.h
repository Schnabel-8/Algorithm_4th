#pragma once
#include "sort.h"

//see p199
template<typename T>
class Heap :public Sort_base<T> {
public:
	Heap() :Sort_base<T>() { this->v.push_back(T()); };

	void swim(int k) {
		while (k > 1&&less(k/2,k)) {
			this->exchange(k, k / 2);
			k = k / 2;
		}
	};

	void sink(int k) {
		while (2*k <= N) {
			int j = 2 * k;
			if (j < N && less(j , j + 1))
				j++;
			if (!less(k, j))
				break;
			this->exchange(k, j);
			k = j;
		}
	};

	//we can change the inequality to get the min heap
	bool less(int i, int j) { return this->v[i] < this->v[j]; };

	bool is_empty() { return N == 0; };

	bool is_sorted() const { cout << "is well sorted" << endl; return true; };

	void push_back(const T& e) { this->v.push_back(e); N++; swim(N); };

	T del_max() {
		if (N) {
			T max = this->v[1];
			this->exchange(1, N--);
			this->v[N + 1] = T();
			sink(1);
			return max;
		}
		else {
			cout << "Empty!" << endl;
			return T();
		}
	};

	void show() const {
		if (N==0) {
			cout << "Empty!" << endl;
		}
		else {
			for (int i = 1; i <= N; ++i)
				cout << this->v[i] << " ";
			cout << endl;
		}
	}

	void sort() {};
private:
	int N = 0;
};