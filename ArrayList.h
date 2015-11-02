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

	bool insert(int pos, const T & data);
	bool remove(int pos);
	void set(int pos, const T & data);
	T const & get(int pos) const;

	T* & operator[](int pos);
	const T* & operator[](int pos) const;


	//void deleteByValue(T const & data);
	//int find(T const & data);
	int getLength() const { return length; }
	void setLength(int i) { length = i; }
	int getCapacity() const { return capacity; }
	T** getList() const { return list; }

	typedef T ** iterator;
	typedef const T ** const_iterator;

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

	template <class A>
	friend std::ostream & operator<<(std::ostream & os, const ArrayList<A> & list);
private:
	T** list;
	int length;
	int capacity;
	void resize();
};

/*~User() {
	//delete friends;
	delete friends->getList();

}*/

template <class T>
ArrayList<T>::ArrayList(int initSize) {
	capacity = initSize + SPARE_CAPACITY;
	length = 0;
	list = new T*[capacity];
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T> & rhs) {
	this->length = rhs.getLength();
	this->capacity = rhs.getCapacity();
	this->list = new T* [this->capacity];

	for (int i = 0; i < length; ++i) {
		this->list[i] = new T(*(rhs.list[i]));
	}
}

template <class T>
ArrayList<T>::~ArrayList() {
	
	for(int i = 0; i < length; i++)

		delete list[i];

	delete [] this->list;
}


template <class T>// May not be correct!!
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T> copy) {
	if (this != &copy) {
		if(list != NULL) {
			for (int i = 0; i < length; i++) {
				if(list[i] != NULL)
					delete list[i];
			}
			delete[] list;
		}
		length = copy.length;
		capacity = copy.capacity;
		list = new T*[capacity];
		for (int i = 0; i < length; i++) {
			list[i] = new T(*(copy.list[i]));
		}
	}
	return *this;

}

template <class T>
bool ArrayList<T>::insert(int pos, const T & data) {
	if(pos > length || pos < 0)
		return false;

	if (this->length == this->capacity) // If at full capacity
		resize(); // double size

	if(pos == length){ // If inserting at end
		this->list[pos] = new T(data);
	}

	else { // Else inserting at beginning or middle
			for (int i = length - 1; i >= pos; i--) {
					this->list[i+1] = this->list[i]; // Move everything over 1 space
			}
		this->list[pos] = new T(data); // make pos = data
	}
	this->length++; // increment length
	return true;
}

template <class T>
bool ArrayList<T>::remove(int pos) {
	if (pos > length - 1 || pos < 0)
		return false;

	if(pos == (getLength() - 1)) { // Removing last element
		length--;
		delete this->list[pos];
		this->list[pos] = NULL;
		return true;
	}
	else { // Removing first or middle element
		delete this->list[pos]; // Delete, then shift left
		this->list[pos] = NULL;
		for (int i = pos + 1; i < length; i++) { //shift all elements to the left
			
			this->list[i-1] = this->list[i];
			//this->list[0]
			
		}
	}

	this->length--;
	return true;
}

template <class T>
void ArrayList<T>::deleteByValue(T const & data) {
	this->remove(this->find(data));
}

template <class T>
int ArrayList<T>::find(T const & data){
	for(T** iter = this->begin(); iter != this->end(); iter++) {
		if (**iter == data) {
			return iter - this->begin();
		}
	}
	return -1;
}

template <class T>
void ArrayList<T>::set(int pos, const T & data) {
	if (pos > length - 1 || pos < 0)
		return;
	delete this->list[pos];
	this->list[pos] = new T(data);
}

template <class T>
T const & ArrayList<T>::get(int pos) const {
	if (pos > length - 1 || pos < 0)
		throw -1;
	return *(this->list[pos]);
}

/*template <class T>
T & ArrayList<T>::operator[](int pos) {
	this->legalPosition(pos, this->getLength());
	return this->list[pos];
}

template <class T>
const T & ArrayList<T>::operator[](int pos) const {
	return get(pos);
}*/

template <class A>
std::ostream & operator<<(std::ostream & os, const ArrayList<A> & list) {
	for(int i = 0; i < list.length; i++) {
		cout << *(list.list[i]) << " ";
	}
	return os;
}

template <class T>
void ArrayList<T>::resize() {
	int newCapacity = (this->capacity + 1) * 2;
	T** newList = new T*[newCapacity];
	for (int i = 0; i < this->length; ++i) {
		newList[i] = this->list[i];
	}
	this->capacity = newCapacity;
	delete [] list;
	list = newList;
}

#endif
