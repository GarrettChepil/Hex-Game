#pragma once

#include <vector>
using namespace std;

// structure to represent an edge and store its target and cost
struct Edge
{
	int target;
	int source;
	double cost;
	Edge(){};
	Edge(int arg_target, int arg_source, double arg_cost)
		: target(arg_target), source(arg_source), cost(arg_cost){}
};

// structure to represent a vertices in the graph
struct Node
{
	// valude to be printed on the board if a player has chosen it
	char value;
	int nodeNum;
	vector<Edge>  edges;	//vector of edges the vetices is conected too
	Node(){ value = '.'; }  // sets the value to ., which represents an empty space
};