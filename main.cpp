#include "UserNetwork.h"
#include "User.h"

using namespace std;

int main() {
	User* jon = new User();
	jon->setUsername("Jonathan");

	User* neeraj = new User();
	neeraj->setUsername("Neeraj");

	User* ish = new User();
	ish->setUsername("Ishi");

	User* amiri = new User();
	amiri->setUsername("Amiri");

	UserNetwork n = UserNetwork();

	n.addUser(*jon);
	n.addUser(*neeraj);
	n.addUser(*ish);
	n.addUser(*amiri);

	jon->sendFriendRequest(neeraj->getUsername(), &n);
	neeraj->acceptFriendRequest(jon->getUsername(), &n);

	neeraj->sendFriendRequest(ish->getUsername(), &n);
	ish->acceptFriendRequest(neeraj->getUsername(), &n);

	ish->sendFriendRequest(amiri->getUsername(), &n);
	amiri->acceptFriendRequest(ish->getUsername(), &n);

	User jonCopy = n.getUsers()->at(n.findUser(jon->getUsername()));
	jonCopy.setFriendPointers(n);

	User neerajCopy = n.getUsers()->at(n.findUser(neeraj->getUsername()));
	neerajCopy.setFriendPointers(n);

	User ishCopy = n.getUsers()->at(n.findUser(ish->getUsername()));
	ishCopy.setFriendPointers(n);

	User amiriCopy = n.getUsers()->at(n.findUser(amiri->getUsername()));
	amiriCopy.setFriendPointers(n);




	n.findShortestPath(jonCopy, amiriCopy);

	delete jon;
	delete neeraj;
	delete ish;
	delete amiri;


	return 0;
}