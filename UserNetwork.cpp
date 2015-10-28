#include "UserNetwork.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;


UserNetwork::UserNetwork(const UserNetwork& network) {
	this->users = new ArrayList<User>(*(network.users));
} 

//Simple destructor
UserNetwork::~UserNetwork () {
	delete users;	
}


// Returns user if found.
// If not found, returns empty user.
User& UserNetwork::findUser(string username_) {
	//Node<User>* currentUser = this->users->getHead();
	
	//while (currentUser) {
	for(User* iter = this->users->begin(); iter != this->users->end(); iter++) {
		if (iter->getUsername() == username_)
			return *iter;
	}
	return User();
}

//Helper method to make sure there are no duplicate users before adding
bool UserNetwork::userAlreadyExists(string username) {
	if(findUser(username).getUsername() == User())
		return false;
	else
		return true;
}

void UserNetwork::addUser(User user) { //make sure no duplicates
	if (userAlreadyExists(user.getUsername())) {
		//printf("Sorry, a user already exists with this username\n");
	} else {
		this->users->insert(0,user);
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
	
	//Node<User>* currentUser = this->users->getHead();
	//while (currentUser) {
	for(User* currentUser = this->users->begin(); currentUser != this->users->end(); currentUser++)
		endString.append(currentUser->toString());
		//currentUser = currentUser->next;
	}
	return endString;
}



void UserNetwork::readUserNetworkFromString(string fullNetworkString_) {
	//delete this->users;
	//users = new ArrayList<User>;
	
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




