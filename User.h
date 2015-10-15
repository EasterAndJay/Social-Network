#ifndef USER_H
#define USER_H


#include <iostream>
#include "DoublyLinkedList.h"
#include "Wall.h"
using namespace std;

class User {

public:

	/*User(string username_, string password_, string realName_, string city_) : username(username_), password(password_), realName(realName_), city(city_), wall(new Wall()) {
		this->wall->setUsername(username_); //set the contained wall's username after creation
		
	};*/
	
	User(string username_, string password_, string realName_, string city);
	~User();
	
	void setUsername(string username_);
	string getUsername();
	void setRealName(string realName_);
	string getRealName();
	void setCity(string city_);
	string getCity();
	
	void setPassword(string password_); //FBI level security 
	bool checkPassword (string password_);
	 
	void addPost(WallPost post_);
	void deletePost(WallPost post_);
	
	string toString();
	void loadUserFromString(const string userString_);


private:
	
	Wall* wall;
	string username;
	string password;
	string realName;
	string city;

};

#endif
