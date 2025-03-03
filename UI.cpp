#include "UI.h"

#include <iostream>
#include <string>

using namespace std;

UI::UI() {
	network = UserNetwork();
	user = NULL;
	cout << "Please wait, the network is reading all of the users..." << endl;
	network.readFromFile();
	//cout << network.getUsers()->at(0).toString() << " " << network.getUsers()->at(2).toString() << endl;
	//network.findShortestPath(network.getUsers()->at(0), network.getUsers()->at(4));
	//network.findUsersWithinThreeDegrees(network.getUsers()->at(0));
}

UI::~UI() {

}

void UI::run() {
	while(running) {
		this->mainMenu();
	}
	cout << "Exiting program" << endl;
}

void UI::mainMenu() {

	cout << "Type 'a' to create a new user\n"
			"Type 'b' to Log in\n"
			"Type 'c' to quit" << endl;

	char option;
	cin >> option;
	switch (option) {
			case 'a':
			{
				this->newUserMenu();
				break;
			}
			case 'b':
			{
				logged_in = loginPrompt();
				if (!logged_in) {
					return;
				}
				else {
					viewFriendRequests();
					while(logged_in) {
						loginMenu();
					}
				}
				break;
			}
			case 'c':
			{
				cout << "Please wait as we write your changes to the network..." << endl;
				running = false;
				network.toFile();
				return;
				break;
			}
			default:
			{
				cout << "Sorry that was not a valid option, please try again." << endl;
				return;
			}
		}
}

void UI::newUserMenu() {
	string username, password, realName, city;

	cout << "Please enter your desired username" << endl;
	cin.ignore();
	getline(cin, username);
	
	if (network.userAlreadyExists(username)) {
		cout << "Sorry that username already exists, please try again" << endl;
		return;
	}

	cout << "Please enter your password" << endl;
	getline(cin, password);

	cout << "Please enter your real name" << endl;
	getline(cin,realName);

	cout << "Please enter your city" << endl;
	getline(cin,city);


	User user = User(username, password, realName, city);
	network.addUser(user);
	return;
}

bool UI::loginPrompt() {
	string username, password;
	cout << "Enter your username" << endl;

	cin.ignore();
	getline(cin, username);

	cout << "Enter your password" << endl;
	getline(cin, password);

	if (!network.userAlreadyExists(username)) {
		cout << "Sorry invalid username or password. Please try again" << endl;
		return false;
	}

	this->user = &(network.getUsers()->at(network.findUser(username)));
	if (user->getPassword() == password) {
		if (user->getWall()->getWallPosts()->size() == 0)
			cout << "Your wall is empty" << endl;
		else
			cout << '\n' << user->getWall()->toString() << endl;
		return true;
	}
	else {
		cout << "Sorry invalid username or password. Please try again" << endl;
		return false;
	}
}

void UI::loginMenu() {
	char option;
	option = 'z';

	cout << "Type 'a' to create a wall post,\n"
			"type 'b' to delete a wall post,\n"
			"type 'c' to change your information\n"
			"type 'd' to log out\n"
			"type 'e' to delete your profile\n"
			"type 'f' to search for other users\n"
			"type 'g' to view your friends\n"
			"type 'h' to find the degree of separation" << endl;
	cin >> option;
	switch(option) {
		case 'a':
		{
			option = 'z';
			cout << "Type 'a' to post on your own wall,\n"
					"Or type 'b' to post on a friend's wall" << endl;
			cin >> option;
			switch(option) {
				case 'a':
				{
					createWallPost();
					break;
				}
				case 'b':
				{
					createWallPostOnFriendsWall();
					break;
				}
				default:
				{
					cout << "That was not a valid option, please try again" << endl;
					break;
				}
			}
			break;
		}
		case 'b':
		{
			option = 'z';
			cout << "Type 'a' to delete a post on your own wall,\n"
					"Or type 'b' to delete your post on a friend's wall" << endl;
			cin >> option;
			switch(option) {
				case 'a':
				{
					deleteWallPost();
					break;
				}
				case 'b':
				{
					deleteWallPostOnFriendsWall();
					break;
				}
				default:
				{
					cout << "That was not a valid option, please try again" << endl;
					break;
				}
			}
			break;
		}
		case 'c':
		{
			updateInformation();
			break;
		}
		case 'd':
		{
			logout();
			break;
		}
		case 'e':
		{
			cout << "Are you sure you would like to delete " 
					"your profile? (y/n)" << endl;
			char answer;
			cin >> answer;
			tolower(answer);
			if(answer == 'y')
				deleteProfile();
			else
				cout << "Returning to login menu" << endl;
			break;
		}
		case 'f':
		{
			searchUsers();
			break;
		}
		case 'g':
		{
			viewFriends();
			break;
		}
		case 'h':
		{
			degreeOfSeparationMenu();
			break;
		}
		default:
		{
			cout << "That was not a valid option, please try again" << endl;
			break;
		}
	}
	return;
}

