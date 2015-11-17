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

	jon->addFriend(neeraj->getUsername());

	neeraj->addFriend(ish->getUsername());

	ish->addFriend(amiri->getUsername());

	n.findShortestPath(*jon, *amiri);



	return 0;
}