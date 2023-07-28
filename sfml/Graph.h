#pragma once
#include "Lib.h"
#include "Route.h"

class RouteGraph
{
	int size;
public:
	RouteGraph();

	vector<vector<int>> matrix;

	
	void add();
	void setEdge(const int, const int, const int = 1 ); 
	bool findPath(const int vsrc, const int vdest, vector <int>& vertexSet);

};

