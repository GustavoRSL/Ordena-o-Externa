CC=g++
CFLAGS=-c -Wall

all: exe

exe: main.o metodos.o
	$(CC) main.o metodos.o -o Exe

main.o: main.cpp metodos.o
	$(CC) $(CFLAGS) main.cpp

metodos.o: metodos.cpp
	$(CC) $(CFLAGS) metodos.cpp

clean:
	rm -rf *o Exe
