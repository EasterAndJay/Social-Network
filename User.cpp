#include "User.h"
#include <stdio.h>
#include <string>



User::User(User const& user) { 
	this->wall = new Wall(*(user.getWall()));
	this->setFriendRequests(user.getFriendRequests());
	this->setFriends(user.getFriends());
	this->username = user.getUsername();
	this->password = user.getPassword();
	this->realName = user.getRealName();
	this->city = user.getCity();
}


User::User(string username_, string password_, string realName_, string city_) {
	this->wall = new Wall();
	this->username = username_;
	this->wall->setUsername(username_);
	this->password = password_;
	this->realName = realName_;
	this->city = city_;
}

//TODO: Get friends from user String
User::User(const string userString_, UserNetwork* myNetwork) {

	this->wall = new Wall();
	
	std::string userString = userString_;
	std::string friendString, singleUsername;
	std::string nextUserDelimiter = "\n________________________________\n";
	//initialize some position markers and strings to hold results
	size_t usernameEndPos, passwordEndPos, realNameEndPos, cityEndPos, wallEndPos, friendsEndPos, singleNameEndPos, index;
	//std::string username, password, realName, city, ;

	//pull out username
	usernameEndPos = userString.find("\n");
	this->username = userString.substr(10, usernameEndPos - 10);
	this->wall->setUsername(this->username);
	userString.erase(0, usernameEndPos + 1);

	//password
	passwordEndPos = userString.find("\n");
	this->password = userString.substr(10, passwordEndPos - 10);
	userString.erase(0, passwordEndPos + 1);

	//real name
	realNameEndPos = userString.find("\n");
	this->realName = userString.substr(11, realNameEndPos - 11);
	userString.erase(0, realNameEndPos + 1);

	//city
	cityEndPos = userString.find("\n");
	this->city = userString.substr(6, cityEndPos - 6);
	userString.erase(0, cityEndPos + 1);
	//cout << "got past city in string constructor...."  << endl;
	
	//friends
	friendsEndPos = userString.find("\n\nWall: \n\n");
	friendString = userString.substr(9, friendsEndPos - 9);
	//now we split friendstring up by the commas to get the usernames out

	/*
 	while((singleNameEndPos = friendString.find(", ")) != friendsEndPos) {
 		singleUsername = friendString.substr(0, friendsEndPos);
 		index = myNetwork->findUser(singleUsername);
 		User friendToAdd = myNetwork->getUsers()->get(index);
 		this->addFriend(&friendToAdd);
 	}*/

	userString.erase(0, friendsEndPos + 10);

	//wall
	//now all that is left in userString is wall since we erased as we parsed the rest
	
	//printf the wall string
	wallEndPos = userString.find(nextUserDelimiter);
	userString = userString.substr(0, wallEndPos);
	this->wall->readWallPostsFromString(userString);

}
/*
//loop through full posts (looking for our big delimiter)
	while ((postEndPos = fullWallString.find(nextPostDelimiter)) != std::string::npos) {
		post = fullWallString.substr(0, postEndPos);
			//now we have a full post, time to grab our date string from between "On" and "\n"
			timeEndPos = post.find("\n");
			time = post.substr(3, timeEndPos - 3);
			post.erase(0, timeEndPos + 1); //add 1 to remove our "\n" delimiter too
			//now we pull the author
			authorEndPos = post.find(" wrote:\n");
			author = post.substr(0, authorEndPos);
			post.erase(0, authorEndPos + 8); // add 8 because " wrote:\n" is 8 characters long
			// content is just what is left over in post now that we've stripped the rest
			content = post;
			
			addPost(WallPost(content, author, time));
			
		fullWallString.erase(0, postEndPos + nextPostDelimiter.length());
	}
*/





User::~User() {
	delete wall;
}

User& User::operator=(User copy) {
	username = copy.getUsername();
	password = copy.getPassword();
	realName = copy.getRealName();
	city = copy.getCity();
	delete wall;
	wall = new Wall(*(copy.getWall()));
	this->setFriendRequests(copy.getFriendRequests());
	this->setFriends(copy.getFriends());
	return *this;
}

//
/* Getters and Setters */
//

Wall* User::getWall() const {
	return this->wall;
}

string User::getPassword() const {
	return this->password;
}


void User::setUsername(string username_) {
	this->username = username_;
}

string User::getUsername() const{
	return this->username;
}

void User::setRealName(string realName_){
	this->realName = realName_;
}

