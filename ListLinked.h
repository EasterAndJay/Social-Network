#ifndef LISTLINKED_H
#define LISTLINKED_H
#include "AbstractList.h"


template <class T>
class ListLinked : public AbstractList<T> {
public:
	// no arg ctor
	ListLinked() : head(NULL), tail(NULL), length(0) {}
	// copy ctor
	ListLinked(const ListLinked<T> & list);
	// dtor
	~ListLinked();

	void insert(int pos, const T & item);
	void remove(int pot);
	void set(int pos, const T & item);
	Node<T>* find(const T & item) const;
	T const & get (int pos)const;
	bool empty() const;
	Node<T>* getHead() const;
	int getLength() const;
	template <class A>
	friend std::ostream & operator<<(std::ostream & os, const ListLinked<A> & list);
	// rest of function declarations inherited from AbstractList.h
private:
	Node<T> * head;
	Node<T> * tail;
	int length;
	bool legalPosition(int pos, int length) const;

	class const_iterator {
	public:
		const_iterator(): current{ nullptr } {}

		const T & operator*() const
		{ return retrieve(); }

		const_iterator & operator++() {
			current = current->next;
			return *this;
		}

		const_iterator operator++ (int) {
			const_iterator old = *this;
			++(*this);
			return old;
		}

		bool operator== (const const_iterator & rhs) const {
			return current == rhs.current;
		}

		bool operator!= (const const_iterator & rhs) const {
			return !(*this == rhs);
		}
	private:
		Node<T>* current;

		T & retrieve() const {
			return current->data;
		}

		const_iterator(Node<T>* p): current { p } {}
		friend class ListLinked<T>;
	};

	class iterator : const_iterator {
	public:
		iterator() {}
		T & operator* () {
			return const_iterator::retrieve();
		}
		const T & operator* () const {
			return const_iterator::operator*();
		}

		iterator& operator++ (int) {
			iterator old = *this;
			++(*this);
			return old;
		}

	protected:
		iterator( Node<T>* p) : const_iterator { p } {}
		friend class ListLinked<T>;
	};
};

template <class T>
ListLinked<T>::ListLinked(const ListLinked<T> & list) {
// Same copy ctor from DoublyLinkedList
	this->head = NULL;
	this->tail = NULL;
	this->length = 0;
	Node<T>* tmp = list.getHead();
	for(int i = 0; i < list.length; i++) {
		// addToEnd should be changed to insert
		this->insert(i, tmp->data);
		tmp = tmp->next;
	}
	this->length = list.getLength();
}

template <class T>
ListLinked<T>::~ListLinked() {
	// dtor from DoublyLinkedList
	Node<T>* current = this->head;
	while (current) {
		Node<T>* next = current->next;
		delete current;
		current = next;
	}
}

template <class T>
void ListLinked<T>::insert(int pos, const T & data) {
	// pos can be between 0 and length of list
	if (!this->legalPosition(pos, this->getLength()+1)) {
		return; // Print error and return if
				// position out of range
	}
	Node<T>* tmp = this->getHead();
	Node<T>* newNode = new Node<T>(data);
	if (pos == 0) { // if inserting at front
		if (this->length == 0) { // list is empty
			head = tail = newNode;
			head->next = tail;
			tail->prev = head;
			tail->next = head->prev = nullptr;
		
		}
		else {
			newNode->next = head;
			head->prev = newNode;
			this->head = newNode;
		}
		
	}
	else if(pos == this->getLength()) {// inserting at back
		tail->next = newNode;
		newNode->prev = tail;
		newNode->next = nullptr;
		tail = newNode;
	}
	else { // general case
		for (int i = 0; i < pos-1; i++) {
			tmp = tmp->next;
		}

		newNode->next = tmp->next;
		newNode->next->prev = newNode;
		newNode->prev = tmp;
		tmp->next = newNode;
	}
	length++;
}

template <class T>
void ListLinked<T>::remove(int pos) {
	if (!this->legalPosition(pos, this->length))
		return; // Print error and return if
				// Position out of range.
				// Checks if list is empty.
	if (this->length == 1) { // Case where deleting 1 node list
		delete this->head;
		head = tail = nullptr;
	}
	else if (pos == 0) { // Case where deleting current head
		Node<T>* tmp = this->getHead();
		this->head->next->prev = nullptr;
		this->head = tmp->next; // Update head
		delete tmp; // delete head
	}

	else if (pos == this->length-1) { // Case where deleting tail
		Node<T>* tmp = tail; // tmp = tail
		this->tail = tmp->prev; // update tail
		this->tail->next = nullptr;
		delete tmp;
	}
	else {
		Node<T>* tmp = this->getHead();
		for(int i = 0; i < pos - 1; i++) {
			tmp = tmp->next;
		} // tmp now points to node right before one to be deleted

		Node<T>* deleteNode = tmp->next;
		tmp->next = deleteNode->next; // update tmp->next
		tmp->next->prev = tmp; // update tmp->next->prev
		delete deleteNode;
	}
	length--;
}

template <class T>
void ListLinked<T>::set(int pos, const T & data) {
	Node<T>* toSet = this->find(pos);
	if(toSet)
		toSet->data = data;
}

template <class T>
Node<T>* ListLinked<T>::find(const T & data) const{
	Node<T>* tmp = this->getHead();
	while(tmp) {
		if (tmp->data == data)
			return tmp;
	}
	return nullptr;
}

template <class T>
T const& ListLinked<T>::get(int pos)const {
	if(!this->legalPosition(pos, this->length))
		return NULL;
	Node<T>* tmp = this->getHead();
	for(int i = 0; i < pos; i++) {
		tmp = tmp->next;
	}

	return tmp->data;
}

template <class T>
bool ListLinked<T>::empty() const {
	if (!this->getHead())
		return false;
	else
		return true;
}

template <class A>
std::ostream & operator<<(std::ostream & os, const ListLinked<A> & list) {
	Node<A>* tmp = list.getHead();
	if (!tmp)
		cout << "List is empty";
	while (tmp) {
		os << tmp->data << " ";
		tmp = tmp->next;
	}
	return os;
}

template <class T>
Node<T>* ListLinked<T>::getHead() const {
	return this->head;
}
template <class T>
bool ListLinked<T>::legalPosition(int pos, int length) const{
	if (pos < 0) {
		std::cout << "Tried to use index < 0" << std::endl;
		return false;
	}
	else if (pos >= length) {
		std::cout << "Tried to access index past length = " << length << std::endl;
		return false;
	}
	else
		return true;
}

template <class T>
int ListLinked<T>::getLength() const {
	return this->length;
}

#endif