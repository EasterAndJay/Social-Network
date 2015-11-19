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
	void run();
	void mainMenu();
	void newUserMenu();
	bool loginPrompt();
	void loginMenu();
	void createWallPost();
	void createWallPostOnFriendsWall();
	void deleteWallPost();
	void deleteWallPostOnFriendsWall();
	void updateInformation();
	void deleteProfile();
	void searchUsers();
	void viewFriends();
	void deleteFriend(int atIndex);
	void viewWall(int atIndex);
	void addResponse(int postIndex, int chosenFriendIndex);
	void deleteResponse(int postIndex, int chosenFriendIndex);
	void viewFriendRequests();
	void degreeOfSeparationMenu();
	void logout();
private:
	User* user;
	UserNetwork network;
	bool logged_in = false;
	bool running = true;

};

#endif