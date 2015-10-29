#ifndef WALL_H
#define WALL_H
#include <iostream>
#include "ArrayList.h"
#include "WallPost.h"

using namespace std;

class Wall {

public:
	Wall() : wallPosts(new ArrayList<WallPost>), username(string()){};
	Wall(const Wall& otherWall);
	~Wall();

	string getUsername() const;
	void setUsername(string username_);

	void addPost(WallPost post);
	void deletePost(int pos);
	string toString();

	void readWallPostsFromString(string fullWallString);
	bool isEmpty();
	
	
private:
	ArrayList<WallPost>* wallPosts;
	string username;
	
};

#endif
