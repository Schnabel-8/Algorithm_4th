#include "BST.h"

typedef BST<int, int> BST_int;
int main() {
	BST_int s;
	for (int k = 0; k < 10; ++k)
		s.put(k, k);
	return 0;
}