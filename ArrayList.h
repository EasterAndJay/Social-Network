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
	ArrayList<T> & operator=(ArrayList<T> copy);

	void insert(int pos, const T & data);
	void remove(int pos);
	void set(int pos, const T & data);
	T const & get(int pos) const;

	T & operator[](int pos);
	const T & operator[](int pos) const;


	void deleteByValue(T const & data);
	int find(T const & data);
	int getLength() const { return length; }

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

	template <class A>
	friend std::ostream & operator<<(std::ostream & os, const ArrayList<A> & list);
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
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T> copy) {
	std::swap(*this,copy);
	return *this;
}

template <class T>
void ArrayList<T>::insert(int pos, const T & data) {
	this->legalPosition(pos, this->length+1);

	if (this->length == this->capacity) // If at full capacity
		resize(); // double size
	T copy = data;
	if(pos == length){ // If inserting at end
		
		this->list[pos] = copy;
	}

	else { // Else inserting at beginning or middle
		for (int i = length - 1; i >= pos; i--) {
			this->list[i+1] = this->list[i]; // Move everything over 1 space
		}

		this->list[pos] = copy; // make pos = data
	}
	this->length++; // increment length
}

template <class T>
void ArrayList<T>::remove(int pos) {
	this->legalPosition(pos, this->getLength());
	if(pos == (getLength() - 1)) { // Removing last element
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
void ArrayList<T>::deleteByValue(T const & data) {
	this->remove(this->find(data));
}

template <class T>
int ArrayList<T>::find(T const & data){
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
	this->legalPosition(pos, this->getLength());
	return this->list[pos];
}

template <class T>
T & ArrayList<T>::operator[](int pos) {
	this->legalPosition(pos, this->getLength());
	return this->list[pos];
}

template <class T>
const T & ArrayList<T>::operator[](int pos) const {
	return get(pos);
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
