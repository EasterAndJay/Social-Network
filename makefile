# MakeFile for Social network project for CS 130A

CC = g++

CFLAGS = -Wall -g -std=c++11
OBJECTS = program.o WallPost.o Wall.o User.o UserNetwork.o
TARGET = run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -g -o $(TARGET) $(OBJECTS)

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp

WallPost.o: WallPost.cpp
	$(CC) $(CFLAGS) -c WallPost.cpp

Wall.o: Wall.cpp
	$(CC) $(CFLAGS) -c Wall.cpp
	
User.o: User.cpp
	$(CC) $(CFLAGS) -c User.cpp

UserNetwork.o: UserNetwork.cpp
	$(CC) $(CFLAGS) -c UserNetwork.cpp

program.o: program.cpp
	$(CC) $(CFLAGS) -c program.cpp

clean:
	$(RM) $(TARGET) $(OBJECTS)
