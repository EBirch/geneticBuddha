all: main.cpp Node.h Node.cpp
	mpic++ -std=c++11 -g -O3 main.cpp Node.cpp -o geneticBuddha
