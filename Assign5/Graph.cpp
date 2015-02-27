#include "Graph.h"

// default constructor for the graph object
Graph::Graph(void){}

// Constructor to build a graph object with numnodes in size
Graph::Graph(int numNodes)
{
	this->numNodes = numNodes;
	nodes.resize(numNodes);
}

// Constructor to build a graph from a file 
Graph::Graph(ifstream& ifp)
{
	GeneratefromFile(ifp);
}

// constructor to build a random grapm
Graph::Graph(double density, double minRange, const double maxRange, int numNodes)
{
	GenerateRandom(density, minRange, maxRange, numNodes);
}

Graph::~Graph(void){}

// method to generate a graph from a file
void Graph::GeneratefromFile(ifstream& ifp)
{
	reset();
	ifp >> numNodes;	// first line in the file is the size of the graph
	nodes.resize(numNodes);		// sets the size of the graph
	int target, source;
	double cost;

	while (!ifp.eof())
	{
		ifp >> source;		// gets the source node from the file
		ifp >> target;		// gets the target node from the file
		ifp >> cost;		// gets the cost from the file
		nodes[source].edges.push_back(Edge(target, source, cost)); // adds the node to the graph
		numEdges++;
	}
	numEdges / 2;	// not the best way to handle this but takes in accout that the graph is undirected  
}

// Generates a Random graph from the argumnets the user gives
void Graph::GenerateRandom(double density, double minRange, const double maxRange, int numNodes)
{
	reset();
	this->numNodes = numNodes;
	nodes.resize(numNodes);
	this ->density = density;
	numEdges = 0;

	// use 2 for loops to fill the graph with edges
	for(int i = 0; i < numNodes; ++i)
	{
		for(int j= i + 1; j < numNodes; ++j)
		{
			if ((rand() / (double)RAND_MAX) < density)
			{
				double cost = minRange + ((maxRange - minRange) * ((double) rand()) / RAND_MAX);
				//double cost = ((rand() / (double) RAND_MAX) * 9.0) + 1.0;
				addEdge(i,j, cost);
			}
		}
	}
}

// adds and edge to the graph with a size of the edge
void Graph::addEdge(int target, int source, double cost)
{
	nodes[source].edges.push_back(Edge(target,source,cost));
	nodes[target].edges.push_back(Edge(source,target,cost));
	numEdges++;
}

// returns how many vertices are in the graph
int Graph::V()
{
	return numNodes;
}

// returns how many edges are in the graph
int Graph::E()
{
	return numEdges;
}

// returns a vector of edges that the node is connected too
vector<Edge> Graph::neighbors(int x)
{
	return nodes[x].edges;
}

// reset the graph
void Graph::reset()
{
	nodes.clear();
	numEdges = 0;
	nodes.resize(numNodes);
}
