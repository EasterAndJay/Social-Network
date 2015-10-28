#ifndef FRIENDREQUEST_H
#define FRIENDREQUEST_H

#include <iostream>

class FriendRequest {

public:
	FriendRequest(string sender_, string receiver_) : sender(sender_), reciever(reciever_) {};


private:
	User sender;
	User receiver;


}

#endif
