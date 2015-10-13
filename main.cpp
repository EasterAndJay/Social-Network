// Basic file for testing implementations

#include "DoublyLinkedList.h"
#include "WallPost.h"
#include "Wall.h"
int main()
{
  /*
  DoublyLinkedList<int> dll;

  dll.addToEnd(1);
  dll.addToEnd(2);
  dll.addToEnd(3);
  dll.addToEnd(4);
  dll.addToEnd(5);

  cout << dll << endl;
  DoublyLinkedList<int> dll2(dll);
  cout << dll2 << endl;

  dll.deleteByValue(3);
  dll.deleteByValue(1);
  dll.deleteByValue(5);

  cout << dll << endl;
  cout << dll2 << endl;

  cout << dll.getHead()->data << endl;
  */
  
  WallPost myPost = WallPost("Hi this is my first post", "Jonathan Easterman");
  //cout << myPost << endl;

  WallPost otherPost = WallPost();
  otherPost.setContent("And this is my second post");
  otherPost.setAuthor("Jonathan Easterman");
  otherPost.setTimePosted();
  //cout << otherPost.getAuthor() << otherPost.getContent() << otherPost.getTimePosted() << endl;
  //cout << otherPost << endl;

  Wall myWall = Wall();

  WallPost wallPost = WallPost("Here is my wall!", "WallPost creator");

  myWall.addPost(myPost);
  myWall.addPost(otherPost);
  //myWall.deletePost(myPost);
  myWall.addPost(wallPost);
  
  cout << myWall.toString() << endl;
  cout << "\n\n^%^%^&%^&%^&------DESIRED CONTENT ABOVE%$^$%^$%^%$\n\n";
  
  string myWallStr = myWall.toString();
  Wall myOtherWall = Wall();
  myOtherWall.readWallPostsFromString(myWallStr);

  cout << myOtherWall.toString() << endl;


  //cout << myWall.toString() << endl;

  cout << "end of program!" << endl;

  return 0;
}
