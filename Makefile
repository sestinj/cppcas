all: cas

cas: main.o
	g++ -o cas main.o

main.o: main.cpp
	g++ -c main.cpp