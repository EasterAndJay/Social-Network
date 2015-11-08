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
	ArrayList<T> & operator=(ArrayList<T>& copy);
	ArrayList<T> & operator=(ArrayList<T>&& copy);


	bool insert(int pos, const T & data);
	bool remove(int pos);
	void set(int pos, const T & data);
	T const & get(int pos) const;

	void deleteByValue(T const & data);
	int find(T const & data);

	int getLength() const { return length; }
	void setLength(int i) { length = i; }

	int getCapacity() const { return capacity; }
	T* getList() const { return list; }

	template <class A>
	friend std::ostream & operator<<(std::ostream & os, const ArrayList<A> & list);

	typedef T * iterator;
	typedef const T * const_iterator;

	iterator begin() {
		return list;
	}

	const_iterator begin() const {
		return list;
	}

	iterator end() {
		return &(this->list[length]);
	}

	const_iterator end() const {
		return &(this->list[length]);
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
	this->capacity = rhs.getCapacity();
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
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T>& copy) {
	delete[] list;
	length = copy.length;
	capacity = copy.capacity;
	list = new T [capacity];
	for (int i = 0; i < length; i++) {
		list[i] = copy.list[i];
	}
	return *this;
}

template <class T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T>&& copy) {
	delete[] list;
	length = copy.length;
	capacity = copy.capacity;
	list = new T [capacity];
	for (int i = 0; i < length; i++) {
		list[i] = copy.list[i];
	}
	return *this;
}


template <class T>
bool ArrayList<T>::insert(int pos, const T & data) {
	// If index out of bounds, return false
	if(pos > length || pos < 0)
		return false;

	//T newItem = T(data);

	// If at full capacity, double size
	if (this->length == this->capacity) 
		resize();

	// If inserting at end, simple assignment
	// Also could be case with empty list
	if(pos == length){
		this->list[pos] = data;
	}

	// Else inserting at beginning or middle
	else {
		// Shift everything 1 space to the right
		for (int i = length - 1; i >= pos; i--) {
				this->list[i+1] = this->list[i];
		}
		// Assign new value	
		this->list[pos] = data;
	}
	// Increment length for either case
	this->length++;
	return true;
}

template <class T>
bool ArrayList<T>::remove(int pos) {
	// If index out of bounds, return false
	if (pos > length - 1 || pos < 0)
		return false;

	// If removing last element, just decrement length
	if(pos == (getLength() - 1)) {
		length--;
		return true;
	}
	// Else removing first or middle element
	else {
		// Shift all elements after deleted element 
		// to the left
		for (int i = pos + 1; i < length; i++) {
			this->list[i-1] = this->list[i];
		}
	}
	// Decrement length in both cases
	this->length--;
	return true;
}

template <class T>
void ArrayList<T>::set(int pos, const T & data) {
	// If index out of bounds, do nothing
	if (pos > length - 1 || pos < 0)
		return;
	// Else assign element to new value
	this->list[pos] = data;
}

// Return constant reference to element
// at index pos
template <class T>
T const & ArrayList<T>::get(int pos) const {
	if (pos > length - 1 || pos < 0)
		throw -1;
	return this->list[pos];
}

// Finds index of element based on value
// Then removes
template <class T>
void ArrayList<T>::deleteByValue(T const & data) {
	this->remove(this->find(data));
}

// Finds index of element based on value
// return -1 if not found
template <class T>
int ArrayList<T>::find(T const & data){
	for(T* iter = this->begin(); iter != this->end(); iter++) {
		if (*iter == data) {
			return iter - this->begin();
		}
	}
	return -1;
}

// << operator for cout
template <class A>
std::ostream & operator<<(std::ostream & os, const ArrayList<A> & list) {
	for(int i = 0; i < list.length; i++) {
		cout << list.list[i] << " ";
	}
	return os;
}


// Resize function for growing array
template <class T>
void ArrayList<T>::resize() {
	int newCapacity = (this->capacity + 1) * 2;
	T* newList = new T[newCapacity];
	for (int i = 0; i < this->length; ++i) {
		newList[i] = this->list[i];
	}
	this->capacity = newCapacity;
	delete [] list;
	list = newList;
}

#endif
