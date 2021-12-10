#pragma once
#include "sort.h"
#include <algorithm>

//see p170 and p171
template <typename T>
class Merge :public Sort_base<T> {
	typedef typename std::vector<T> vector;
public:
	void sort() override;
	void merge_from_top(int low , int high);
	void merge_insertion(int low, int high);
	void merge_from_bottom(int low, int high);
	void merge_natural(int low, int high);
	int merge_pass(int low,int high);//return the number of ordered subsequence
	void merge(int low, int mid, int high);
	bool sorted();
	Merge() : Sort_base<T>() {};
private:
	vector aux;
};

template<typename T>
bool Merge<T>::sorted() {
	if (this->v.size() > 1)
		for (int i = 0; i < this->v.size() - 1; ++i) {
			if (this->v[i + 1] < this->v[i]) {
				return false;
			}
		}
	return true;
}

template<typename T>
void Merge<T>::merge(int low,int mid, int high) {
			/*
			vector aux;
			for (int i = low; i <= high; ++i)
				aux.push_back(this->v[i]);
			*/
	if (this->v[mid+1]<this->v[mid]) {//see p180 2.2.8
		for (int i = low; i <= high; ++i)
			aux[i - low] = this->v[i];

		int i = 0, j = mid + 1 - low;

		for (int k = low; k <= high; ++k) {
			if (i > mid - low)
				this->v[k] = aux[j++];
			else if (j > high - low)
				this->v[k] = aux[i++];
			else if (aux[j] < aux[i])
				this->v[k] = aux[j++];
			else
				this->v[k] = aux[i++];
		}
	}
}
	


template<typename T>
void Merge<T>::merge_from_bottom(int low, int high) {
	if (!sorted()) {
		int size = high - low + 1;
		for (int sz = 1; sz < size; sz *= 2)
			for (int i = low; i <= high - sz;i += 2*sz) {
				merge(i, i+sz-1, std::min(i+2*sz-1,high));
			}
	}
}

template<typename T>
void Merge<T>::merge_insertion(int low, int high) {
	if (high > low) {
			int mid = (high + low) / 2;
			if (high - low + 1 > 15) {
				merge_insertion(low, mid);
				merge_insertion(mid + 1, high);
				merge(low, mid, high);
			}
			//we use insertion sort here
			else {
				for (int i = low+1; i <= high; ++i) {
					for (int j = i; j > low && this->v[j] < this->v[j-1]; --j) {
						this->exchange(j, j-1);
					}
				}
			
		}
	}
}

template<typename T>
void Merge<T>::merge_from_top(int low , int high) {
	if (high > low) {
		int mid = (high + low) / 2;
		merge_from_top(low , mid);
		merge_from_top(mid + 1 , high);
		merge(low, mid, high);
	}
}

template<typename T>
int Merge<T>::merge_pass(int low,int high) {
	//use aux to store the starting position of the ordered subsequence
	int k = 0;
	aux[k++] = low;
	for (int i = low ; i < high; ++i) {
		if (this->v[i] > this->v[i + 1])
			aux[k++] = i + 1;
	}
	return k;
}

template<typename T>
void Merge<T>::merge_natural(int low, int high) {
	if (high > low) {
		int tmp;
		for (int k = low; k <= high-15; k += 15) {
			for (int i = k+1; i < k + 15; ++i)
				for (int j = i; j > k && this->v[j] < this->v[j-1]; j--)
					this->exchange(j, j - 1);
		}

		while (tmp = merge_pass(low, high) > 1) {
			for (int i = 0; i < tmp ; i += 2) {
				merge(aux[i], aux[i + 1] - 1, (i+2)<tmp?aux[i + 2] - 1:high);
			}
		}
	}
	
}

template<typename T>
void Merge<T>::sort() {
	clock_t start, finish;
	start = clock();

	/*
	//we use std::sort here for convenience
	//the second parameter is the iterator which point 
	//to the position after the last element
	std::sort(this->v.begin(), this->v.begin() + mid+1);
	std::sort(this->v.begin() + mid +1, this->v.end());
	*/

	aux.resize(this->v.size());
	//merge_from_top(0, this->v.size() - 1);
	//merge_insertion(0, this->v.size() - 1);
	merge_from_bottom(0, this->v.size() - 1);
	//merge_natural(0, this->v.size() - 1);

	finish = clock();
	cout << "totaltime: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}