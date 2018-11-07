#include "main.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include <cmath> 
#include <algorithm>
using namespace std;


//=======MAP GENERATION AND PRINTING======//

//Generates Map
vector<vector<int>> generatePathMap(int n)
{
	
	vector<vector<int>> pathMap;
	
	for (int i = 0; i < n; i++) {
		vector<int> pathRow;
		for(int j = 0; j < n; j++) {
			if(j == i) {
				pathRow.push_back(0);
			} else {
				pathRow.push_back((rand()%10) - 2);	
				if(pathRow[j] <= 0) pathRow[j] = 1000;
			}
			if(i==0&&j==n-1)pathRow[j] = 1000;
		}
		pathMap.push_back(pathRow);
	}	

	return pathMap;
}

//Generate Maze
vector<vector<int>> generateMazeMap(int n)
{
	
	vector<vector<int>> pathMap;
	int root = sqrt(n);	
	for (int i = 0; i < n; i++) {
		vector<int> pathRow;
		for(int j = 0; j < n; j++) {
			if(j==i) pathRow.push_back(0);
			else {
				if((abs(j%root - i%root) <= 1 && abs(j-i)<=1) || ((abs(j-i) <= root) && ((i+1) % root) == ((j+1) % root))) {
					pathRow.push_back(rand()%2);	
					if(pathRow[j] <= 0) pathRow[j] = 1000;
					else pathRow[j] = 1;
				} else pathRow.push_back(1000);
			}
		}
		pathMap.push_back(pathRow);
	}	
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n;j++) {
		pathMap[j][i] = pathMap[i][j];
		}
	}
	

	return pathMap;
}


//Print Vector
void printVector(vector<vector<int>> pathMap)
{
	cout<<"Map: "<<endl;

	cout<<" 	";	
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
}


//======Floyd's Algorithms======//

//Floyd's Algorithm 1
vector<vector<int>> floyd(vector<vector<int>> pathMap) {
	vector<vector<int>> D = pathMap;
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

//Floyd's Algorithm 2
vector<vector<int>> floyd2(vector<vector<int>> pathMap) {
	vector<vector<int>> D = pathMap;
	vector<vector<int>> P;
	int i, j, k;
	int n = pathMap.size();
	for (int i = 0; i < n; i++) {
		vector<int> pathRow;
		for(int j = 0; j < n; j++) {
			pathRow.push_back(0);
		}
		P.push_back(pathRow);
	}	

	for(k = 0; k < n;k++) {
		for(i = 0; i < n;i++) {
			for(j = 0; j < n; j++) {
				if(D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
	return P;

}


//Print Floyd's
void printFloyd(vector<vector<int>> sortedPathMap, int x, int y) {
	if(sortedPathMap[x][y]!=0) {
		printFloyd(sortedPathMap, x,sortedPathMap[x][y]);
		cout<<"v"<<sortedPathMap[x][y]<<" ";
		printFloyd(sortedPathMap, sortedPathMap[x][y],y);
	}

}

//======DJIKSTRA'S ALGORITHM======//
int minDistance(int dist[], bool sptSet[], int n) {
	int min = 1000;
	int min_index;
	for(int j = 0; j < n; j++) {
		if(sptSet[j]==false && dist[j]<=min) {
			min = dist[j],min_index = j;
		}	
	}
	return min_index;
}

void printSolution(int dist[], int n)
{
   if (dist[n-1] < 1000) {
		cout<<endl<<endl<<"The distance from Point 0 to Point "<<n-1<<" is "<<dist[n-1]<<"."<<endl; 
	}
}

void djikstra(vector<vector<int>> pathMap) {
	int i;
	int n = pathMap.size();
	int dist[n];
	bool  sptSet[n];

	for(i=1; i < n; i++) {
		dist[i] = 1000;
		sptSet[i] = false;
	} 

	dist[0] = 0;
		
	for(int j = 0; j < n-1;j++)
	{
		int u = minDistance(dist,sptSet,n);

		sptSet[u] = true;
		
		for(i = 0; i < n; i++) {
			if(!sptSet[i] && pathMap[u][i] && dist[u]!= 1000&&dist[u]+pathMap[u][i] < dist[i]) {
			dist[i] = dist[u] + pathMap[u][i];
			}
		}
		
	}

	printSolution(dist,n);
}



/*
//===== SLIME MOLD ALGORITHM =====//

//Handles building and comparing branches
vector<vector<int>> slimeMoldSpreader(vector<vector<int>> pathMap,vector<int> branch, unsigned int shortestPath, vector<vector<int>> branches) {
	
	if(branch.size() > shortestPath) return branches;

	int n = pathMap.size();
		
	for(int i = 0; i < n; i ++) {
		if(pathMap[branch[branch.size()-1]][i] == 1 && find(branch.begin(), branch.end(), i) == branch.end()) {
			if(i == n-1) branches.push_back(branch); 
			else slimeMoldSpreader(pathMap, branch, shortestPath, branches);
		}
	}

	return branches;
}




//Takes in map and initiates path building/manages path building
vector<int> slimeMoldHandler(vector<vector<int>> pathMap) {
	
	int n = pathMap.size();
	unsigned int shortest = pathMap[0][n-1];
	vector<int> shortestPath;

	vector<vector<int>> branches;
	
	
	
	//Skims top row of pathMap to create initial branches
	for(int j = 0; j < n; j++) {
		
		if(pathMap[0][j] == 1) {
			vector<int> branch;
			branch.push_back(0);
			branch.push_back(j);
			branches = slimeMoldSpreader(pathMap, branch, shortest, branches);

			for(unsigned int i = 0; i < branches.size(); i++) {
				if(branches[i].size() < shortest) {
					shortest = branches[i].size();
					shortestPath = branches[i];
				}
			}
		}
		
	}

	for(unsigned int i = 0; i < shortestPath.size(); i++) {
		cout<<" "<<shortestPath[i];
	}


	return shortestPath;
}*/


//Displays output from shortest path algos
void shortestPathDisplay() {
	cout<<"Enter array size (NxN):"<<endl;
	int n;
	cin>>n;

	srand(time(NULL));
	vector<vector<int>> mazeMap;

	while (true) {
		mazeMap = generateMazeMap(n);
		if(floyd(mazeMap)[0][n-1] != 1000) break;
	}
	cout<<"Weighted Maze ";
	printVector(mazeMap);

	

	cout<<endl<<"Floyd's Vertex Distance ";
	printVector(floyd(mazeMap));	

	cout<<endl<<"Floyd's: "<<endl<<endl<<"The distance from Point 0 to Point "<< n-1<< " is " <<floyd(mazeMap)[0][n-1]<<".";
	cout<<endl<<endl<<"The path from Point 0 to Point "<< n-1<<" goes through: "<< endl;
	printFloyd(floyd2(mazeMap),0,n-1);	
	cout<<"(If empty, no intermediate Points)"<<endl;	
	cout<<endl<<endl<<endl<<"Djikstra's: ";
	djikstra(mazeMap);
	cout<<"."<<endl;

	//slimeMoldHandler(mazeMap);

	cout<<endl;
}

//Main
int main()
{	
	shortestPathDisplay();	
	return 0;
}

