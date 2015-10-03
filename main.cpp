// Basic file for testing implementations

#include "DoublyLinkedList.h"
#include "WallPost.h"
#include "Wall.h"
int main()
{
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

  WallPost myPost = WallPost("Hi this is my first post", "Jonathan Easterman", "9/30/2015");
  cout << myPost << endl;

  WallPost otherPost = WallPost();
  otherPost.setContent("And this is my second post");
  otherPost.setAuthor("Jonathan Easterman");
  otherPost.setTimePosted("9/30/2015");
  cout << otherPost.getAuthor() << otherPost.getContent() << otherPost.getTimePosted();
  cout << otherPost << endl;

  Wall myWall = Wall();

  WallPost wallPost = WallPost("Here is my wall!", "WallPost creator", "10/1/15");

  myWall.addPost(myPost);
  myWall.addPost(otherPost);
  //myWall.deletePost(myPost);
  myWall.addPost(wallPost);

  cout << myWall.toString() << endl;

  cout << "end of program!" << endl;

  return 0;
}