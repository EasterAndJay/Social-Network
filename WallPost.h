#ifndef WALLPOST_H
#define WALLPOST_H

#include <iostream>
#include <time.h>

using namespace std;

class WallPost {
public:
	
	WallPost() : content(string()), author(string()), timePosted(string()) {};
	WallPost(string content_, string author_) : content(content_), author(author_) {
		setTimePosted();
		timePosted = this->getTimePosted();
	};
	
	WallPost(const WallPost& wallPost);
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
