#include "Wall.h"
#include <sstream>
#include <string>
#include <vector>


Wall::Wall(const Wall& otherWall) {
	this->username = otherWall.getUsername();
	this->wallPosts = new ArrayList<WallPost>(*(otherWall.wallPosts));
}

Wall::~Wall() {

}

Wall& Wall::operator=(const Wall &rhs)
{
	username = rhs.getUsername();
	wallPosts = rhs.wallPosts;
}

string Wall::getUsername() const {
	return this->username;
}

void Wall::setUsername(string username_) {
	this->username = username_;
}

// Uses function from ArrayList template
void Wall::addPost(WallPost post) {
	this->wallPosts->insert(0,post); // Inserts post at front of wall
}

void Wall::deletePost(int pos) {
	this->wallPosts->remove(pos);
}


// Writes out all WallPosts on the wall to one string
// TEST
string Wall::toString() {
	string endString = string();

	for (int i = 0; i < this->wallPosts->getLength(); i++) {
		
		// data refers to WallPost
		// call toString method of each WallPost
		endString.append(this->wallPosts->get(i).toString());
		//add a separator
		endString.append("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		//Iterate through all WallPosts
	}
	return endString;
}

void Wall::readWallPostsFromString (const string fullWallString_) {
	delete this->wallPosts;
	wallPosts = new ArrayList<WallPost>;

	//set our between-post separator 
	std::string fullWallString = fullWallString_;
	std::string nextPostDelimiter = "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	
	
	//initialize some position markers and strings to hold results
	size_t postEndPos, timeEndPos, authorEndPos;
	std::string post, content, author, time;
	
	//loop through full posts (looking for our big delimiter)
	while ((postEndPos = fullWallString.find(nextPostDelimiter)) != std::string::npos) {
		post = fullWallString.substr(0, postEndPos);
			//now we have a full post, time to grab our date string from between "On" and "\n"
			timeEndPos = post.find("\n");
			time = post.substr(3, timeEndPos - 3);
			post.erase(0, timeEndPos + 1); //add 1 to remove our "\n" delimiter too
			//now we pull the author
			authorEndPos = post.find(" wrote:\n");
			author = post.substr(0, authorEndPos);
			post.erase(0, authorEndPos + 8); // add 8 because " wrote:\n" is 8 characters long
			// content is just what is left over in post now that we've stripped the rest
			content = post;
			
			addPost(WallPost(content, author, time));
			
		fullWallString.erase(0, postEndPos + nextPostDelimiter.length());
	}
}

bool Wall::isEmpty() {
	if (this->wallPosts->getLength() == 0) {
		return true;
	}
	else {
		return false;
	}
}










