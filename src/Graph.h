#pragma once

#include <vector>
#include <fstream>
#include "Node.h"

using namespace std;

// class for the graph object
class Graph
{
public:
	// constructors
	Graph(void);
	Graph(int numNodes);		
	Graph(ifstream& ifp);		// generate a graph from a file
	Graph(double density, double minRange, const double maxRange, int numNodes); //generate a random graph
	~Graph(void);

	// methods
	void GenerateRandom(double density, double minRange, double maxRange, int numNodes);
	void GeneratefromFile(ifstream& ifp);
	void addEdge(int target, int source, double cost);
	void delEdge(int target, int source);
	int V();		// returns the number of verticies in the graph
	int E();		// returns the number of edges in the graph
	bool adjacent(int target, int source);	// checks if the edge is in the graph
	vector<Edge> neighbors(int x);		// returns a vector of the edges for a node
	void reset();			// resets the graph

private:
	int numNodes;
	double density;
	vector<Node> nodes;
	int numEdges;
};

