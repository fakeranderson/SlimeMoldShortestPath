#pragma once
#ifndef SMSP_H
#define SMSP_H

#include <vector>
#include <algorithm>

class smsp
{
public:
	std::vector<int> slimePath(std::vector<std::vector<int> > adjMatrix);
	long getNanos();
private:
	int n, j, i, r;
	int path;
	static std::vector<std::vector<int> > promisingPaths;	
	static std::vector<std::vector<bool> > occupado;
	struct timeval start, end;
	long mtime, seconds, useconds;
	
};

#endif // !"SMSP_H"
