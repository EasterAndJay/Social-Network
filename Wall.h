#ifndef WALL_H
#define WALL_H
#include <iostream>
#include <vector>
#include "WallPost.h"

using namespace std;

class Wall {

public:
	Wall() : wallPosts(new vector<WallPost>()), username(string()){};
	Wall(const Wall& otherWall);
	~Wall();

	Wall& operator=(const Wall &rhs);

	string getUsername() const;
	void setUsername(string username_);

	void addPost(WallPost post);
	void deletePost(int pos);
	string toString();

	vector<WallPost>* getWallPosts() {return wallPosts;};

	void clearWall();
	void readWallPostsFromString(string fullWallString);
	bool isEmpty();
	
	
private:
	vector<WallPost>* wallPosts;
	string username;
	
};

#endif
