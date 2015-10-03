# MakeFile for Social network project for CS 130A

CC = g++

CFLAGS = -Wall -g
OBJECTS = main.o WallPost.o Wall.o
TARGET = run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

WallPost.o: WallPost.cpp
	$(CC) $(CFLAGS) -c WallPost.cpp

Wall.o: Wall.cpp
	$(CC) $(CFLAGS) -c Wall.cpp

clean:
	$(RM) $(TARGET) $(OBJECTS)