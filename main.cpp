// Basic file for testing implementations

#include "DoublyLinkedList.h"
#include "WallPost.h"
#include "Wall.h"
#include "User.h"
#include "UserNetwork.h"
#include "ArrayList.h"

int main()
{ 
  

  /*ArrayList<int> ints = ArrayList<int>();

  for (int i = 0; i < 1000; i++) {
    ints.insert(i, i);
    
  }

  for (int i = 0; i < 500; i++) {
    ints.remove(0);
    
  }

  for (int i = 0; i < 200; i++) {
    ints.set(i, i);
    
  }
  for (int i = 0; i < 210; i++) {
    cout << ints.get(i) << " " << endl;
    
  }*/

  //Wall myWall = Wall();


  //myWall.addPost(myPost);
  //cout << ints << endl;



  //cout << ints << endl;
  //User* Ishi = new User("ishi123", "pass", "Ishi von Meier", "Sebastopol");
  //cout << Ishi->toString() << endl;
  
  
  // ArrayList<User*> myFriends = ArrayList<User*>();
  // myFriends.insert(0, Ishi);
  
  // cout << "List so far:" << endl;
  
  // User* friendData = myFriends.get(0);
  
  // cout << friendData->toString() << endl;
  
  
  
  
 
  WallPost myPost = WallPost("Hi this is my first post", "Jonathan Easterman");
//   cout << myPost << endl;

 WallPost otherPost = WallPost();
  otherPost.setContent("And this is my second post");
  otherPost.setAuthor("Jonathan Easterman");
  otherPost.setTimePosted();
//   cout << otherPost.getAuthor() << otherPost.getContent() << otherPost.getTimePosted() << endl;
//   cout << otherPost << endl;

//   Wall myWall = Wall();

 WallPost wallPost = WallPost("Here is my wall!", "WallPost creator");

//   myWall.addPost(myPost);
// //segfault
//   cout << "make it here?" << endl;
//   myWall.addPost(otherPost);

//   myWall.deletePost(0);
//   myWall.addPost(wallPost);


  


  // Wall newWall = Wall(myWall);
  
  // myWall.deletePost(0);
  
  // cout << newWall.toString() << endl;
  
 
  // cout << myWall.toString() << endl;
  // cout << "\n\n^%^%^&%^&%^&------DESIRED CONTENT ABOVE%$^$%^$%^%$\n\n";
  
  // cout << myWall.toString() << endl;
  
  // string myWallStr = myWall.toString();
  // Wall myOtherWall = Wall();
  // myOtherWall.readWallPostsFromString(myWallStr);

  // cout << myOtherWall.toString() << endl;
/*
    Wall myWall = Wall();
    myWall.addPost(otherPost);
    myWall.addPost(wallPost);

    Wall newWall = Wall(myWall);
    myWall.deletePost(0);

    cout << myWall.toString() << endl;

    cout << "Above is myWall. should have 1 post" << endl;
    cout << newWall.toString() << endl;
    cout << "Above is newWall. Should have 2 posts" << endl;
*/

User Marty = User("Marty", "qwerty", "Sweet Balls", "Goleter");
User Queef = User("bob", "badpass", "Bob Queefs", "SB");
Queef.addPost(wallPost);
User Ish = User("feshies", "pass123", "Ishi von Meier", "Goleta, CA");
Ish.addPost(otherPost);
User Jon = User("jonny", "pass234", "Jonathan Beasterman", "Queefville, CA");
Jon.addPost(myPost);

UserNetwork* myNetwork = new UserNetwork();

myNetwork->addUser(Ish);
myNetwork->addUser(Marty);
//myNetwork->addUser(Queef);
//myNetwork->addUser(Jon);

//myNetwork->howManyFriendsUsersHave();

//cout << "sending one friend request..." << endl;
//Marty.sendFriendRequest(&Ish);
//cout << "Trying to send a duplicate friend request..." << endl;
//Jon.sendFriendRequest(&Ish);
//cout << "Queef sending ish a friend request....." <<endl;
//Queef.sendFriendRequest(&Ish);
//cout << "Marty sending ish a friend request....." <<endl;
//Marty.sendFriendRequest(&Ish);

//cout << "Ishi accepting 1 friend request...." << endl;
//Ish.acceptFriendRequest(0);

//myNetwork->howManyFriendsUsersHave();
//cout << Marty.toString() << endl;

myNetwork->sendFriendRequest(2,0);

//User *copyMarty= new User(myNetwork->getUsers()->get(0));

//cout << copyMarty.toString() << endl;

/*
cout << "~~~trying to see one user on mynetwork~~~~" << endl;
ArrayList<User>* myArrPtr = myNetwork->getUsers();
User faggot = myArrPtr->get(0);
cout << faggot.toString() << endl;
*/

//cout << "now trying it on the network....." << endl;

myNetwork->toFile();

//cout << "trying to print from user a 2nd time" << endl;
//cout << Ish.toString() << endl;

//cout << Ish.toString() << endl;



/*
cout << "sending one friend request..." << endl;
Jon->sendFriendRequest(Ish);
cout << "Trying to send a duplicate friend request..." << endl;
Jon->sendFriendRequest(Ish);
cout << "Queef sending ish a friend request....." <<endl;
Queef->sendFriendRequest(Ish);
cout << "Marty sending ish a friend request....." <<endl;
Marty->sendFriendRequest(Ish);

cout << "Ishi accepting 1 friend request...." << endl;
Ish->acceptFriendRequest(0);
Ish->acceptFriendRequest(0);
cout << "These are Ishi's friends: " << endl;
cout << Ish->getFriends().get(0)->getUsername() << endl;
cout << Ish->getFriends().get(1)->getUsername() << endl;

cout << "Trying toString...." << endl;
cout << Ish->toString() << endl;

copyIsh = User(Ish->toString, )
*/

/*.get(0)->getUsername() << endl;
cout << Ish->getFriendRequests()
cout << Ish->getFriendRequests().get(1)->getUsername() << endl;


cout << "deleting friend request at index 1:" << endl;
Ish->deleteFriendRequest(1);

cout << "These are Ishi's friend requests now: " << endl;
cout << Ish->getFriendRequests().get(0)->getUsername() << endl;

try {
  cout << Ish->getFriendRequests().get(1)->getUsername() << endl;
} catch (int& e) {
  cout << "No request at index 1" << endl;
}*/
//cout << Ish->getFriendRequests().get(1)->getUsername() << endl;



 /*
  cout << "trying read from string......." << endl;

  // cout << "\n\n^%^%^&%^&%^&------DESIRED CONTENT ABOVE%$^$%^$%^%$\n\n";
  string ishUserString = Ish->toString();
  User copyIsh = User(ishUserString);
  cout << "now printing out what our read in and back out gives us:....."   <<endl;
  cout << copyIsh.toString() << endl;
*/
  // Ish.sendFriendRequest(&Jon);
  // Jon.acceptFriendRequest(0);

  // cout << Ish.toString() << endl;

  
  
  // cout << "trying to add duplicate user..." << endl;
  // myNetwork.addUser(Ish);
  // cout << "trying to add second user..." << endl;
  // myNetwork.addUser(Jon);
  // cout<< "trying to delete first User....." <<endl;
  // myNetwork.deleteUser(Ish);
/*
  cout << "trying toString(): ....." << endl;
  string stringToRead = myNetwork.toString();
  cout << myNetwork.toString() << endl;
  
  cout << "trying to write to file....." << endl;
  myNetwork.toFile();
  cout << "trying to read from a file ....." <<endl;
  UserNetwork copyNetwork = UserNetwork();
  copyNetwork.readFromFile();
  cout << copyNetwork.toString() << endl;
  
  cout << "WE GOT THE FUCKING STRING FROM THE FILE" << endl;
  
  cout << "\n\n^%^%^&%^&%^&------DESIRED CONTENT ABOVE%$^$%^$%^%$\n\n";

  copyNetwork.readUserNetworkFromString(stringToRead);
  cout << "string we read: ...." << endl;
  cout << copyNetwork.toString() << endl;
  

  cout << "end of program!" << endl;*/

  return 0;
}
