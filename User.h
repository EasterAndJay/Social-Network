#ifndef USER_H
#define USER_H


#include <iostream>
#include "DoublyLinkedList.h"
#include "Wall.h"

class User {

public:

	User(string username_, string password_, string realName_, string city_);  //set the contained wall's username after creation
	~User();
	
	void setUsername(string username_);
	string getUsername();
	void setRealName(string realName_);
	string getRealName();
	void setCity(string city_);
	string getCity(string city_);
	
	void setPassword(string password_); //FBI level security 
	bool checkPassword (string password_);
	 
	void addPost(string content_);
	void deletePost(WallPost post_);
	
	string toString();
	void loadUserFromString();
	


private:
	
	Wall* wall;
	string username;
	string password;
	string realName;
	string city;

};

#endif
