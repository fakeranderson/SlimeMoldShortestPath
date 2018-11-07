#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <vector>
class mazeGenerator
{
public:
	mazeGenerator();
	~mazeGenerator();
	std::vector<std::vector<int> > generateMazeMap(int n);
};


#endif // !MAZEGENERATOR_H


