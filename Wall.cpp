#include "Wall.h"
#include <sstream>
#include <string>
#include <vector>

// Destructor deletes data allocated for wallPosts pointer
Wall::~Wall() {
	delete wallPosts;
	this->username.clear(); //not sure if we want to do this or not
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


void Wall::clearWall() {	
	delete wallPosts;
}

// Writes out all WallPosts on the wall to one string
string Wall::toString() {
	string endString = string();
	Node<WallPost>* tmp = this->wallPosts->getHead();
	while (tmp) {
		// data refers to WallPost
		// call toString method of each WallPost
		endString.append(tmp->data.toString());
		//add a separator
		endString.append("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		//Iterate through all WallPosts
		tmp = tmp->next;
	}
	return endString;
}

void Wall::readWallPostsFromString (const string fullWallString) {
	

	//set our between-post separator 
	std::string s = fullWallString;
	std::string nextPostDelimiter = "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	
	size_t substringEndPos;
	std::string token;
	
	while ((substringEndPos = s.find(nextPostDelimiter)) != std::string::npos) {
		token = s.substr(0, substringEndPos);
		addPost(WallPost("content", "author"));
		s.erase(0, substringEndPos + nextPostDelimiter.length());
	}
}











