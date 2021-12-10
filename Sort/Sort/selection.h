#pragma once
#include "sort.h"

//see p156
template<typename T>
class Selection :public Sort_base<T>{
public :
	void sort() override ;
	Selection() : Sort_base<T>(){};
	
};

template<typename T>
void Selection<T>::sort() {
	clock_t start, finish;
	start = clock();

	int tmp;
	T tmp_element;
	for (int i = 0; i < this->v.size(); ++i) {
		tmp_element = this->v[i];
		tmp = i;
		for (int j = i + 1; j < this->v.size(); ++j) {
			if (this->v[j] < tmp_element) {
				tmp_element = this->v[j];
				tmp = j;
			}
		}
		if (tmp != i)
			this->exchange(i, tmp);
	}

	finish = clock();
	cout << "totaltime: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}