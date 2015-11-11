#include "UserNetwork.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
using namespace std;


UserNetwork::UserNetwork(const UserNetwork& network) {
	this->users = new vector<User>(*(network.users));
}

UserNetwork::~UserNetwork () {
	delete users;	
}

UserNetwork& UserNetwork::operator=(UserNetwork copy) {
	delete users;
	users = new vector<User>(*(copy.getUsers()));
	return *this;
}

vector<User>*& UserNetwork::getUsers(){
	return this->users;
}

// Returns index of user if found.
// If not found, returns -1
int UserNetwork::findUser(string username_) {
	int i = 0;
	for(auto iter = this->users->begin(); iter != this->users->end(); iter++) {
		if (iter->getUsername() == username_)
			return i;
		i++;
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
		this->users->insert(users->begin() + 0,user);
}

void UserNetwork::deleteUser(int i){ //make sure user in fact exists before deleting
	this->users->erase(users->begin() + i);
}


string UserNetwork::toString() {
	string endString = string();
	
	//Node<User>* currentUser = this->users->getHead();
	//while (currentUser) {
	for(auto currentUser = this->users->begin(); currentUser != this->users->end(); currentUser++) {
		endString.append(currentUser->toString());
	}
	return endString;
}



void UserNetwork::readUserNetworkFromString(string fullNetworkString_) {
	//delete this->users;
	//users = new vector<User>;
	
	std::string fullNetworkString = fullNetworkString_;
	std::string nextUserDelimiter = "\n________________________________\n";
	int delimiterLength = nextUserDelimiter.length();
	
	size_t userEndPos;
	while ((userEndPos = fullNetworkString.find(nextUserDelimiter)) != std::string::npos) {
		//Changed to reflect new User constructor:
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

void UserNetwork::findShortestPath(User& source, User& target) {
	queue<User> q;
	for (auto user: *(this->getUsers())) {
		user.dist = -1;
	
	}
	source.dist = 0;
	q.push(source);
	while(!q.empty()) {
		User v = q.front();
		q.pop();
		for (auto adjUser : v.getFriends()) {
			User w = this->getUsers()->at(this->findUser(adjUser));
			//cout << w.toString() << endl;
			w.dist = v.dist + 1;
			w.path = v.getUsername();
			if (w == target) {
				cout << w.dist << endl;
				string path = v.path;
				while (path != "") {
					cout << path << endl;
					v = this->getUsers()->at(this->findUser(v.path));
					path = v.path;
				}
				return;
			}
			
			q.push(w);
		}
	}
}