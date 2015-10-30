#ifndef USERNETWORK_H
#define USERNETWORK_H

#include "DoublyLinkedList.h"
#include "User.h"


class UserNetwork {
	
public:
	UserNetwork() : users(new ArrayList<User>) {};
	UserNetwork(const UserNetwork& network);
	~UserNetwork();

	UserNetwork& operator=(UserNetwork copy);

	bool userAlreadyExists(string username);
	void addUser(User user); //make sure no duplicate usernames
	void deleteUser(User user); //make sure user in fact exists before deleting
	int findUser(string username_);
	ArrayList<User>* getUsers();

	string toString();
	void readUserNetworkFromString(string fullNetworkString_);
	void toFile();
	void readFromFile();


private:
	ArrayList<User>* users;

};


#endif
