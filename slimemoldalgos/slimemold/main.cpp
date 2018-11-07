#include "smsp.h"
#include "mazeGenerator.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdio.h>

using namespace std;

//Print Vector
void printVector(vector<vector<int> > pathMap)
{
	cout<<"Map: "<<endl;

	cout<<"	";
	for(unsigned int i = 0; i < pathMap.size(); i++) {
		cout<<i<<"	";
	}
	cout<<endl<<endl;
	for(unsigned int i = 0; i < pathMap.size(); i++) {
		cout<< i <<"	";
		for (unsigned int j = 0; j < pathMap[i].size();j++) {
			cout<<pathMap[i][j]<<"	";
		}
		cout<<endl;
	}
	cout<<endl;
}


//Floyd's Algorithm 1
vector<vector<int> > floyd(vector<vector<int> > pathMap) {
	vector<vector<int> > D = pathMap;
	int i, j, k;
	int n = pathMap.size();
	for(k = 0; k < n;k++) {
		for(i = 0; i < n;i++) {
			for(j = 0; j < n; j++) {
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
			}
		}
	}
	return D;
}




int main()
{
	srand(time(NULL));
	mazeGenerator mg;
	int n, trialCount = 100;
	vector<vector<int> > maze;
	long nanos = 0;
	double aveNanos = 0.0;
	cout<< "Enter Matrix N Dimension: "<<endl;
	cin>>n;

	while(true)
	{
		smsp tempMold;
		vector<int> tempPath;

		maze = mg.generateMazeMap(n);
		tempPath = tempMold.slimePath(maze);
		if (!tempPath.empty())
		{
			break;
		} else 
		{
			printf("Maze not solveable... Regenerating.\r");;
		} 
	} cout << endl;

	for(int i = 0; i < trialCount; i++) //trials to be averaged
	{
		vector<int> slimepath;
		smsp slimemold;
		slimepath = slimemold.slimePath(maze);
		nanos += slimemold.getNanos();
	} 
	aveNanos = (double) nanos/trialCount;
	cout << "Average nanos: " << aveNanos << endl;
	//printVector(maze);
	/*
		 cout << "Path is" << endl;

		 for (unsigned int i = 0; i < slimepath.size(); i++)
		 {
		 cout << " " << slimepath.at(i);
		 }

		 cout<<endl;
	 */
	return 0;
}
