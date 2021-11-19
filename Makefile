.PHONY: main
main: main.cpp
	g++ -o main main.cpp -Ofast -march=native -std=c++11 -lpthread -lSDL2

debug: main.cpp
	g++ -o main main.cpp -g -march=native -std=c++11 -lpthread -lSDL2