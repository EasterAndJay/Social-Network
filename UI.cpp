#include "UI.h"

#include <iostream>
#include <string>

using namespace std;

UI::UI() {
	network = UserNetwork();
	user = User();
	network.readFromFile();
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
				running = false;
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
	this->network.toFile();
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

	this->user = User(network.getUsers()->at(network.findUser(username)));
	if (user.getPassword() == password) {
		if (user.getWall()->getWallPosts()->size() == 0)
			cout << "Your wall is empty" << endl;
		else
			cout << '\n' << user.getWall()->toString() << endl;
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
			"type 'g' to view your friends" << endl;
	cin >> option;
	switch(option) {
		case 'a':
		{
			createWallPost();
			break;
		}
		case 'b':
		{
			deleteWallPost();
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
			viewFriendRequests();
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
	WallPost newPost = WallPost(content, user.getRealName());
	this->user.addPost(newPost);
	network.getUsers()->at(network.findUser(user.getUsername())) = user;
	return;
}

void UI::deleteWallPost() {
	cout << '\n';
	int index;
	int i = 0;
	if (user.getWall()->getWallPosts()->size() == 0) {
		cout << "Your wall is empty" << endl;
		return;
	}
	for (auto iter = user.getWall()->getWallPosts()->begin(); iter != user.getWall()->getWallPosts()->end(); iter++) {
		cout << i << ") " << iter->toString() << endl;
		i++;
	}
	cout << "Enter a number corresponding to the wall post "
			"you would like to delete, or enter '-1' to "
			"return to the login menu" << endl;
	cin >> index;

	if (index < 0)
		return;
	if (index > i) {
		cout << "Sorry there is no wall post corresponding to that number" << endl;
		return;
	}
	user.deletePost(index);
	network.getUsers()->at(network.findUser(user.getUsername())) =  user;
	return;
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
			user.setRealName(newInfo);
			break;
		}
		case 'b':
		{
			cout << "Enter new city" << endl;
			cin.ignore();
			getline(cin,newInfo);
			user.setCity(newInfo);
			break;
		}
		case 'c':
		{
			cout << "Enter new password" << endl;
			cin.ignore();
			getline(cin,newInfo);
			user.setPassword(newInfo);
			break;
		}
		default:
		{
			cout << "That was not a valid option. Returning to login menu" << endl;
			break;
		}
	}
	network.getUsers()->at(network.findUser(user.getUsername())) = user;

	return;
}

void UI::deleteProfile() {
	network.deleteUser(network.findUser(user.getUsername()));
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
			user.sendFriendRequest(foundUsers.at(i), &network);
		} catch(int& e) {
			cout << "Sorry there is no user corresponding to that number" << endl;
		}
	
	}
}

void UI::viewFriends() {
	// Need to delete friends from this list
	int index;

	if (user.getFriends().size() == 0) {
		cout << "You have no friends" << endl;
		return;
	}

	for (int i = 0; i < user.getFriends().size(); i++) {
		try {
			cout << i << ") " << user.getFriends().at(i) << endl;
		} catch (int& e) {
			cout << "Error: no friend at this index" << endl;
		}
	}

	cout << "Enter a number corresponding to the friend "
			"you would like to delete, "
			"or enter '-1' to go back" << endl;
	cin >> index;
	

	//if (index < 0)
	//	return;
	
	if (index > -1) {
		try {
			string usernameToDelete = user.getFriends().at(index);
			user.deleteFriend(usernameToDelete, &network);
		}
		catch (int& e) {
			cout << "Sorry there aren't any friends corresponding to that number" << endl;
		}
	}

	user = User(network.getUsers()->at(network.findUser(user.getUsername())));
	return;
}

void UI::viewFriendRequests() {
	int index;
	char choice;

	if(user.getFriendRequests().size() == 0) {
		cout << "You have no friend requests" << endl;
		return;
	}
	//had to change to for loop, iter not working correctly for ArrayList<string>
	for (int i = 0; i < user.getFriendRequests().size(); i++) {
		try {
			cout << i << ") " << user.getFriendRequests().at(i) << endl;
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
		string usernameToAccept = user.getFriendRequests().at(index);
	
		cout << "Enter 'a' to accept and 'd' to delete this friend request" << endl;
		cin >> choice;


		if (choice == 'a') {
			
			user.acceptFriendRequest(usernameToAccept, &network);
		}
		if (choice == 'd') {
			user.deleteFriendRequest(usernameToAccept, &network);
		}
	} catch(int& i) {
		cout << "Sorry there is no friend request corresponding to that number" << endl;
	}

	user = User(network.getUsers()->at(network.findUser(user.getUsername())));
	
	return;
}

void UI::logout() {
	logged_in = false;
	this->network.toFile();
	return;
}
