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
	void remove(int pos);
	void set(int pos, const T & item);
	T const & get (int pos)const;
	
	Node<T>* getHead() const;
	int getLength() const;

	template <class A>
	friend std::ostream & operator<<(std::ostream & os, const ListLinked<A> & list);
private:
	Node<T> * head;
	Node<T> * tail;
	int length;
};

template <class T>
ListLinked<T>::ListLinked(const ListLinked<T> & list) {
	this->head = NULL;
	this->tail = NULL;
	this->length = 0;
	Node<T>* tmp = list.getHead();
	for(int i = 0; i < list.length; i++) {
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
	if (!this->legalPosition(pos, this->getLength()))
		return;
	Node<T>* tmp = this->getHead();
	for (int i = 0; i < pos; i++) {
		tmp = tmp->next;
	}
	tmp->data = data;
	return;
}

template <class T>
T const& ListLinked<T>::get(int pos) const {
	if (!this->legalPosition(pos, this->length))
		return NULL;
	Node<T>* tmp = this->getHead();
	for(int i = 0; i < pos; i++) {
		tmp = tmp->next;
	}
	return tmp->data;
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
int ListLinked<T>::getLength() const {
	return this->length;
}

#endif