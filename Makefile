all: cas

cas: main.o
	g++ -o cas main.o -std=c++11

main.o: main.cpp
	g++ -c main.cpp -std=c++11