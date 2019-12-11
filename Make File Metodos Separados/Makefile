CC=g++
CFLAGS=-c -Wall

all: exe

exe: main.o Intercala.o MergeSort.o
	$(CC) main.o Intercala.o MergeSort.o -o Exe

main.o: main.cpp Intercala.o MergeSort.o
	$(CC) $(CFLAGS) main.cpp

Intercala.o: Intercala.cpp MergeSort.o
	$(CC) $(CFLAGS) Intercala.cpp

MergeSort.o: MergeSort.cpp
	$(CC) $(CFLAGS)	MergeSort.cpp

clean:
	rm -rf *o Exe
