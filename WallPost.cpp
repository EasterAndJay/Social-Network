#include "WallPost.h"
#include "time.h"


string WallPost::getContent() const{
	return this->content;
}

void WallPost::setContent(string content_) {
	this->content = content_;
}

string WallPost::getAuthor() const{
	return this->author;
}

void WallPost::setAuthor(string author_) {
	this->author = author_;
}

string WallPost::getTimePosted() const{
	return this->timePosted;
}

void WallPost::setTimePosted() {
	time_t timeNow = time(NULL); //get time now
	//convert time to string
	struct tm *ptr = localtime(&timeNow);
	char buffer[80];
	strftime(buffer,80,"%d-%m-%Y %I:%M:%S", ptr);
	
	this->timePosted = buffer;
}

void WallPost::setTimePosted(string customTime) {
	this->timePosted = customTime;
}

void WallPost::addResponse(WallPostResponse response_){
	this->responses.insert(responses.end(),response_);
}

void WallPost::deleteResponse(int pos){
	this->responses.erase(responses.begin() + pos);
}

vector<WallPostResponse> WallPost::getResponses() {
	return this->responses;
}

/*
int WallPost::findResponse(WallPostResponse response_) {
	int i = 0;
	for(auto iter = this->responses.begin(); iter != this->responses.end(); iter++) {
		if (iter->getUsername() == username_)
			return i;
		i++;
	}
	return -1;
}*/

string WallPost::toString() const{
	string endString = "On " + this->timePosted + "\n" + 
	this->author + " wrote:\n" + 
	
	//if (this->responses.size() > 0) {
		this->content + "\nResponses:\n";
		for (int i = 0; i < this->responses.size(); i++) {
			endString += responses.at(i).toString();
			endString += "\n********************************\n";
		}
	//}
	return endString;
}

std::ostream & operator<<(std::ostream & os, const WallPost & wallPost) {
	os << wallPost.toString();
	return os;
}

bool operator==(const WallPost& left, const WallPost& right) {
	return (left.getContent() == right.getContent() 
			&& left.getAuthor() == right.getAuthor() 
			&& left.getTimePosted() == right.getTimePosted());
}

bool operator !=(const WallPost& left, const WallPost& right) {
	return !(left == right);
}