void UI::createWallPost() {
	
	string content;
	cout << "Enter your content:" << endl;
	cin.ignore();
	getline(cin, content);
	WallPost newPost = WallPost(content, user->getRealName());
	this->user->addPost(newPost);
	return;
}

void UI::createWallPostOnFriendsWall() {
	int index;
	string content, friendUsername;

	if (user->getFriends().size() == 0) {
		cout << "You have no friends" << endl;
		return;
	}

	for (int i = 0; i < user->getFriends().size(); i++) {
		try {
			cout << i << ") " << user->getFriends().at(i) << endl;
		} catch (int& e) {
			cout << "Error: no friend at this index" << endl;
		}
	}

	cout << "Enter a number corresponding to the friend "
			"whose wall you would like to post on, "
			"or enter '-1' to go back" << endl;
	cin >> index;

	if (index == -1) //go back if user entered -1
		return;
	else {
		try {
			//try to get the friend's username
			friendUsername = user->getFriends().at(index);
		}
		catch (int& e) {
			cout << "Sorry there aren't any friends corresponding to that number" << endl;
		}
	}

	cout << "Friend's username: " << friendUsername << endl;
	cout << "Enter your content: " << endl;

	cin.ignore();
	getline(cin, content);

	try {
		//get the friend's Index in the network
		int friendUserIndex = network.findUser(friendUsername);
		//make a copy of the user
		User friendCopy = network.getUsers()->at(friendUserIndex);
		//create the post
		WallPost newPost = WallPost(content, user->getRealName());
		//add the post
		friendCopy.addPost(newPost);
		//set the friend on the network
		network.getUsers()->at(friendUserIndex) = friendCopy;
		cout << "Posted successfully" << endl;
	}
	catch (int& e) {
		cout << "Error getting friend from network" << endl;
	}

	return;
}

void UI::deleteWallPost() { // BUG

	cout << '\n';
	int index;
	int i = 0;
	if (user->getWall()->getWallPosts()->size() == 0) {
		cout << "Your wall is empty" << endl;
		return;
	}
	for (auto iter = user->getWall()->getWallPosts()->begin(); iter != user->getWall()->getWallPosts()->end(); iter++) {
		cout << i << ") " << iter->toString() << endl;
		i++;
	}
	cout << "Enter a number corresponding to the wall post "
			"you would like to delete, or enter '-1' to "
			"return to the login menu" << endl;
	cin >> index;

	if (index < 0)
		return;
	if (index > user->getWall()->getWallPosts()->size() -1 ) { // BUG segfaulting when index out of range
		cout << "Sorry there is no wall post corresponding to that number" << endl;
		return;
	}
	user->deletePost(index);
	return;
}

