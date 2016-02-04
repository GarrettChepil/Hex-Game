#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <list>

#include "Node.h"
#include "Playerturn.h"

using namespace std;

// a class to represent a hex board that uses a graph representation
// also will calculate the path to check if a player has won
class HexBoard
{
public:
	// constructors
	HexBoard();
	HexBoard(const int size);
	~HexBoard(){};

	//enum object to keep track of whos turn it is
	Playerturn turn;

	//methods
	void generateBoard(const int size);
	void reset();
	bool makeMove(const string input);
	void makeMove(int x);
	vector<Edge> neighbors(const int x) const;
	int Winner();
	int getSize(); // returns how many nodes in the board
	vector<int> movesLeft(); // returns how many legal moves left
	bool generatePath(const int source, const char player, const int target);
	void printBoard() const;

protected:
	// vector that represents all the places on the board
	vector<Node> nodes;
	int size;
};