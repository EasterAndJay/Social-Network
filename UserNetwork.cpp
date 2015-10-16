#include "UserNetwork.h"

//Simple destructor
UserNetwork::~UserNetwork () {
	delete users;	
}

//Helper method to make sure there are no duplicate users before adding
bool UserNetwork::userAlreadyExists(User user) {
	//start peekUser pointer at the head of users
	//string username = user.getUsername();
	/*Node<User>* peekUser = this->users->getHead();
	//loop through and check against input argument username
	while (peekUser) {
		if (peekUser->data.getUsername() == username) {
			printf("user found\n");
			return true;
		}
		peekUser = peekUser->next;
	}

	printf("user not found\n");*/
	return true;
}

void UserNetwork::addUser(User user) { //make sure no duplicates
	//printf("User Added Successfully\n");
	/*if (userAlreadyExists(user)) {
		printf("Sorry, a user already exists with this username\n");
	} else {*/
		//this->users->addToEnd(user);
	//}
}

void UserNetwork::deleteUser(User user){ //make sure user in fact exists before deleting
}

void UserNetwork::toFile() {
	
}

void UserNetwork::readFromFile() {
	//possibly delete users and create new users list before reading
	//go to delimiter, remember to add delimiter length because we want to keep it
}