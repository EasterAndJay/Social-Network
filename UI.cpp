#include "UI.h"

#include <iostream>
#include <string>

using namespace std;

UI::UI() {
	network = UserNetwork();
	user = User();
	network.readFromFile();
	logged_in = false;
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
	cout << "Type 'a' to create a new user, type 'b' to Log in, type 'c' to quit" << endl;
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
					cout << "Sorry invalid username or password. Please try again" << endl;
					return;
				}
				else {
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
	cin >> username;

	if (network.userAlreadyExists(username)) {
		cout << "Sorry that username already exists, please try again" << endl;
		return;
	}

	cout << "Please enter your password" << endl;
	cin >> password;

	cout << "Please enter your real name" << endl;
	cin.ignore();
	getline(cin,realName);

	cout << "Please enter your city" << endl;
	cin.ignore();
	getline(cin,city);


	User user = User(username, password, realName, city);
	network.addUser(user);
	return;
}

bool UI::loginPrompt() {
	string username, password;
	cout << "Enter your username" << endl;
	cin >> username;
	cout << "Enter your password" << endl;
	cin >> password;
	if (!network.userAlreadyExists(username)) {
		cout << "User not found. Returning to main menu." << endl;
		return false;
	}
	this->user = network.getUsers()->get(network.findUser(username));
	if (user.getPassword() == password) {
		return true;
	}
	else {
		return false;
	}
}

void UI::loginMenu() {
	// Should output friend requests and be able to accept or decline
	cout << '\n' << user.getWall()->toString();
	// cout << friend requests
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
		default:
		{
			cout << "That was not a valid option, please try again" << endl;
			break;
			return;
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
	network.getUsers()->set(network.findUser(user.getUsername()), user);
	return;
}

void UI::deleteWallPost() {
	int index;
	cout << "Enter a number corresponding to the wall post you would like to delete" << endl;
	cin >> index;
	user.deletePost(index);
	network.getUsers()->set(network.findUser(user.getUsername()), user);
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
	network.getUsers()->set(network.findUser(user.getUsername()), user);
	return;
}

void UI::deleteProfile() {
	network.deleteUser(network.findUser(user.getUsername()));
	logged_in = false;
	cout << "Profile deleted. Returning to Main menu" << endl;
}

void UI::searchUsers() {
	// Need to send friend requests to users from this list
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
	for (User* iter = network.getUsers()->begin(); iter != network.getUsers()->end(); iter++) {
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
			cout << "Username: " << iter->getUsername() << " ";
			cout << "Real Name: " << iter->getRealName() << endl;
		}
	}
	if(!found)
		cout << "User not found" << endl;
}

void UI::viewFriends() {
	// Need to delete friends from this list
}

void UI::logout() {
	cout << network.toString() << endl;
	logged_in = false;
	this->network.toFile();
	return;
}
