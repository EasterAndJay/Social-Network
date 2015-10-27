#ifndef ABSTRACTLIST_H
#define ABSTRACTLIST_H
#include "Node.h"
using namespace std;
#include <iostream>

template <class T>
class AbstractList {
public:
	virtual ~AbstractList() {}
	virtual void insert(int pos, const T & item)=0;
	virtual void remove(int pot)=0;
	virtual void set(int pos, const T & item)=0;
	virtual T const & get (int pos)const=0;
	virtual bool empty() const=0;
	bool legalPosition(int pos, int length) const{
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
};

#endif