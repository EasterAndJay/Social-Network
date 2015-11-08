#ifndef NODE_H
#define NODE_H
#include <iostream>
template <class T> 
struct Node {
	Node(T data) : data(data), next(NULL), prev(NULL){}; //node constructor
	T data;
	Node* next;
	Node* prev;
};

#endif