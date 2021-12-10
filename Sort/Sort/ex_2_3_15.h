#pragma once
#include <vector>
#include <time.h>
#define random(x) (rand()%x)
typedef std::vector<int>  vector;

//see p192
//screws and nuts problem

//assuming that we have already seperated the screws and nuts 
//in fact , the cost of this process is O(n)
class screw_nut {
public:
	screw_nut():size(10) {
		init(10);
		shuffle();
	}

	screw_nut(int N):size(N){
		init(N);
		shuffle();
	}

	void shuffle() {
		srand((int)time(0));
		for (int i = 0; i < size / 3; ++i) {
			exchange(screws, random(size), random(size));
			exchange(nuts, random(size), random(size));
		}
	}

	void exchange(vector& a,int i,int j) {
		int tmp;
		tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
	}

	void show() {
		cout << "screws: ";
		for (auto& v : screws)
			cout << v << " ";
		cout << endl;
		cout << "nuts: ";
		for (auto& v : nuts)
			cout << v << " ";
		cout << endl;
	}

	int partition(int low, int high) {
			int i = low, j = high+1;
			int flag = screws[low];
			for (int k = low; k < high; ++k) {
				if (nuts[k] == flag)
					exchange(nuts, low, k);
			}
			while (i < j) {
				while (nuts[++i] < flag) { if (i == high)break; };
				while (nuts[--j] > flag) {};
				if (i >= j)break;
				exchange(nuts, i, j);
			}
			exchange(nuts, low, j);
			flag = nuts[j];
			i = low; 
			j = high + 1;
			while (i < j) {
				while (screws[++i] < flag) { if (i == high)break; };
				while (screws[--j] > flag) {};
				if (i >= j)break;
				exchange(screws, i, j);
			}
			exchange(screws, low, j);
			return j;
	    }

	void solve(int low,int high) {
		if (high > low) {
			int tmp;
			tmp = partition(low , high);
			solve(tmp + 1, high);
			solve(low, tmp);
		}
	}

	void sort() {
		clock_t start, finish;
		start = clock();

		solve(0, size - 1);

		finish = clock();
		cout << "totaltime: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	}

	bool is_sorted() {
		for(int i=0;i<size-1;++i)
			if (screws[i+1] < screws[i] && nuts[i+1] < nuts[i]) {
				cout << "not solved yet" << endl;
				return false;
			}
		cout << "is well solved" << endl;
		return true;
	}
private:
	void init(int N) {
		for (int i = 0; i < N; i++) {
			screws.push_back(i);
			nuts.push_back(i);
		}
	}

	int size;
	vector screws;
	vector nuts;
};