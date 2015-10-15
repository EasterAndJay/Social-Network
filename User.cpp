#include "User.h"
#include <stdio.h>

User::User(string username_, string password_, string realName_, string city_) {
	Wall* wall = new Wall();
	username = username_;
	wall->setUsername(username_);
	password = password_;
	realName = realName_;
	city = city_;
}

User::~User() {

}


void User::setUsername(string username_) {
	this->username = username_;
}

string User::getUsername(){
	return this->username;
}

void User::setRealName(string realName_){
	this->realName = realName_;
}

string User::getRealName(){
	return this->realName;
}

void User::setCity(string city_){
	this->city = city;
}

string User::getCity(){
	return this->city;
}

void User::setPassword(string password_){ //FBI level security
	this->password = password_;
}
bool User::checkPassword (string password_){
	if (this->password == password_) {return true;}
	else {return false;}
}
	 
void User::addPost(WallPost post_){
	this->wall->addPost(post_);
}
void User::deletePost(WallPost post_) {
	this->wall->deletePost(post_);
}

string User::toString() {
	return "";
}

void User::loadUserFromString() {
}
