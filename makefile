all: main.cpp Node.h Node.cpp Population.h Population.cpp
	mpic++ -std=c++11 -g -O3 main.cpp Node.cpp Population.cpp -o geneticBuddha
