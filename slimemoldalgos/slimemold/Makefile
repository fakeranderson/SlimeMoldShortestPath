CXX = g++ 
CXXFLAGS = -std=c++11 -Wall -ansi -pedantic -g 

all: slimemold

slimemold: main.o smsp.o mazeGenerator.o
	$(CXX) $(CXXFLAGS) -o slimemold main.o smsp.o mazeGenerator.o

main.o: main.cpp smsp.h mazeGenerator.h
	$(CXX) $(CXXFLAGS) -c  main.cpp smsp.cpp mazeGenerator.cpp

mazeGenerator.o: mazeGenerator.cpp mazeGenerator.h
	$(CXX) $(CXXFLAGS) -c mazeGenerator.cpp

smsp.o: smsp.cpp smsp.h
	$(CXX) $(CXXFLAGS) -c smsp.cpp 

.PHONY: clean
clean:
	rm -f *.o slimemold	
