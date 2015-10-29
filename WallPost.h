#ifndef WALLPOST_H
#define WALLPOST_H

#include <iostream>
#include <time.h>

using namespace std;

class WallPost {
public:
	
	//no arg constructor
	WallPost() : content(string()), author(string()), timePosted(string()) {};
	//2 arg constructor
	WallPost(string content_, string author_) : content(content_), author(author_) {
		setTimePosted();
		timePosted = this->getTimePosted();
	};
	//3 arg constructor
	WallPost(string content_, string author_, string timePosted_) : content(content_), author(author_), timePosted(timePosted_) {};
	
	
	/*~WallPost() { //not sure if we need this but instructions called for one
		content.clear();
		author.clear();
		timePosted.clear();
	};*/
	
	WallPost(const WallPost& wallPost);
	~WallPost();
	string getContent() const;
	void setContent(string content_);
	string getAuthor() const;
	void setAuthor(string author_);
	string getTimePosted() const;
	void setTimePosted(string customTime);
	void setTimePosted();
	string toString() const;
	

	friend std::ostream & operator<<(std::ostream & os, const WallPost & wallPost);
private:
	string content;
	string author;
	string timePosted;
};

bool operator==(const WallPost& left, const WallPost& right);

bool operator !=(const WallPost& left, const WallPost& right);

#endif
