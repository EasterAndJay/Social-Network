#ifndef UI_H
#define UI_H

#include <string>
#include "UserNetwork.h"
#include "User.h"

using namespace std;

class UI {
public:
	UI();
	~UI();
	void mainMenu();
	void newUserMenu();
	bool loginPrompt();
	void loginMenu();
	void logout();
	void run();
	void createWallPost();
	void deleteWallPost();
	void updateInformation();
	void deleteProfile();
	void viewFriends();
	void searchUsers();
	bool running = true;


private:
	User user;
	UserNetwork network;
	bool logged_in;

};

#endif