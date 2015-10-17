#include "UserNetwork.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

//Simple destructor
UserNetwork::~UserNetwork () {
	delete users;	
}


// Returns user if found.
// If not found, returns empty user.
User UserNetwork::findUser(string username_) {
	Node<User>* currentUser = this->users->getHead();
	while (currentUser) {
		if (currentUser->data.getUsername() == username_)
			return currentUser->data;
		currentUser = currentUser->next;
	}
	return User();
}

//Helper method to make sure there are no duplicate users before adding
bool UserNetwork::userAlreadyExists(string username) {
	//start peekUser pointer at the head of users
	Node<User>* peekUser = this->users->getHead();
	//loop through and check against input argument username
	while (peekUser) {
		if (peekUser->data.getUsername() == username) {
			//printf("user found\n");
			return true;
		}
		peekUser = peekUser->next;
	}

	//printf("user not found\n");
	return false;
}

void UserNetwork::addUser(User user) { //make sure no duplicates
	if (userAlreadyExists(user.getUsername())) {
		//printf("Sorry, a user already exists with this username\n");
	} else {
		this->users->addToEnd(user);
		//printf("User Added Successfully\n");
	}
}

void UserNetwork::deleteUser(User user){ //make sure user in fact exists before deleting
	if (userAlreadyExists(user.getUsername())) {
		this->users->deleteByValue(user);
		printf("Deleted successfully\n");
	} else {
		printf("No matching user found to delete\n");
	}

}


string UserNetwork::toString() {
	string endString = string();
	
	Node<User>* currentUser = this->users->getHead();
	while (currentUser) {
		endString.append(currentUser->data.toString());
		currentUser = currentUser->next;
	}
	return endString;
}



void UserNetwork::readUserNetworkFromString(string fullNetworkString_) {
	//delete this->users;
	//users = new DoublyLinkedList<User>;
	
	std::string fullNetworkString = fullNetworkString_;
	std::string nextUserDelimiter = "\n________________________________\n";
	int delimiterLength = nextUserDelimiter.length();
	
	size_t userEndPos;
	while ((userEndPos = fullNetworkString.find(nextUserDelimiter)) != std::string::npos) {
		User userToAdd = User(fullNetworkString.substr(0, userEndPos + delimiterLength));
		this->addUser(userToAdd);
		fullNetworkString.erase(0, userEndPos + delimiterLength);
	}

}

void UserNetwork::toFile() {
	string fileName = "UserNetwork.txt";
	ofstream outfile(fileName);
	outfile << this->toString();
	outfile.close();
}

void UserNetwork::readFromFile() {
	//possibly delete users and create new users list before reading
	//go to delimiter, remember to add delimiter length because we want to keep it
	string fileName = "UserNetwork.txt";
	ifstream infile(fileName);
	string line, networkString;
	

	stringstream strStream;
	strStream << infile.rdbuf();//read the file
	networkString = strStream.str();//str holds the content of the file;
	
	this->readUserNetworkFromString(networkString);
}	




