#include "BST.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#define random(x) (rand()%x)

using std::cout;
using std::endl;

typedef BST<int, int> BST_int;
int main() {
	{
	BST_int s;
	s.put(11,11);
	for (int k = 0; k < 10; ++k)
		s.put(k, k);
	for (int k = 12; k < 20; ++k)
		s.put(k, k);
	//s.test();
	s.deleteMin();
	for (int k = 0; k < 20; ++k)
		cout << s.get(k) << " ";
	cout << endl;
	//cout << s.rank(s.select(5).key);
	cout << s.floor(10).key<<endl;
	cout << s.ceil(10).key;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}