#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "HexBoard.h"
#include "Node.h"

using namespace std;

// class for the players playing the game, with 2 inherited classes for a 
// human player and a computer player

// default player class
class Player
{
public:
	// constructors
	Player(){};
	Player(char stone);
	~Player(){};

	// methods
	void SetPlayer(char stone);
	char getStone();
	virtual void Move(HexBoard& board) = 0;

protected:
	char stone;
};

// inherited class for a human player
class HumanPlayer : public Player
{
public:
	// virtual method of the move
	virtual void Move(HexBoard& board);
};

// inherited class for a computer player
class ComputerPlayer : public Player
{
public:
	virtual void Move(HexBoard& board);
};