string User::getRealName() const{
	return this->realName;
}

void User::setCity(string city_){
	this->city = city_;
}

string User::getCity() const{
	return this->city;
}

void User::setPassword(string password_){
	this->password = password_;
}

bool User::checkPassword (string password_){
	if (this->password == password_)
		return true;
	else
		return false;
}
	 
void User::addPost(WallPost post_){
	this->wall->addPost(post_);
}
void User::deletePost(int pos) {
	this->wall->deletePost(pos);
}


//TODO: Print friends
string User::toString() {
	string endString = "Username: " + this->getUsername() + "\n";
	endString += "Password: " + this->password + "\n";
	endString += "Real Name: " + this->getRealName() + "\n";
	endString += "City: " + this->getCity() + "\n";
	endString += friendsToString();
	endString += friendRequestsToString();

	endString += "Wall: \n\n" + this->wall->toString() + "\n";
	endString += "________________________________\n";
	return endString;
}

string User::friendsToString() {
	string endString = "";
	endString += "Friends: ";
	User** iter = getFriends().begin();
	for (; iter != getFriends().end(); iter++) {
		if(iter == getFriends().end()-1) {
			endString += (*iter)->getUsername() += "\n\n";
		}
		else {
			endString += (*iter)->getUsername() + ", ";
		}
	}
	endString += '\n';
	return endString;
}

string User::friendRequestsToString() {
	string endString = "";
	endString += "Friend Requests: ";
	User** iter = getFriendRequests().begin();
	for (; iter != getFriendRequests().end(); iter++) {
		if(iter == getFriendRequests().end()-1){
			endString += (*iter)->getUsername() += "\n\n";
		}
		else {
			endString += (*iter)->getUsername() + ", ";
		}
	}
	endString += '\n';
	return endString;
}
//
/* Getters and setters for friends and friendRequests arrays*/
//

ArrayList<User*> User::getFriendRequests() const{
	return this->friendRequests;	
}

void User::setFriendRequests(ArrayList<User*> friendRequests_){
	int i = 0;
	for (User** iter = friendRequests_.begin(); iter != friendRequests_.end(); iter++) {
		this->friendRequests.set(i, *(iter));
		i++;
	}
}

ArrayList<User*> User::getFriends() const{
	return this->friends;
}
	
	
void User::setFriends(ArrayList<User*> friends_){
	int i = 0;
	for (User** iter = friends_.begin(); iter != friends_.end(); iter++) {
		this->friends.set(i, *(iter));
		i++;
	}
}

//
/* General methods for friends and friend requests */
//

void User::sendFriendRequest(User* potentialFriend) {
    if (potentialFriend->getFriendRequests().find(this) == -1) {
        potentialFriend->addFriendRequest(this);
    }
    else {
    	cout << "Error: You have already sent this user a friend request. Now you just look desperate." << endl;
    }
}

//helper for sendFriendRequest
void User::addFriendRequest(User* newFriendRequest) {
	this->friendRequests.insert(0, newFriendRequest);
}


void User::acceptFriendRequest(int index){
    // Remove the friend request, which makes sure 
    // that it infact is in the list.
    // If so get the friend so we 
	try { 
		//if this friend request actually exists
		User* friendToAccept = this->getFriendRequests().get(index);
    	//remove the request
    	this->friendRequests.remove(index);
        //add the friend to this user
        this->addFriend(friendToAccept);
        //add this user to the new friend's friend list
        friendToAccept->addFriend(this);
        
        cout << friendToAccept->getUsername() <<" is now your friend." << endl;
    } catch (int& e) {
        cout << "Error: You dont have a request at this index." << endl;
    }
}

//helper for accept friend request
void User::addFriend(User* newFriend) {
	this->friends.insert(0, newFriend);
}


void User::deleteFriendRequest(int index){
    if (this->friendRequests.remove(index)){
        cout << "Friend request removed successfully" << endl;
    }
    
    else {
        cout << "Error: No friend request at this index." << endl;
    }
}


//also delete this from the other persons friend list
void User::deleteFriend(int index){
    if (this->friends.remove(index)) {
        cout << "Friend removed successfully" << endl;
    }
    else {
        cout << "Error: No friend request at this index." << endl;
    }

}

bool operator==(const User& left, const User& right) {
	return left.getUsername() == right.getUsername();		
}

bool operator !=(const User& left, const User& right) {
	return !(left == right);
}
