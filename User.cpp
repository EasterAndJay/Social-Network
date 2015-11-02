#include "User.h"
#include <stdio.h>


User::User(User const& user) { 
	/*
	if (user.getWall() != NULL)
		this->wall = Wall(*(user.getWall()));
	else
		this->wall = new Wall();
	*/
	this->wall = user.getWall();
	this->setFriendRequests(user.getFriendRequests());
	this->setFriends(user.getFriends());
	this->username = user.getUsername();
	this->password = user.getPassword();
	this->realName = user.getRealName();
	this->city = user.getCity();
}

User& User::operator=(User copy) {
	std::swap(*this,copy);
	return *this;
}

//solely made these for the copy constructor to use
Wall* User::getWall() const {
	return this->wall;
}

string User::getPassword() const {
	return this->password;
}

User::User(string username_, string password_, string realName_, string city_) {
	this->wall = new Wall();
	//don't think we need to initialize these, because it is dont implicitly when the User object is made
	//this->friends = ArrayList<User*>;
	//this->friendRequests = ArrayList<User*>;
		 
	this->username = username_;
	this->wall->setUsername(username_);
	this->password = password_;
	this->realName = realName_;
	this->city = city_;
}

User::~User() {
	delete wall;
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
	this->city = city;
}

string User::getCity() const{
	return this->city;
}

void User::setPassword(string password_){ //FBI level security
	this->password = password_;
}
bool User::checkPassword (string password_){
	if (this->password == password_) {return true;}
	else {return false;}
}
	 
void User::addPost(WallPost post_){
	this->wall->addPost(post_);
}
void User::deletePost(int pos) {
	this->wall->deletePost(pos);
}

string User::toString() {
	string endString = "Username: " + this->getUsername() + "\n";
	endString += "Password: " + this->password + "\n";
	endString += "Real Name: " + this->getRealName() + "\n";
	endString += "City: " + this->getCity() + "\n\n";
	endString += "Wall: \n\n" + this->wall->toString() + "\n";
	endString += "________________________________\n";

	return endString;
}

User::User(const string userString_) {

//void User::readUserFromString(string userString_) {

	this->wall = new Wall();
	
	std::string userString = userString_;
	std::string nextUserDelimiter = "\n________________________________\n";
	//initialize some position markers and strings to hold results
	size_t usernameEndPos, passwordEndPos, realNameEndPos, cityEndPos, wallEndPos;
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
	cityEndPos = userString.find("\n\nWall: \n\n");
	
	this->city = userString.substr(6, cityEndPos - 6);
	userString.erase(0, cityEndPos + 10);

	//wall
	//now all that is left in userString is wall since we erased as we parsed the rest
	
	//printf the wall string
	wallEndPos = userString.find(nextUserDelimiter);
	userString = userString.substr(0, wallEndPos);
	this->wall->readWallPostsFromString(userString);

}


	




//getters and setters for friends and friendRequests arrays
ArrayList<User*> User::getFriendRequests() const {
	return this->friendRequests;	
}

void User::setFriendRequests(ArrayList<User*> friendRequests_){
	this->friendRequests = friendRequests_;
}
	
ArrayList<User*> User::getFriends() const {
	return this->friends;
}
	
	
void User::setFriends(ArrayList<User*> friends_){
	this->friends = friends_;
}



//general methods for friends and friend requests

void User::sendFriendRequest(User* potentialFriend) {  //not sure whether to use pointer or not for these
    
    if (potentialFriend->getFriendRequests()->find(this) == -1;
        potentialFriend->getFriendRequests()->insert(0, this);
    } else {
        cout << "Error: You have already sent this user a friend request. Now you just look desperate." << endl
    }
}

void User::acceptFriendRequest(int index){
    //remove the friend request which makes sure that it infact is in the list, if so
    //get the friend so we 

	try { 
		//if this friend request actually exists
		User* friendToAccept = this->getFriendRequests()->get(index);
    	//remove the request
    	this->getFriendRequests()->remove(index);
        //add the friend to this user
        this->getFriends()->insert(0, friendToAccept);
        //add this user to the new friend's friend list
        friendToAccept->getFriends()->insert(0, this);
        
        cout << "Friend added successfully" << endl;
    } catch (int& e) {
        cout << "Error: You dont have a request at this index." << endl;
    }
    /*
    if (this->getFriendRequests().find(friendToAccept) != -1) {
		this->getFriendRequests().delete
		this->getFriends().insert(0, friendToAccept);
		friendToAccept->getFriends().insert(0, this);
	}*/
}

void User::deleteFriendRequest(int index){
    if (this->getFriendRequests()->remove(index)){
        cout << "Friend removed successfully" << endl
        //could add the firends name to cout
    }
    
    else {
        cout << "Error: No friend request at this index." << endl;
    }
    /*
    if (this->getFriendRequests().find(friendToDelete) > -1) {
		this->getFriendRequests().deleteByValue(friendToDelete);
	}*/
}

void User::deleteFriend(int index){
    if (this->getFriends()->remove(index)) {
        cout << "Friend removed successfully" << endl;
        //could add the deleted friends name to cout
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










