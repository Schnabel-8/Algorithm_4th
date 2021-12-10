#include<iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "selection.h"
#include "sort.h"
#include "Insertion.h"
#include "Shell.h"
#include "merge.h"
#include "quick.h"
#include "card.h"
#include "heap.h"
#include "heap_sort.h"
#include "ex_2_3_15.h"
#include "heap_list.h"

int main() {
	{
		//Sort_base<int> s;
		//Selection<int> s;
		//Insertion<int> s;
		//Shell<int> s;
		//Merge<int> s;
		//Quick<int> s;
		//Card<int> s;
		//Heap<int> s;
		//Heap_sort<int> s;
		//screw_nut s(1000);
		Heap_List::Heap_list<int> s;

		for (int i = 10000; i > 0; --i)
	      	s.push_back(i);
	//	s.exchange(0, 5);	
		//s.show();
		//for (int i = 0; i < 10; ++i)
		//	s.push_back(i);
		//s.max();
		//s.show();
		//s.push_back(10);
		//s.max();
		//s.show();
		/*for (int i = 0; i < 15; ++i) {
			cout<<s.delMax()<<" ";
		}*/
		//s.is_sorted();
		//s.show();
		//s.sort();
		//s.sort_Floyd();
		//s.sort_flag();
		//s.sort_without_exchange();
		//s.is_sorted();
		//s.show();
		//s.Delete();
		//s.sort();
		//s.is_sorted();
		//s.show();
		/*for (int i = 0; i < 10; ++i) {
			s.del_max();
			s.show();
		}*/
	}
	_CrtDumpMemoryLeaks();
	return 0;
}