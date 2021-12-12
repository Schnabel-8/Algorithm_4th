#include "BST.h"
#include <iostream>
#define random(x) (rand()%x)

using std::cout;
using std::endl;

typedef BST<int, int> BST_int;
int main() {
	BST_int s;
	for (int k = 0; k < 10; ++k)
		s.put(10,10);
	s.test();
	for (int k = 0; k < 10; ++k)
		cout << s.get(k) << " ";
	cout << endl;
	return 0;
}