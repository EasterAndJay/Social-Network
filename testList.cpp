#include "ArrayList.h"
#include "LinkedList.h"
#include "Wall.h"
#include <chrono>
#define N 10000

template<class T>
void benchMark(LinkedList<T> linkedList, ArrayList<T> arrayList, int n) {
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	begin = std::chrono::steady_clock::now();
	for(int i = 0; i < n; i++) {
		arrayList.insert((arrayList.getLength()-1)/2, i);
	}
	end = std::chrono::steady_clock::now();
	int arrayTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();

	begin = std::chrono::steady_clock::now();
	for(int i = 0; i < n; i++) {
		linkedList.insert((linkedList.getLength()-1)/2, i);
	}
	end = std::chrono::steady_clock::now();
	int listTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();

	cout << "Array List time for " << n << " inserts: " << arrayTime << endl;
	cout << "Linked List time for " << n << " inserts: " << listTime << endl;

}
int main() {
	//ArrayList<WallPost>* myWall = new ArrayList<WallPost>;
	
	WallPost myPost = WallPost("Hi this is my first post", "Jonathan Easterman");
	Wall* myWall = new Wall(); 
	//myWall->addPost(myPost);

	cout << myWall->toString() << endl;
	return 0;
}

