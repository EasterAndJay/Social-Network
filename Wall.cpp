#include "Wall.h"

// Destructor deletes data allocated for wallPosts pointer
Wall::~Wall() {
	delete wallPosts;
}

string Wall::getUsername() {
	return this->username;
}

void Wall::setUsername(string username_) {
	this->username = username_;
}

// Uses function from DoublyLinkedList template
void Wall::addPost(WallPost post) {
	this->wallPosts->addToEnd(post);
}

void Wall::deletePost(WallPost post) {
	this->wallPosts->deleteByValue(post);
}

void Wall::delteAllPosts() {//TODO: implement}

// Writes out all WallPosts on the wall to one string
string Wall::toString() {
	string endString = string();
	Node<WallPost>* tmp = this->wallPosts->getHead();
	while (tmp) {
		// data refers to WallPost
		// call toString method of each WallPost
		endString.append(tmp->data.toString());
		//Iterate through all WallPosts
		tmp = tmp->next;
	}
	return endString;
}