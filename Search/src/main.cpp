#include "BST.h"
#include <iostream>

using std::cout;
using std::endl;

typedef BST<int, int> BST_int;
int main() {
	BST_int s;
	for (int k = 0; k < 10; ++k)
		s.put(k, k);
	s.test();
	for (int k = 0; k < 10; ++k)
		cout << s.get(k) << " ";
	cout << endl;
	return 0;
}