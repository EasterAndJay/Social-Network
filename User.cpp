#include "User.h"

User::User(string username_, string password_, string realName_, string city_) {
	this->wall = new Wall();
	this->setUsername(username_);
	this->wall->setUsername(username_); //also set the wall's username attribute
	this->setPassword(password_);
	this->setRealName(realName_);
	this->setCity(city_);
}


User::~User() {
	//delete wall;
}
	
User::setUsername(string username_) {

}

string User::getUsername(){
}
User::setRealName(string realName_){
}
User::getRealName(){
}
User::setCity(string city_){
}
User::getCity(string city_){
}

void User::setPassword(string password_){ //FBI level security
}
bool User::checkPassword (string password_){
}
	 
void User::addPost(WallPost post_){
}
void User::deletePost(WallPost post_) {
}

string User::toString() {
}

void User::loadUserFromString() {
}