void UI::deleteWallPostOnFriendsWall() {
	// Should also allow user to post on friends wall from here
	int index;
	int postPosInTheirPosts;
	int j = 0;
	vector< tuple<int, int> > friendIndexAndPostIndex = vector< tuple<int, int> >();
	//second part of tuple is index of post on their wall = 

	if (user->getFriends().size() == 0) {
		cout << "You have no friends" << endl;
		return;
	}

	
	for (int friendPosInOurFriends = 0; friendPosInOurFriends < user->getFriends().size(); friendPosInOurFriends++) {
		try {
			//for all of our friends
			string usernameOfFriendMayHavePost = user->getFriends().at(friendPosInOurFriends);
			int indexOfFriendInNetwork = network.findUser(usernameOfFriendMayHavePost);
			User friendInNetwork = network.getUsers()->at(indexOfFriendInNetwork);

			postPosInTheirPosts = 0;
			for (auto iter = friendInNetwork.getWall()->getWallPosts()->begin(); iter != friendInNetwork.getWall()->getWallPosts()->end(); iter++) {
				//check if a post is ours, if so print it out;
				
				if (iter->getAuthor() == user->getRealName()) {
					friendIndexAndPostIndex.insert(friendIndexAndPostIndex.begin() + j, make_tuple(indexOfFriendInNetwork, postPosInTheirPosts));
					cout << j << ") " << iter->toString() << endl;
					j++;
				}
				postPosInTheirPosts++;
			}
			cout << "Enter a number corresponding to the wall post "
			"you would like to delete, or enter '-1' to "
			"return to the login menu" << endl;
			cin >> index;
			
			if (index > -1 && index < friendIndexAndPostIndex.size()) {
				//std::tie (myint, std::ignore, mychar) = mytuple;
				int chosenFriendIndex = 0;
				int postIndex = 0;

				tie (chosenFriendIndex, postIndex) = friendIndexAndPostIndex.at(index);
				cout << "chosenFriendIndex: " << chosenFriendIndex << endl;
				cout << "postIndex: " << postIndex << endl;
				//tuple<int,int> chosenFriendAndPostTuple = friendIndexAndPostIndex.at(index);
				//make a copy, edit the user, and set the user
				User friendCopy = network.getUsers()->at(chosenFriendIndex);
				friendCopy.deletePost(postIndex);
				network.getUsers()->at(chosenFriendIndex) = friendCopy;
				cout << "Post deleted successfully" << endl;
			} else {
				cout << "Error: bad post index" << endl;
			}


		} catch (int& e) {
			cout << "Error: no friend at this index" << endl;
		}
	}

	return;
	//make sure we can't delete other users posts
}

void UI::updateInformation() {
	char option = 'z';
	cout << "Enter 'a' to change Real name\n"
			"Enter 'b' to change city\n"
			"Enter 'c' to change password" << endl;

	cin >> option;
	string newInfo;
	switch(option) {
		case 'a':
		{
			cout << "Enter new name" << endl;
			cin.ignore();
			getline(cin,newInfo);
			user->setRealName(newInfo);
			break;
		}
		case 'b':
		{
			cout << "Enter new city" << endl;
			cin.ignore();
			getline(cin,newInfo);
			user->setCity(newInfo);
			break;
		}
		case 'c':
		{
			cout << "Enter new password" << endl;
			cin.ignore();
			getline(cin,newInfo);
			user->setPassword(newInfo);
			break;
		}
		default:
		{
			cout << "That was not a valid option. Returning to login menu" << endl;
			break;
		}
	}
	network.getUsers()->at(network.findUser(user->getUsername())) = *user;

	return;
}

void UI::deleteProfile() {
	network.deleteUser(network.findUser(user->getUsername()));
	logged_in = false;
	cout << "Profile deleted. Returning to Main menu" << endl;
}

