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

void Wall::deleteAllPosts() {//TODO: implement
	
	delete wallPosts;



	/*Node<WallPost>* tmpHead = this->wallPosts->getHead();
	cout << tmpHead->data;
	WallPost postToDelete;
	int i = 0;
	cout << "entering loop:" << endl;
	while(tmpHead) {
		postToDelete = tmpHead->data;
		cout << postToDelete;
		tmpHead = tmpHead->next;
		this->deletePost(postToDelete);
		i++;
		printf ("looped %d times\n", i);
	}*/
}

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
