#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "AbstractList.h"

#define SPARE_CAPACITY 16

template <class T>
class ArrayList : public AbstractList<T> {
public:
	ArrayList(int initSize = 0);
	ArrayList(const ArrayList<T> & list);
	~ArrayList();

	void insert(int pos, const T & data);
	void remove(int pos);

	void deleteByValue(T & data);
	void deleteByValue(T && data);

	int find(T & data);
	int find(T && data);

	void set(int pos, const T & data);
	T const & get(int pos) const;

	int getLength() const { return length; }

	template <class A>
	friend std::ostream & operator<<(std::ostream & os, const ArrayList<A> & list);

	typedef T * iterator;
	typedef const T * const_iterator;

	iterator begin() {
		return &list[0];
	}

	const_iterator begin() const {
		return &list[0];
	}

	iterator end() {
		return &list[length];
	}

	const_iterator end() const {
		return &list[length];
	}
private:
	T* list;
	int length;
	int capacity;
	void resize();
};

template <class T>
ArrayList<T>::ArrayList(int initSize) {
	capacity = initSize + SPARE_CAPACITY;
	length = 0;
	list = new T[capacity];
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T> & rhs) {
	this->length = rhs.getLength();
	this->capacity = rhs.capacity;
	this->list = new T [this->capacity];

	for (int i = 0; i < length; ++i) {
		this->list[i] = rhs.list[i];
	}
}

template <class T>
ArrayList<T>::~ArrayList() {
	delete [] this->list;
}

template <class T>
void ArrayList<T>::insert(int pos, const T & data) {
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
void ArrayList<T>::remove(int pos) {
	if (!this->legalPosition(pos, this->getLength()))
		return;
	else if(pos == (getLength() - 1)) { // Removing last element
		this->list[pos] = T();
	}
	else { // Removing first or middle element
		for (int i = pos + 1; i < length; i++) { //shift all elements to the left
			this->list[i-1] = this->list[i];
		}
	}

	this->length--;
}
template <class T>
void ArrayList<T>::deleteByValue(T & data) {
	this->remove(this->find(data));
}

template <class T>
void ArrayList<T>::deleteByValue(T && data) {
	this->remove(this->find(data));
}

template <class T>
int ArrayList<T>::find(T & data) {
	for(T* iter = this->begin(); iter != this->end(); iter++) {
		if (*iter == data) {
			return iter - this->begin();
		}
	}
	return -1;
}

template <class T>
int ArrayList<T>::find(T && data) {
	for(T* iter = this->begin(); iter != this->end(); iter++) {
		if (*iter == data) {
			return iter - this->begin();
		}
	}
	return -1;
}

template <class T>
void ArrayList<T>::set(int pos, const T & data) {
	this->list[pos] = data;
}

template <class T>
T const & ArrayList<T>::get(int pos) const {
	if (!this->legalPosition(pos, this->getLength()))
		return T();
	else
		return this->list[pos];
}

template <class A>
std::ostream & operator<<(std::ostream & os, const ArrayList<A> & list) {
	for(int i = 0; i < list.length; i++) {
		cout << list.list[i] << " ";
	}
	return os;
}

template <class T>
void ArrayList<T>::resize() {
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
