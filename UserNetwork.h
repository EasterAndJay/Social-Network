#ifndef USERNETWORK_H
#define USERNETWORK_H

#include "DoublyLinkedList.h"
#include "User.h"


class UserNetwork {
	
public:
	UserNetwork() : users(new DoublyLinkedList<User>) {};
	UserNetwork(const UserNetwork& network);
	~UserNetwork();

	bool userAlreadyExists(string username);
	void addUser(User user); //make sure no duplicate usernames
	void deleteUser(User user); //make sure user in fact exists before deleting
	User findUser(string username_);
	string toString();
	void readUserNetworkFromString(string fullNetworkString_);
	void toFile();
	void readFromFile();


private:
	DoublyLinkedList<User>* users;

};


#endif
