#ifndef LISTARRAY_H
#define LISTARRAY_H
#include "AbstractList.h"

#define SPARE_CAPACITY 16
template <class T>
class ListArray : public AbstractList<T> {
public:
	ListArray(int initSize = 0);
	~ListArray();

	void insert(int pos, const T & data);
	void remove(int pos);
	void set(int pos, const T & data);
	T const & get(int pos) const;
	bool empty() const;
	template <class A>
	friend std::ostream & operator<<(std::ostream & os, const ListArray<A> & list);
private:
	T* list;
	int length;
	int capacity;
	void sizeUp();
};

template <class T>
ListArray<T>::ListArray(int initSize) {
	capacity = initSize + SPARE_CAPACITY;
	length = 0;
	list = new int[capacity];
}

template <class T>
ListArray<T>::~ListArray() {
	delete [] list;
}

template <class T>
void ListArray<T>::insert(int pos, const T & data) {
	if (!this->legalPosition(pos, this->length+1)) {
		return;
	}
	if (this->length == this->capacity) // If at full capacity
		sizeUp();

	if(pos == length){ // If inserting at end -> works
		this->list[pos] = data;
	}

	else { // Else inserting at beginning or middle
		for (int i = length - 1; i >= pos; i--) {
			this->list[i+1] = this->list[i];
		}
		this->list[pos] = data;
	}
	length++;
}

template <class T>
void ListArray<T>::remove(int pos) {

}

template <class T>
void ListArray<T>::set(int pos, const T & data) {

}

template <class T>
T const & ListArray<T>::get(int pos) const {

}

template <class T>
bool ListArray<T>::empty() const {
	if (length == 0)
		return true;
	else
		return false;
}

template <class A>
std::ostream & operator<<(std::ostream & os, const ListArray<A> & list) {
	for(int i = 0; i < list.length; i++) {
		cout << list.list[i] << " ";
	}
	return os;
}

template <class T>
void ListArray<T>::sizeUp() { // This could be broken
	cout << "Size up just got called" << endl;
	int newCapacity = (this->capacity + 1) * 2;
	T* newArray = new T[newCapacity];
	for (int i = 0; i < this->length; ++i) {
		newArray[i] = std::move(this->list[i]);
	}
	this->capacity = newCapacity;
	std::swap(this->list, newArray);
	delete [] newArray;
}

#endif