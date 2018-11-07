//this program will simulate how a slime mold finds the shortest path in a maze

/**
  The map is a 2d vector, so the slime mold will travel from it's current position down the maze paths path until it finds food
  -Food location is at the lowest right index of the map array, aka vertex n in an nxn adjacency matrix.
  -Starting location is 0,0

 */

#include "smsp.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <sys/time.h>

std::vector<int> smsp::slimePath(std::vector<std::vector<int> > adjMatrix){

	int n = adjMatrix.size();
	//promisingPaths is the set of paths the slime mold will take to the food	
	std::vector<std::vector<int> > promisingPaths;
	//shortestPaths is the overall set of shortest paths that the slime mold discovers
	//***** not necessary unless there is more than one piece of food on the map
	//std::vector<std::vector<int>> shortestPaths;

	//vector where each location turns true when a slime mold has 
	//occupied (grown into) that spot, because a slime mold does not grow over itself
	std::vector<std::vector<bool> > occupado;

	for (int k = 0; k < n; k++)
	{
		occupado.push_back(std::vector<bool>());
		for (int l = 0; l < n; l++)
		{
			occupado[k].push_back(false);
		}

	}


	r = 0;

	gettimeofday(&start, NULL);

	//main while loop, runs until current location is last
	while( r < n )
	{	
		j = 0; //potential next vertex
		i = 0; //current vertex location

		//the list of vertexes taken on the current path only. Reset after a path is completed.
		std::vector<int> currentPath;
		currentPath.push_back(0);

		/**while j<n, asks: 
		 * 1) if the current vertex hasn't already been grown into by previous mold arm,
		 * 2) if the current vertex is 1 (meaning a path exists),
		 * 3) if that vertex has not already been added to current path history (no circuits).
		 * 	-if so, then-
		 *    -Push the current location into the current path.
		 *    -Reassign current location to vertex representing the next location.
		 *    -Reset next potential vertex to 0, restarting the search from current vertex, which is i
		 *
		 * When current location is the nth vertex (bottom right location in the maze),
		 * then the food has been found, and the first vertex is saved (so the alg doesn't retread it),
		 * and current path is stored into the promising paths
		 */

		while(j < n)
		{ 	
			//printf("i: %d, j: %d, r: %d, n: %d", i, j, r, n);
			if(occupado[i][j]==false && adjMatrix[i][j]==1 && 
					std::find(currentPath.begin(), currentPath.end(), j) == currentPath.end())
			{
				currentPath.push_back(j);
				occupado[i][j] = true;
				i = j;
				j = 0;

			} else j++;
			//check if food is reached
			if (i == n - 1)
			{
				//std::cout << "\nFound food at "<< i << std::endl;
				promisingPaths.push_back(currentPath);
				// TODO when food is found, should backtrack to previous not, not start
				//r = currentPath.at(1);
				break;
			}	//else r = n;

			if(j == n - 1 && adjMatrix[i][n-1] != 1) //if j has reached the last vertex and the last vertex is not reachable from position i
			{
				if(currentPath.size() <= 1)
				{
					r = n;
					break;
				}
				occupado[i][j] = true; //set new vertex to occupied, so slime mold doesnt use it again 
				currentPath.pop_back();  //remove this vertex from the current path (backtrack)
				i = currentPath.at(currentPath.size()-1); // set i to previous vertex
				j = 0; //sets search back to 0
			} 
		}
	}

	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = (end.tv_sec*1e6 + end.tv_usec) - (start.tv_sec*1e6 + start.tv_usec);
	//mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

	std::vector<int>  tempPath;


	if (!promisingPaths.empty())
	{
		tempPath  = promisingPaths[0]; 


		for (unsigned int i = 1; i < promisingPaths.size(); i++)
		{
			if(tempPath.size() > promisingPaths[i].size())
			{	
				tempPath = promisingPaths.at(0);
			} 
		}

	}
	return tempPath;

}

long smsp::getNanos()
{
	return useconds;
}
