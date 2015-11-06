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

//TODO: BUGS HERE!!!
User::User(const string userString_, UserNetwork* myNetwork) {

	this->wall = new Wall();
	
	std::string userString = userString_;
	std::string friendString, friendRequestString, singleUsername;
	std::string nextUserDelimiter = "\n________________________________\n";
	//initialize some position markers and strings to hold results
	size_t usernameEndPos, passwordEndPos, realNameEndPos, cityEndPos, wallEndPos, friendsEndPos,friendRequestEndPos, index;
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
	friendsEndPos = userString.find("\n");
	friendString = userString.substr(9, friendsEndPos - 9);
	//now we split friendstring up by the spaces to get the usernames out

	while ((friendsEndPos = friendString.find(", ")) != std::string::npos) {
		singleUsername = friendString.substr(0, friendsEndPos);
 		index = myNetwork->findUser(singleUsername);

 		// EXCEPTION HERE
 		User friendToAdd = User(myNetwork->getUsers()->get(index));
 		//
 		//
 		
 		this->addFriend(&friendToAdd);
		friendString.erase(0, friendsEndPos+2);
	}
	userString.erase(0, userString.find("\n") + 1);

	//friend requests
	friendRequestEndPos = userString.find("\n\nWall: \n\n");
	friendRequestString = userString.substr(17, friendRequestEndPos - 17);

	//cout << "friend request string: " << friendRequestString << "end of fr string" << endl;

	//again, same format, split by the commas to parse usernames
	while ((friendRequestEndPos = friendRequestString.find(", ")) != std::string::npos) {
		singleUsername = friendRequestString.substr(0, friendRequestEndPos);
 		index = myNetwork->findUser(singleUsername);

 		// EXCEPTION HERE
 		User friendToAdd = User(myNetwork->getUsers()->get(index));
 		//
 		//
 		cout << "friend we are trying to add:" << friendToAdd.getUsername() << endl;
 		this->addFriendRequest(&friendToAdd);
		friendRequestString.erase(0, friendRequestEndPos+2);
	}

	
	userString.erase(0, userString.find("\n\nWall: \n\n") + 10);
	//cout << "Userstring so far..."  << userString << endl;

	//wall
	//now all that is left in userString is wall since we erased as we parsed the rest
	//printf the wall string
	
	wallEndPos = userString.find(nextUserDelimiter);
	userString = userString.substr(0, wallEndPos);
	this->wall->readWallPostsFromString(userString);
	
}



User::~User() {
	delete wall;
}

User& User::operator=(const User& copy) {
	username = copy.getUsername();
	password = copy.getPassword();
	realName = copy.getRealName();
	city = copy.getCity();
	delete wall;
	wall = new Wall(*(copy.getWall()));
	this->friendRequests = copy.getFriendRequests();
	this->friends = copy.getFriends();
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


string User::toString() const {
	//cout << "inside User:toString" << endl;
	string endString = "Username: " + this->getUsername() + "\n";
	endString += "Password: " + this->password + "\n";
	endString += "Real Name: " + this->getRealName() + "\n";
	endString += "City: " + this->getCity() + "\n";
	endString += this->friendsToString();
	endString += this->friendRequestsToString();

	endString += "\n\nWall: \n\n" + this->wall->toString() + "\n";
	endString += "________________________________\n";
	return endString;
}

//
/* Helpers for printing friends/requests*/
//

string User::friendsToString() const{
	string endString = "";
	endString += "Friends: ";
	User** iter = getFriends().begin();

	for (; iter != getFriends().end(); iter++) {
		endString += (*iter)->getUsername() + ", ";
	//cout << "length now:" << getFriends().getLength() << endl;
	//for (int i =0; i < getFriends().getLength(); i++) {

		//cout << "friend " << i <<endl;
		
		//endString += getFriends().get(i)->getUsername() + ", "; 
		//cout << "inside friendsToString, heres *iter: " << *iter << endl;

		//cout << "**" << (*iter)->getUsername() <<endl;
	}
	//cout << "endString: " << endString << endl;
	return endString + "\n";
}

string User::friendRequestsToString() const {
	string endString = "";
	endString += "Friend Requests: ";
	User** iter = getFriendRequests().begin();
	for (; iter != getFriendRequests().end(); iter++) {
		endString += (*iter)->getUsername() + ", ";
	}
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
/* General methods for friends and friend requests*/
//

//probably get rid of this:
void User::sendFriendRequest(User* potentialFriend) {
    //if (potentialFriend->getFriendRequests().find(this) == -1) {
        potentialFriend->addFriendRequest(this);
    //}
   // else {
    	//cout << "Error: You have already sent this user a friend request. Now you just look desperate." << endl;
    //}
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
