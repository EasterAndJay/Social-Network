#include <iostream>
#include <fstream>
#include "DoublyLinkedList.h"
#include "WallPost.h"
#include "Wall.h"
#include "User.h"
#include "UserNetwork.h"
using namespace std;

// Make this come from our file
UserNetwork network = UserNetwork();
network.readFromFile();

void createUser() {
	string username, password, realName, city;

	cout << "Please enter your desired username" << endl;
	
	cin >> username;

	if (network.userAlreadyExists(username)) {
		cout << "Sorry that username already exists, please try again" << endl;
		createUser();
	}
	cout << "Please enter your password" << endl;
	cin >> password;
	cout << "Please enter your real name" << endl;
	cin >> realName;
	cout << "Please enter your city" << endl;
	cin >> city;

	network.addUser(User(username,password,realName,city));
}

// returns to main menu if user not found
bool login(string username, string password) {
	User user = network.findUser(username);
	if (user.getUsername() == "") {
		cout << "User not found. Returning to main menu." << endl;
		return false;
	}
	if (user.getPassword() == password) {
		user.getWall()->toString();
		return true;
	}
}


void mainMenu() {
	cout << "Type 'a' to create a new user, type 'b' to Log in, type 'c' to quit" << endl;
	char option;
	cin >> option;
	switch (option) {
			case 'a':
				createUser();
				break;
			case 'b':
				string username, password;
				cout << "Enter your username" << endl;
				cin >> username;
				cout << "Enter your password" << endl;
				cin >> password;
				login(username, password);
				break;
			case 'c':
				exit(0);
				break;
			default:
				cout << "Sorry that was not a valid option, please try again." << endl;
				mainMenu();
		}
}




int main() {
	// Name of file with user information
	string fileName = "test.txt";
	string line;
	// input file stream object for reading from file
	std::ifstream usersInfo(fileName);
	
	// While loop that reads line by line until EOF
	while(getline(usersInfo, line)) {
		cout << line << endl;
	}
	// close
	usersInfo.close();
	// This just printed everything in our UserNetwork file ^
	mainMenu();
	


return 0;
}
