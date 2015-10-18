#ifndef WALL_H
#define WALL_H


#include <iostream>
#include "DoublyLinkedList.h"
#include "WallPost.h"
using namespace std;

class Wall {

public:
	Wall() : wallPosts(new DoublyLinkedList<WallPost>), username(string()){ };
	Wall(const Wall& otherWall);
	~Wall();

	string getUsername() const;
	void setUsername(string username_);

	void addPost(WallPost post);
	void deletePost(WallPost post);
	string toString();

	void readWallPostsFromString(string fullWallString);
	bool isEmpty();
	
	
private:
	DoublyLinkedList<WallPost>* wallPosts;
	string username;
	
};

#endif
