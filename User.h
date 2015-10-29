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
	
	User() : username(string()), password(string()), realName(string()), city(string()), wall(new Wall()), friends(new ArrayList<string>()), friendRequests(new ArrayList<string>()) {};
	User(string username_, string password_, string realName_, string city);
	User(const string userString_);
	~User();
	
	User(const User& user);
	void setUsername(string username_);
	string getUsername() const;
	void setRealName(string realName_);
	string getRealName()const;
	void setCity(string city_);
	string getCity() const;
	
	//solely made these for the copy constructor to use, don't actually want them
	Wall* getWall() const;
	string getPassword() const;
	
	void setPassword(string password_); //FBI level security 
	bool checkPassword (string password_);
	 
	void addPost(WallPost post_);
	void deletePost(int pos);
	
	string toString();
	//void readUserFromString(string userString_);
	
	//getters and setters for friends and friendRequests arrays
	ArrayList<string>* getFriendRequests() const;
	void setFriendRequests(ArrayList<string> const & friendRequests_);
	
	ArrayList<string>* getFriends() const;
	void setFriends(ArrayList<string> const & friends_);
	
	//methods for Friends and Friend Requests
	void deleteFriend(User& friendToDelete);
	
	void sendFriendRequest(User& potentialFriend);   //not sure whether to use pointer or not for these
	void acceptFriendRequest(User& friendToAccept); //could call a helper addfriend
	void deleteFriendRequest(User& friendToDelete);
	


private:
	
	Wall* wall;
	ArrayList<string>* friends;
	ArrayList<string>* friendRequests;
	string username;
	string password;
	string realName;
	string city;

};

bool operator==(const User& left, const User& right);
bool operator !=(const User& left, const User& right);

#endif
