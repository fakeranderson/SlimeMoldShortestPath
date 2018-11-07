all: BestPaths

main.o: main.cpp main.h
	g++ -Wall -g -std=gnu++11 -c main.cpp

BestPaths: main.o
	g++ -Wall -std=gnu++11 -g -o BestPaths main.o

clean:
	rm -r *.o BestPaths
