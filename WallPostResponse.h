#ifndef WALLPOSTRESPONSE_H
#define WALLPOSTRESPONSE_H

#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

class WallPostResponse {
public:
	
	//no arg constructor
	WallPostResponse() : content(string()), author(string()), timePosted(string()) {};
	//2 arg constructor
	WallPostResponse(string content_, string author_) : content(content_), author(author_) {
		setTimePosted();
		timePosted = this->getTimePosted();
	};

	//3 arg constructor
	WallPostResponse(string content_, string author_, string timePosted_) : 
		content(content_), 
		author(author_), 
		timePosted(timePosted_) 
		{};
	

	string getContent() const;
	//void setContent(string content_);
	string getAuthor() const;
	//void setAuthor(string author_);
	string getTimePosted() const;
	void setTimePosted(string customTime);
	void setTimePosted();
	string toString() const;
	

	//friend std::ostream & operator<<(std::ostream & os, const WallPost & wallPost);
private:
	string content;
	string author;
	string timePosted;
};

//bool operator==(const WallPostResponse& left, const WallPostResponse& right);

//bool operator !=(const WallPostResponse& left, const WallPostResponse& right);

#endif
