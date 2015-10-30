#ifndef ABSTRACTLIST_H
#define ABSTRACTLIST_H
#include "Node.h"
#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class AbstractList {
public:
	virtual ~AbstractList() {}
	virtual void insert(int pos, const T & item)=0;
	virtual void remove(int pos)=0;
	virtual void set(int pos, const T & item)=0;
	virtual T const & get (int pos)const=0;

	void legalPosition(int pos, int length) const;
};

template <class T>
void AbstractList<T>::legalPosition(int pos, int length) const {
	if (pos < 0) {
		std::cout << "Tried to access negative index" << std::endl;
		exit(1);
	}
	else if (pos >= length) {
		std::cout << "Tried to access index past length = " << length << std::endl;
		exit(1);
	}
	else
		return;
}

#endif
