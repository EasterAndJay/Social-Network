# MakeFile for Social network project for CS 130A

CC = g++

CFLAGS =  -Wall -g -std=c++11
OBJECTS = program.o WallPost.o WallPostResponse.o Wall.o User.o UserNetwork.o UI.o
TESTOBJECTS = testList.o Wall.o WallPost.o
TARGET = run
LIST = testList

all: $(TARGET)

test: $(LIST)

$(LIST): $(TESTOBJECTS)
	$(CC) $(CFLAGS) -g -o $(LIST) $(TESTOBJECTS)

testList.o: testList.cpp
	$(CC) $(CFLAGS) -c testList.cpp

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -g -o $(TARGET) $(OBJECTS)

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp

WallPost.o: WallPost.cpp
	$(CC) $(CFLAGS) -c WallPost.cpp

WallPostResponse.o: WallPostResponse.cpp
	$(CC) $(CFLAGS) -c WallPostResponse.cpp

Wall.o: Wall.cpp
	$(CC) $(CFLAGS) -c Wall.cpp
	
User.o: User.cpp
	$(CC) $(CFLAGS) -c User.cpp

UserNetwork.o: UserNetwork.cpp
	$(CC) $(CFLAGS) -c UserNetwork.cpp

UI.o: UI.cpp
	$(CC) $(CFLAGS) -c UI.cpp

program.o: program.cpp
	$(CC) $(CFLAGS) -c program.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

generateUsers.o: generateUsers.cpp
	$(CC) $(CFLAGS) -c generateUsers.cpp

clean:
	$(RM) $(TARGET) $(OBJECTS) $(TESTOBJECTS)
