#pragma once
#include <vector>
#include <iostream>
#include <cassert>
#include <time.h>
#include <cmath>
using std::cout;
using std::endl;

template <typename T> 
class Sort_base {
	typedef typename std::vector<T> vector;
public:
	virtual bool is_sorted  () const {
		if(v.size()>1)
		for (int i = 0; i < v.size()-1; ++i) {
			if (v[i + 1] < v[i]) {
				cout << "not sorted yet"<<endl;
				return false;
			}
		}
		cout << "is well sorted"<<endl;
		return true;
	}

	virtual void show() const {
		for (int i=0;i < v.size();++i)
			cout << v[i] << " ";
		    cout << endl;
	}

	virtual void sort() = 0;

	virtual void push_back(const T& e) {
		v.push_back(e);
	}
	
	void exchange(int i,int j) {
		assert(i >= 0 && i < v.size() && j >= 0 && j < v.size());
		T tmp;
		tmp = v[i];
		v[i] = v[j];
		v[j] = tmp;
	}
protected:
	vector v;

};