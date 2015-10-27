#include "ListArray.h"


int main() {
	ListArray<int> ints = ListArray<int>();
	for(int i = 1; i < 18;i++) {
		ints.insert(i-1, i);
		cout << ints << endl;
	}
	for(int i = 1; i < 7; i++) {
		ints.insert(i-1, i*10);
		cout << ints << endl;
	}

	ints.insert(10, 100000);
	cout << ints << endl;
	/*for(int i = 0; i < 20; i++) {
		ints.remove(0);
		cout << ints << endl;
	}*/


	return 0;
}