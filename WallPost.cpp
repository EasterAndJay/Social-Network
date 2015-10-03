#include "WallPost.h"

WallPost::WallPost(const WallPost& wallPost) {
	this->author = string(wallPost.getAuthor());
	this->content = string(wallPost.getContent());
	this->timePosted = string(wallPost.getTimePosted());
}

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

void WallPost::setTimePosted(string timePosted_) {
	this->timePosted = timePosted_;
}

string WallPost::toString() const{
	string endString = string("\n").append(this->author);
	endString.append(" wrote:\n").append(this->content).append("\n");
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