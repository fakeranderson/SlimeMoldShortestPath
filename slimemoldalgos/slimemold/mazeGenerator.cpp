#include "mazeGenerator.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

mazeGenerator::mazeGenerator()
{
	
}



std::vector<std::vector<int> > mazeGenerator::generateMazeMap(int n)
{

	std::vector<std::vector<int> > pathMap;
	int root = std::sqrt(n);
	for (int i = 0; i < n; i++) {
		std::vector<int> pathRow;
		for (int j = 0; j < n; j++) {
			if (j == i) pathRow.push_back(0);
			else {
				if ((std::abs(j%root - i % root) <= 1 && std::abs(j - i) <= 1) || ((std::abs(j - i) <= root) && ((i + 1) % root) == ((j + 1) % root))) {
					pathRow.push_back(rand() % 2);
					if (pathRow[j] <= 0) pathRow[j] = 1000;
					else pathRow[j] = 1;
				}
				else pathRow.push_back(1000);
			}
		}
		pathMap.push_back(pathRow);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			pathMap[j][i] = pathMap[i][j];
		}
	}

	return pathMap;
}

mazeGenerator::~mazeGenerator()
{
}
