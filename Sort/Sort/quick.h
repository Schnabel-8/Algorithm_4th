#pragma once
#include "sort.h"
#include <utility>
#include <stack>
#define random(x) (rand()%x)
typedef std::pair<int, int>    pair;
typedef std::stack<pair>       stack;

//see p182
template <typename T>
class Quick :public Sort_base<T> {
public:
	void sort() override;
	void sort(int low, int high);
	void sort_3(int low, int high);
	int partition(int low, int high);
	void quick_sort_with_stack();
	void ex_2_3_22(int low, int high);
	int compare(T a, T b) { if (a > b) return 1; else if (a < b) return -1; else return 0; };
	Quick() : Sort_base<T>() {};

};

template<typename T>
void Quick<T>::sort_3(int low, int high) {
	if (high > low) {
		int lt = low, i = low + 1, gt = high;
		T tmp = this->v[low];
		while (i <= gt) {
			int cmp = compare(this->v[i], tmp);
			if (cmp > 0)
				this->exchange(i, gt--);
			else if (cmp < 0)
				this->exchange(i++, lt++);
			else i++;
		}
		sort_3(low, lt - 1);
		sort_3(gt + 1, high);
	}
}

template<typename T>
void Quick<T>::ex_2_3_22(int low, int high) {
	if (high > low) {
		int p = low - 1, q = high + 1, i = low - 1, j = high+1;
		T tmp = this->v[low];
		while (1) {
			while (this->v[++i] <= tmp) {
				if (i == high)
					break;
				else if (this->v[i] == tmp)
					this->exchange(++p, i);
			}
			while (this->v[--j] >= tmp) {
				if (j == low)
					break;
				else if (this->v[j] == tmp)
					this->exchange(--q, j);
			}
			if (i >= j)
				break;
			this->exchange(i, j);
		}

		//Important!!
		if (i > j)i--;

		for (int k = 0; k < p - low + 1 && k + p < i; ++k) {
			this->exchange(k + low, i - k);
		}
		if(q<=high)
		for (int k = 0; k < high - q + 1 && q > j + k; ++k) {
			this->exchange(high - k, j + k);
		}
		ex_2_3_22(low, i - 1);
        ex_2_3_22(i + 1, high);
	}
}

template<typename T>
void Quick<T>::sort(int low, int high) {
	if (high > low) {
		int j = partition(low, high);
		sort(low, j - 1);
		sort(j + 1, high);
	}
}

template<typename T>
int Quick<T>::partition(int low, int high){
		int i = low, j = high + 1;
		T tmp = this->v[low];
		while (1) {
			while (this->v[++i] < tmp) {
				if (i == high)
					break;
			}
			while (this->v[--j] > tmp) {
			}
			if (i >= j)
				break;
			this->exchange(i, j);
		}
		this->exchange(low, j);
		return j;
}


template<typename T>
void Quick<T>::quick_sort_with_stack() {
	stack pair_stack;
	int low = 0, high = this->v.size() - 1;
	pair tmp;
	int j;
	pair_stack.push(pair(low, high));
	while (!pair_stack.empty()) {
		tmp = pair_stack.top();
		pair_stack.pop();
		j = partition(tmp.first, tmp.second);
			if(j-1 > tmp.first)
			pair_stack.push(pair(tmp.first, j - 1));
			if(tmp.second>(j+1))
			pair_stack.push(pair(j + 1, tmp.second));
	}
}

template<typename T>
void Quick<T>::sort() {
	clock_t start, finish;
	start = clock();

	//shuffle
	srand((int)time(0));
	int size = this->v.size();
	int shuffle_size = size / 3;
	for (int i = 0; i < shuffle_size;++i) {
		this->exchange(random(size), random(size));
	}
	
	//sort(0, size - 1);
	//sort_3(0, size - 1);
	//quick_sort_with_stack();
	ex_2_3_22(0, size - 1);

	finish = clock();
	cout << "totaltime: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}