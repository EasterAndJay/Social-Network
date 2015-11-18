#ifndef USER_H
#define USER_H


#include <iostream>
#include <vector>
#include "Wall.h"
#include "UserNetwork.h"

using namespace std;

class UserNetwork;

class User {

public:
	
	User() : 
		username(string()),
		password(string()), 
		realName(string()), 
		city(string()), 
		wall(new Wall())
		{ this->wall->setUsername(username); };

	User(string username_, string password_, string realName_, string city);
	User(const string userString_);
	~User();

	User(const User& user);

	User& operator=(const User& rhs);

	void setUsername(string username_);
	string getUsername() const;
	void setRealName(string realName_);
	string getRealName()const;
	void setCity(string city_);
	string getCity() const;

	Wall* getWall() const;
	string getPassword() const;
	
	void setPassword(string password_); 
	//bool checkPassword (string password_);
	 
	void addPost(WallPost post_);
	void deletePost(int pos);
	void addResponse(int pos, WallPostResponse response_);
	void deleteResponse(int postPos, int responsePos);
	
	string toString() const;
	string friendsToString() const;
	string friendRequestsToString() const;
	void readUserFromString(string userString_);
	//void loadFriendsFromString(string friendString, const UserNetwork& MyNetwork);
	
	//getters and setters for friends and friendRequests arrays
	vector<string> getFriendRequests() const;
	void setFriendRequests(vector<string> friendRequests_);
	
	vector<string> getFriends() const;
	void setFriends(vector<string> friends_);
	
	//methods for Friends and Friend Requests
	void deleteFriend(string usernameOfFriendToDelete, UserNetwork* myNetwork);

	void sendFriendRequest(string potentialFriendUsername, UserNetwork* myNetwork);

	void acceptFriendRequest(string usernameToAdd, UserNetwork* myNetwork);
	void addFriend(string newFriend);
	void addFriendRequest(string newFriendRequestUsername);
	void deleteFriendRequest(int index);
	void deleteFriendRequest(string usernameOfFriendToDelete, UserNetwork* myNetwork);
	

	int dist = -1;
	string path = "";

private:

	string username;
	string password;
	string realName;
	string city;
	Wall* wall;
	vector<string> friends = vector<string>();
	vector<string> friendRequests = vector<string>();

};

bool operator==(const User& left, const User& right);
bool operator !=(const User& left, const User& right);

#endif
