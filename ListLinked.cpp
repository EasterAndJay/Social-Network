#include "ListLinked.h"

template <class T>
ListLinked::ListLinked(const ListLinked<T> & list) {
// Same copy ctor from DoublyLinkedList
	this->head = NULL;
	this->tail = NULL;
	Node<T>* tmp = doublyLinkedList.head;
	while (tmp) {
		// addToEnd should be changed to insert
		this->addToEnd(tmp->data);
		tmp = tmp->next;
	}
}

template <class T>
ListLinked::~ListLinked() {
	// dtor from DoublyLinkedList
	Node<T>* current = this->head;
	while (current) {
		Node<T>* next = current->next;
		delete current;
		current = next;
	}
}

template <class T>
void ListLinked::insert(int pos, const T & data) {

}

template <class T>
void ListLinked::remove(int pos) {
	
}

template <class T>
void ListLinked::set(int pos, const T & data) {

}

template <class T>
T const & ListLinked::find(const T & data) const{

}

template <class T>
T const & ListLinked::get(int pos) const {

}

template <class T>
bool ListLinked::empty() const {
	if (!this->head)
		return false
	else
		return true
}
