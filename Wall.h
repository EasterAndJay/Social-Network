#ifndef WALL_H
#define WALL_H


#include <iostream>
#include "DoublyLinkedList.h"
#include "WallPost.h"
using namespace std;

class Wall {

public:
	Wall() : wallPosts(new DoublyLinkedList<WallPost>), username(string()){};
	~Wall();

	string getUsername();
	void setUsername(string username_);

	void addPost(WallPost post);
	void deletePost(WallPost post);

	string toString();

	void readWallPostsFromString(string fullWallString);
	
	// Still need to do part f
private:
	DoublyLinkedList<WallPost>* wallPosts;
	string username;
	
};

#endif
