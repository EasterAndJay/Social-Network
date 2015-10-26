#ifndef LISTLINKED_H
#define LISTLINKED_H
#include "AbstractList.h"
#include "Node.h"

template <class T>
class ListLinked : public List {
public:
	// no arg ctor
	ListLinked() : head(NULL), tail(NULL) {}
	// copy ctor
	ListLinked(const ListLinked<T> & list);
	// dtor
	~ListLinked();

	// rest of function declarations inherited from AbstractList.h

private:
	Node<T> * head;
	Node<T> * tail;
};

#endif