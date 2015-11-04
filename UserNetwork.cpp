#include "UserNetwork.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;


UserNetwork::UserNetwork(const UserNetwork& network) {
	this->users = new ArrayList<User>(*(network.users));
}

UserNetwork::~UserNetwork () {
	delete users;	
}

UserNetwork& UserNetwork::operator=(UserNetwork copy) {
	delete users;
	users = new ArrayList<User>(*(copy.getUsers()));
	return *this;
}

ArrayList<User>* UserNetwork::getUsers(){
	return this->users;
}

// Returns index of user if found.
// If not found, returns -1
int UserNetwork::findUser(string username_) {
	//for(User* iter = this->users->begin(); iter != this->users->end(); iter++) {
	
	for (int i = 0; i < this->users->getLength(); i++){
		//cout << "inside finduser this is current length of users list:" << endl;
		//cout << this->users->getLength() << endl;
	if (this->users->get(i).getUsername() == username_)
		return i;
	}
	return -1;
}

//Helper method to make sure there are no duplicate users before adding
bool UserNetwork::userAlreadyExists(string username) {
	if(findUser(username) != -1)
		return true;
	else
		return false;
}

void UserNetwork::addUser(User user) { //make sure no duplicates   //was: const User& user
	if (userAlreadyExists(user.getUsername()))
		return;
	else
		this->users->insert(0,user);
}

void UserNetwork::deleteUser(int i){ //make sure user in fact exists before deleting
	this->users->remove(i);
}


string UserNetwork::toString() {
	string endString = string();
	
	//Node<User>* currentUser = this->users->getHead();
	//while (currentUser) {
	for(User* currentUser = this->users->begin(); currentUser != this->users->end(); currentUser++) {
		//cout << currentUser << endl;
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
		User userToAdd = User(fullNetworkString.substr(0, userEndPos + delimiterLength), this);
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

/*
void UserNetwork::howManyFriendsUsersHave() {
	for (int i = 0; i < this->users->getLength(); i++){
		//cout << "inside finduser this is current length of users list:" << endl;
		//cout << this->users->getLength() << endl;
	  	string name = this->users->get(i).getUsername();
	  	
	  	cout << "----" << "pointer we get?" << this->users->get(i).getFriends() <<endl;
	  	int friendNumber = this->users->get(i).getFriends().getLength();

	    cout << "~~~~~" << name << " has " << friendNumber << " friends." <<endl;
	}
}*/

void UserNetwork::createFriendship(int requestorIndex, int acceptorIndex) {

	if (this->users->getLength() < 2) {
		return;
	}

	User* network = this->getUsers()->getList();
	
	(network + requestorIndex)->addFriend(network+acceptorIndex);
	(network + acceptorIndex)->addFriend(network+requestorIndex);
    
    //cout << "Error: No user at this index." << endl;
}

void UserNetwork::sendFriendRequest(int requestorIndex, int acceptorIndex) {
//make sure acceptor doesn't already have a friend request from this user

	User* network = this->getUsers()->getList();
	(network + requestorIndex)->sendFriendRequest(network+acceptorIndex);
	//this is so error prone
}


/*
if (potentialFriend->getFriendRequests().find(this) == -1) {
        potentialFriend->addFriendRequest(this);
    }
    else {
    	cout << "Error: You have already sent this user a friend request. Now you just look desperate." << endl;
    }

*/





