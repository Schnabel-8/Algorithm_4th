#pragma once
#include "sort.h"

//see p162
template <typename T>
class Shell :public Sort_base<T> {
public:
	void sort() override;
	Shell() : Sort_base<T>() {};

};

template<typename T>
void Shell<T>::sort() {
	clock_t start, finish;
	start = clock();

	int size = this->v.size();
	assert(size > 1);
	int h = 1;
	while (h < size / 3)h = 3 * h + 1;
	while (h >= 1) {
		for (int i = h; i < this->v.size(); ++i)
			for (int j = i; j >= h && (this->v[j] < this->v[j - h]); j-=h) {
				this->exchange(j, j - h);
			}
		h /= 3;
	}

	finish = clock();
	cout << "totaltime: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}