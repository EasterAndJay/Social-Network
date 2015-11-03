# MakeFile for Social network project for CS 130A

CC = clang++

CFLAGS =  -Wall -g -std=c++11
OBJECTS = main.o WallPost.o Wall.o User.o UserNetwork.o
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

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

main2.o: main2.cpp
	$(CC) $(CFLAGS) -c main2.cpp

WallPost.o: WallPost.cpp
	$(CC) $(CFLAGS) -c WallPost.cpp

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

clean:
	$(RM) $(TARGET) $(OBJECTS) $(TESTOBJECTS)
