#ifndef USERNETWORK_H
#define USERNETWORK_H

#include "User.h"
#include <vector>

class User;
class UserNetwork {
	
public:
	UserNetwork() : users(new vector<User>) {};
	UserNetwork(const UserNetwork& network);
	~UserNetwork();

	UserNetwork& operator=(UserNetwork copy);

	bool userAlreadyExists(string username);
	void addUser(User user); //make sure no duplicate usernames //was const
	void deleteUser(int i);
	int findUser(string username_) ;
	vector<User>*& getUsers();

	string toString();
	void readUserNetworkFromString(string fullNetworkString_);
	void toFile();
	void readFromFile();

	void findShortestPath(User& source, User& target);
	void findUsersWithinThreeDegrees(User& source);

private:
	vector<User>* users;

};


#endif
