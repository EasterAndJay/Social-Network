#include "UserNetwork.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>
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
	/*if (userAlreadyExists(user.getUsername()))
		return;
	else*/
		this->users->insert(users->end(),user);
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

void print(queue<User> s,int num)
{
    if(!num)
    {
        cout << endl;
        return;
    }
    User x= s.front();
    s.pop();
    cout << x.toString() << endl;
    s.push(x);
    print(s,--num);
}

void UserNetwork::findShortestPath(User& source, User& target) {
	// Initialize Queue to hold pointers to Users
	queue<User*> q;
	string path = "";
	// Build a string to print out
	string printOut = "";
	printOut += "The shortest path to "
				+ target.getUsername() 
				+ " is:\n";


	// IF source and target are equal
	if (source == target) { 
		printOut += source.getUsername();
		cout << printOut << endl;
		cout << "The distance of the path is: 0" << endl;
		return;
	}
	
	// Initialize distance of all users in network to -1
	for (auto iter = getUsers()->begin(); iter != getUsers()->end(); ++iter) {
		iter->dist = -1;
		iter->path = "";
	}

	// Initialize source distance to 0
	source.dist = 0;
	// Push source to queue
	q.push(&source);
	User* adjUser;
	// While the queue has users in it
	while(!q.empty()) {
		// Pop user from front of queue

		User* v = q.front();
		v->setFriendPointers(*this);
		q.pop();
		// Iterate through all the users friends
		for (int i = 0; i < v->getFriendPointers().size(); i++) {
			adjUser = v->getFriendPointers().at(i);
			// IF we haven't discovered the user before
			// Set its distance and path
			// Push it to the queue
			if (adjUser->dist == -1) {
				adjUser->dist = v->dist + 1;
				adjUser->path = v->getUsername();
				q.push(adjUser);
				// IF we found the target
				// print out path and distance
				// Return
				if (*adjUser == target) {
					path = adjUser->getUsername();
					std::vector<string> users;
					// Build path by following it from the back->tofront
					// and inserting it a vector
					while (path != "") {
						users.insert(users.begin(), path);
						path = getUsers()->at(findUser(path)).path;
					}
					// Build printOut string
					for (auto iter = users.begin(); iter != users.end(); ++iter) {
						printOut += *iter;
						if (iter != users.end()-1) {
							printOut += "->";
						}
					}
					// Print and return
					cout << printOut << endl;
					cout << "The distance of the path is: " 
						 << adjUser->dist << endl;
					return;
				}
			}
		}
	}
	// IF we never found the target
	// Print that there is no path and return
	cout << "There is no path that connects "
		 << source.getUsername() << " and "
		 << target.getUsername() << endl;
	return;
}

void UserNetwork::findUsersWithinThreeDegrees(User& source) {
	// Initialize Queue to hold pointers to Users
	queue<User*> q;

	// Build a string to print out
	string printOut = "";
	printOut += "These users are three degrees of separation from "
				+ source.getUsername() 
				+ ":\n";

	// Initialize distance of all users in network to -1
	for (auto iter = getUsers()->begin(); iter != getUsers()->end(); ++iter) {
		iter->dist = -1;
	}

	// Initialize source distance to 0
	source.dist = 0;
	// Push source to queue
	q.push(&source);
	User* adjUser;
	// While the queue has users in it
	while(!q.empty()) {
		// Pop user from front of queue
		User* v = q.front();
		v->setFriendPointers(*this);
		q.pop();
		// Iterate through all the users friends
		for (int i = 0 ; i < v->getFriendPointers().size(); i++) {
			adjUser = v->getFriendPointers().at(i);
			// IF we haven't discovered the user before
			// Set its distance, add it to the path,
			// Push it to the queue
			//if (adjUser) {
			if (adjUser->dist == -1) {
				adjUser->dist = v->dist + 1;
				adjUser->path = v->getUsername();
				q.push(adjUser);
				if (adjUser->dist == 3) {
					printOut+= adjUser->getUsername() + "\n";
				}
			}
		}
	}
	cout << printOut << endl;
}

