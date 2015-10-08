#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>
using namespace std;

// Contains interface and implementation of DoublyLinkedList template

template <class T> 
struct Node {
	Node(T data) : data(data), next(NULL), prev(NULL){}; //node constructor
	T data;
	Node* next;
	Node* prev;
};

template <class T>
class DoublyLinkedList {
public:
	DoublyLinkedList() : head(NULL), tail(NULL){}     //no arg constructor
	DoublyLinkedList(const DoublyLinkedList<T> & doublyLinkedList);
	~DoublyLinkedList();

	Node<T>* getHead(); //returns pointer to head
	void addToEnd(T const& data); 
	void deleteByValue(T data);

	template <class A>
	friend std::ostream & operator<<(std::ostream & os, const DoublyLinkedList<A> & doublyLinkedList); 
private:
	Node<T>* head;
	Node<T>* tail;
};

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node<T>* tmp = NULL;
	while (head) {
		tmp = this->head;
		head = this->head->next;
		delete tmp;
	}
}

template<class T>
Node<T>* DoublyLinkedList<T>::getHead() {
	return this->head;
}

// Takes some data, creates a new node with that data, appends new node to tail
// new node then becomes new tail
template <class T>
void DoublyLinkedList<T>::addToEnd(T const& data) {
	Node<T>* newNode = new Node<T>(data);
	if (this->head == NULL) {
		this->head = newNode;
		this->tail = newNode;
	}
	else {
		this->tail->next = newNode;
		newNode->prev = this->tail;
		this->tail = newNode;
	}
}

// Finds first node with matching data, deletes it, connects the nodes
// Surrounding the node that was just deleted
template <class T>
void DoublyLinkedList<T>::deleteByValue(T data) {
	Node<T>* tmp = this->head;

	// Iterate until tmp = node to be deleted
	while (tmp && tmp->data != data) {
		tmp = tmp->next;
	}

	// If node to be deleted exists
	if (tmp) {
		// If tmp is not the head and not the tail
		if (tmp->prev && tmp->next) {
			// Connect the nodes on either side of the node to be deleted
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
		}
		// If tmp is the head
		else if (tmp->next) {
			tmp->next->prev = tmp->prev;
			this->head = tmp->next;
		}
		// If tmp is tail
		else if (tmp->prev) {
			tmp->prev->next = tmp->next;
			this->tail = tmp->prev;
		}
		delete tmp;
	}
}

// Copy constructor. Performs a deep copy
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& doublyLinkedList) {
	this->head = NULL;
	this->tail = NULL;
	Node<T>* tmp = doublyLinkedList.head;
	while (tmp) {
		this->addToEnd(tmp->data);
		tmp = tmp->next;
	}
}

// Overload of << operator for easy writing of list to cout
template <class A>
std::ostream & operator<<(std::ostream & os, const DoublyLinkedList<A> & doublyLinkedList) {
	Node<A>* tmp = doublyLinkedList.head;
	while (tmp) {
		os << tmp->data << " ";
		tmp = tmp->next;
	}
	return os;
}
#endif
