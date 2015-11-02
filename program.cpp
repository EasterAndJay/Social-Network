#include <iostream>
#include <fstream>
#include "WallPost.h"
#include "Wall.h"
#include "User.h"
#include "UserNetwork.h"
#include "UI.h"
using namespace std;



int main() {

	/*UserNetwork network = UserNetwork();
	network.readFromFile();
	
	mainMenu(network);

	//cout << network.toString() << endl;
	network.toFile();
	network.readFromFile();
	//cout << network.toString() << endl;*/


	UI menu = UI();
	menu.run();
	return 0;
}