void UI::searchUsers() {
	string name, uname, realName;
	string buildString = "";
	bool found = false;
	cout << "Type in a name to search" << endl;
	cin.ignore();
	getline(cin, name);
	for (auto x : name) {
		buildString += tolower(x);
	}
	name = buildString;
	buildString = "";
	int i = 0;
	vector<string> foundUsers = vector<string>();
	for (auto iter = network.getUsers()->begin(); iter != network.getUsers()->end(); iter++) {
		uname = iter->getUsername();
		realName = iter->getRealName();

		for(auto x : uname) {
			buildString += tolower(x);
		}

		uname = buildString;
		buildString = "";

		for (auto x : realName)
			buildString += tolower(x);

		realName = buildString;
		buildString = "";

		if (uname.find(name) != std::string::npos || realName.find(name) != std::string::npos ) {
			found = true;
			cout << i << ") Username: " << iter->getUsername() << " ";
			cout << "Real Name: " << iter->getRealName() << endl;
			foundUsers.insert(foundUsers.begin() + i, iter->getUsername());
			i++;
		}
	}
	if(!found)
		cout << "User not found" << endl;
	else {
		cout << "Enter the corresponding number of the user "
				"you would like to send a friend request to"
				" or enter -1 to go back"
				<< endl;
		cin >> i;

		if (index < 0)
			return;
		try {
			user->sendFriendRequest(foundUsers.at(i), &network);
		} catch(int& e) {
			cout << "Sorry there is no user corresponding to that number" << endl;
		}
	
	}
}

void UI::viewFriends() {
	int index;
	char option;

	if (user->getFriends().size() == 0) {
		cout << "You have no friends" << endl;
		return;
	}

	//print out list of friends
	for (int i = 0; i < user->getFriends().size(); i++) {
		try {
			cout << i << ") " << user->getFriends().at(i) << endl;
		} catch (int& e) {
			cout << "Error: no friend at this index" << endl;
		}
	}
	//prompt user to choose a friend
	cout << "Enter a number corresponding to the friend "
			"you would like to view, "
			"or enter '-1' to go back" << endl;
	cin >> index;

	if (index > -1 && index < user->getFriends().size()) { //make sure index is in range
		option = 'z';
		cout << "Type 'a' to view their wall,\n"
				"Or type 'd' to delete them as a friend" << endl;
		
		cin >> option;
		
		switch(option) {
			case 'a':
			{
				viewWall(index);
				break;
			}
			case 'd':
			{
				deleteFriend(index);
				break;
			}
			default:
			{
				cout << "That was not a valid option, please try again" << endl;
				break;
			}
		}
	}
}

void UI::deleteFriend(int atIndex) {

	try {
		string usernameToDelete = user->getFriends().at(atIndex);
		user->deleteFriend(usernameToDelete, &network);
	}
	catch (int& e) {
		cout << "Sorry there aren't any friends corresponding to that number" << endl;
	}

	// was: user = User(network.getUsers()->at(network.findUser(user.getUsername())));

	user = &(network.getUsers()->at(network.findUser(user->getUsername())));
	return;

}

void UI::viewWall(int atIndex) {
	string usernameToView = user->getFriends().at(atIndex);
	int chosenFriendIndex = network.findUser(usernameToView);
	User friendCopy = network.getUsers()->at(chosenFriendIndex);

	cout << '\n';
	int postIndex;
	int i = 0;

	if (friendCopy.getWall()->getWallPosts()->size() == 0) {
		cout << "Your friend's wall is empty" << endl;
		return;
	}
	for (auto iter = friendCopy.getWall()->getWallPosts()->begin(); iter != friendCopy.getWall()->getWallPosts()->end(); iter++) {
		cout << i << ") " << iter->toString() << endl;
		i++;
	}
	cout << "Enter a number corresponding to the wall post "
			"you would like to respond to or delete a response from, "
			" or enter '-1' to "
			"return to the login menu" << endl;
	cin >> postIndex;

	if (postIndex < 0)
		return;
	if (postIndex > i) {
		cout << "Sorry there is no wall post corresponding to that number" << endl;
		return;
	}

	char option = 'z';
	cout << "Type 'a' to add a response to this post, "
		"or type 'd' to delete a response of yours" << endl;
	cin >> option;
		
	switch(option) {
		case 'a':
		{
			addResponse(postIndex, chosenFriendIndex);
			break;
		}
		case 'd':
		{
			deleteResponse(postIndex, chosenFriendIndex);
			break;
		}
		default:
		{
			cout << "That was not a valid option, please try again" << endl;
			break;
		}
	}

	return;

}

