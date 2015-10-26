#ifndef ABSTRACTLIST_H
#define ABSTRACTLIST_H

template <class T>
class List {
public:
	virtual void insert(int pos, const T & item)=0;
	virtual void remove(int pot)=0;
	virtual void set(int pos, const T & item)=0;
	virtual T const & find(const T & item) const=0;
	virtual T const & get (int pos) const=0;
	virtual bool empty() const=0;
};

#endif