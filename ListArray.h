#ifndef LISTARRAY_H
#define LISTARRAY_H
#include "AbstractList.h"

#define SPARE_CAPACITY 16

template <class T>
class ListArray : public AbstractList<T> {
public:
	ListArray(int initSize = 0);
	ListArray(const ListArray<T> & list);
	~ListArray();

	void insert(int pos, const T & data);
	void remove(int pos);
	void set(int pos, const T & data);
	T const & get(int pos) const;

	int getLength() const { return length; }

	template <class A>
	friend std::ostream & operator<<(std::ostream & os, const ListArray<A> & list);
private:
	T* list;
	int length;
	int capacity;
	void resize();
};

template <class T>
ListArray<T>::ListArray(int initSize) {
	capacity = initSize + SPARE_CAPACITY;
	length = 0;
	list = new int[capacity];
}

template <class T>
ListArray<T>::ListArray(const ListArray<T> & rhs) {
	this->length = rhs.getLength();
	this->capacity = rhs.capacity;
	this->list = new T [this->capacity];

	for (int i = 0; i < length; ++i) {
		this->list[i] = rhs.list[i];
	}
}

template <class T>
ListArray<T>::~ListArray() {
	delete [] this->list;
}

template <class T>
void ListArray<T>::insert(int pos, const T & data) {
	if (!this->legalPosition(pos, this->length+1)) {
		return;
	}

	if (this->length == this->capacity) // If at full capacity
		resize(); // double size

	else if(pos == length){ // If inserting at end
		this->list[pos] = data;
	}

	else { // Else inserting at beginning or middle
		for (int i = length - 1; i >= pos; i--) {
			this->list[i+1] = this->list[i]; // Move everything over 1 space
		}
		this->list[pos] = data; // make pos = data
	}
	this->length++; // increment length
}

template <class T>
void ListArray<T>::remove(int pos) {
	if (!this->legalPosition(pos, this->getLength()))
		return;
	else if(pos == (getLength() - 1)) { // Removing last element
		this->list[pos] = 0;
	}
	else { // Removing first or middle element
		for (int i = pos + 1; i < length; i++) { //shift all elements to the left
			this->list[i-1] = this->list[i];
		}
	}

	this->length--;
}

template <class T>
void ListArray<T>::set(int pos, const T & data) {
	this->list[pos] = data;
}

template <class T>
T const & ListArray<T>::get(int pos) const {
	if (!this->legalPosition(pos, this->getLength()))
		return NULL;
	else
		return this->list[pos];
}

template <class A>
std::ostream & operator<<(std::ostream & os, const ListArray<A> & list) {
	for(int i = 0; i < list.length; i++) {
		cout << list.list[i] << " ";
	}
	return os;
}

template <class T>
void ListArray<T>::resize() {
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