void UI::addResponse(int postIndex, int chosenFriendIndex) {
	User friendCopy = network.getUsers()->at(chosenFriendIndex);
	string content;

	cout << "Enter content: " << endl;
	cin.ignore();
	getline(cin, content);
	//create the response
	WallPostResponse response = WallPostResponse(content, user->getRealName());
	//add the response to friendCopy
	friendCopy.addResponse(postIndex, response);
	//set the friend to the mutated copy
	network.getUsers()->at(chosenFriendIndex) = friendCopy;
}

void UI::deleteResponse(int postIndex, int chosenFriendIndex) {
	User friendCopy = network.getUsers()->at(chosenFriendIndex);
	vector<WallPostResponse> responses = friendCopy.getWall()->getWallPosts()->at(postIndex).getResponses();

	int i = 0;
	int responseIndex;

	cout << '\n';

	if (responses.size() == 0) {
		cout << "You have no responses on this post" << endl;
		return;
	}
	for (auto iter = responses.begin(); iter != responses.end(); iter++) {
		cout << i << ") " << iter->toString() << endl;
		i++;
	}
	cout << "Enter a number corresponding to the response you would like to delete, "
			"or enter '-1' to go back" << endl;
	
	cin >> responseIndex;

	//cases for user entering index out of range
	if (responseIndex < 0)
		return;
	if (responseIndex >= i) {
		cout << "Sorry there is no response corresponding to that number" << endl;
		return;
	}

	//make sure we can only delete our own responses
	if (responses.at(responseIndex).getAuthor() == user->getRealName()) {
		friendCopy.deleteResponse(postIndex, responseIndex);
		cout << "Response deleted successfully" << endl;
	} else {
		cout << "You can only delete your own responses" << endl;
	}

	//set the friend user
	network.getUsers()->at(chosenFriendIndex) = friendCopy;
	return;
}

void UI::viewFriendRequests() {
	int index;
	char choice;

	if(user->getFriendRequests().size() == 0) {
		cout << "You have no friend requests" << endl;
		return;
	}
	//had to change to for loop, iter not working correctly for ArrayList<string>
	for (int i = 0; i < user->getFriendRequests().size(); i++) {
		try {
			cout << i << ") " << user->getFriendRequests().at(i) << endl;
		} catch (int& e) {
			cout << "Error: no friend request at this index" << endl;
		}
	}

	cout << '\n' << endl;
	cout << "Enter a number corresponding to the friend request "
			"you would like to accept/delete, "
			"or enter '-1' to continue to the login menu" << endl;

	cin >> index;
	if (index < 0)
		return;

	try {
		string usernameToAccept = user->getFriendRequests().at(index);
	
		cout << "Enter 'a' to accept and 'd' to delete this friend request" << endl;
		cin >> choice;


		if (choice == 'a') {
			
			user->acceptFriendRequest(usernameToAccept, &network);
		}
		if (choice == 'd') {
			user->deleteFriendRequest(usernameToAccept, &network);
		}
	} catch(int& i) {
		cout << "Sorry there is no friend request corresponding to that number" << endl;
	}

	user = &(network.getUsers()->at(network.findUser(user->getUsername())));
	
	return;
}

void UI::degreeOfSeparationMenu() {
	char choice;
	cout << "Enter 'a' to find degree of separation between you and "
		 << "another user\n"
		 << "Enter 'b' to find all users who are three degrees away from you" 
		 << endl;
	cin >> choice;
	if (choice == 'a') {
		string target;
		cout << "Please enter the name of the target user" << endl;
		cin.ignore();
		getline (cin, target);
		User* targetUser = &(network.getUsers()->at(network.findUser(target)));
		network.findShortestPath(*(this->user), *targetUser);
	}
	else if (choice == 'b') {
		cout << "Finding all users who are three degrees away from you. "
			<< "This usually takes 5-10 minutes..." << endl;
		network.findUsersWithinThreeDegrees(*(this->user));
	}
	else
		return;
}

void UI::logout() {
	logged_in = false;
	cout << "Please wait as we write your changes to the network..." << endl;
	this->network.toFile();
	return;
}
