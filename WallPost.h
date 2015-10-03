#ifndef WALLPOST_H
#define WALLPOST_H

#include <iostream>

using namespace std;

class WallPost {
public:
	WallPost() : content(string()), author(string()), timePosted(string()) {};
	WallPost(string content_, string author_, string timePosted_) : content(content_), author(author_), timePosted(timePosted_) {};
	WallPost(const WallPost& wallPost);
	string getContent() const;
	void setContent(string content_);
	string getAuthor() const;
	void setAuthor(string author_);
	string getTimePosted() const;
	void setTimePosted(string timePosted_);
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