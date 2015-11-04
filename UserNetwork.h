#ifndef USERNETWORK_H
#define USERNETWORK_H

#include "User.h"

class User;
class UserNetwork {
	
public:
	UserNetwork() : users(new ArrayList<User>) {};
	UserNetwork(const UserNetwork& network);
	~UserNetwork();

	UserNetwork& operator=(UserNetwork copy);

	bool userAlreadyExists(string username);
	void addUser(User user); //make sure no duplicate usernames //was const
	void deleteUser(int i);
	int findUser(string username_) ;
	ArrayList<User>* getUsers();

	string toString();
	void readUserNetworkFromString(string fullNetworkString_);
	void toFile();
	void readFromFile();

	void howManyFriendsUsersHave();

	void createFriendship(int requestorIndex, int acceptorIndex);
	void sendFriendRequest(int requestorIndex, int acceptorIndex); 


private:
	ArrayList<User>* users;

};


#endif
