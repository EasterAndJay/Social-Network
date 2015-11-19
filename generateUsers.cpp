#include "UserNetwork.h"
#include <random>

using namespace std;
int main() {
	UserNetwork network = UserNetwork();
	//vector<User> users;
	/*User user;
	int random;
	typedef std::minstd_rand G;
    G g;
    typedef std::uniform_int_distribution<> D;
    D d(0, 9999);

	for(int i = 0; i < 10000; i++) {
		user = User(to_string(i),"a",to_string(i),"MB");

		user.addPost(WallPost(to_string(i + 100), to_string(i)));
		user.addPost(WallPost(to_string(i + 99), to_string(i)));
		user.addPost(WallPost(to_string(i + 500), to_string(i)));
		user.addPost(WallPost(to_string(i + 1000), to_string(i)));

		network.addUser(user);
		users.insert(users.begin(), user);
		
	}

	for (auto iter = users.begin(); iter != users.end(); ++iter) {
		for (int j = 0; j < 100; j++) {
			random = d(g);
			cout << random << endl;
			iter->sendFriendRequest(to_string(random)	, &network);
		}
	}

	for (auto iter = users.begin(); iter != users.end(); ++iter) {
		for (auto request = iter->getFriendRequests().begin(); request != iter->getFriendRequests().end(); ++request) {
			random = d(g);
			cout << random << endl;
			iter->acceptFriendRequest(*request, &network);
		}
	}
*/
	network.readFromFile();
	for (auto iter = network.getUsers()->begin(); iter != network.getUsers()->end(); ++iter) {
		//iter->setFriendRequestPointers();
		bool going = true;
		while(going) {// = iter->getFriendRequests().begin(); request != iter->getFriendRequests().end(); ++request) {
			cout << iter->toString() << endl;
			try {
				iter->acceptFriendRequest(iter->getFriendRequests().at(0), &network);
			} catch(std::out_of_range& e) {
				going = false;
			}
			cout << iter->toString() << endl;
		}
	}
	network.toFile();
	return 0;
}