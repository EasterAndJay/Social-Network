#include "WallPostResponse.h"
#include "time.h"


string WallPostResponse::getContent() const{
	return this->content;
}

/*void WallPostResponse::setContent(string content_) {
	this->content = content_;
}*/

string WallPostResponse::getAuthor() const{
	return this->author;
}
/*
void WallPostResponse::setAuthor(string author_) {
	this->author = author_;
}
*/

string WallPostResponse::getTimePosted() const{
	return this->timePosted;
}

void WallPostResponse::setTimePosted() {
	time_t timeNow = time(NULL); //get time now
	//convert time to string
	struct tm *ptr = localtime(&timeNow);
	char buffer[80];
	strftime(buffer,80,"%d-%m-%Y %I:%M:%S", ptr);
	
	this->timePosted = buffer;
}

void WallPostResponse::setTimePosted(string customTime) {
	this->timePosted = customTime;
}

string WallPostResponse::toString() const{
	string endString = "On " + this->timePosted + "\n" + 
	this->author + " responded:\n" + 
	this->content;

	return endString;
}

/*
bool operator==(const WallPostResponse& left, const WallPostResponse& right) {
	return (left.getContent() == right.getContent() 
			&& left.getAuthor() == right.getAuthor() 
			&& left.getTimePosted() == right.getTimePosted());
}

bool operator !=(const WallPostResponse& left, const WallPostResponse& right) {
	return !(left == right);
}*/