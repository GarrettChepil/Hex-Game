// this is a continuation on my assignment 4 program, i added a player class and use inheritance 
// to create two other classes one for the human player and computer player
// the computer player uses a Monte Carlo evalulation  to find the best move, 
// MAKE SURE YOU USE A RELEASE BUILD WHEN YOU COMPILE IT, or it will several mins make the move
// where release takes a few secs
// i also used a random shuffle of a vector of the legal moves left and filled the board with that
// felt that would be faster then trying to randomly make a move, then having to check if that 
// move was already made

// assignment 4 comments below
// this program will generate a Hex board and let you play a game 
// the hexboard class will generate a 11x11 board and keep track of the moves
// its uses a graph representation and a spanning tree to check if a player has won


#include <iostream>
#include <string>
#include <time.h>


#include "Node.h"
#include "HexBoard.h"
#include "Playerturn.h"
#include "Player.h"


int main()
{
	// declare the variables
	HexBoard board(11);
	char answer;
	HumanPlayer human;
	ComputerPlayer computer;
	srand(time(0));

	// print a welcome message askd who goes first and prints the board
	cout << "Welsome to the Game of Hex" << endl;
	cout << "Do you want to go First? (player X): ";
	cin >> answer;
	if (toupper(answer) == 'Y')
	{
		human.SetPlayer('X');
		computer.SetPlayer('O');
	}
	else
	{
		human.SetPlayer('O');
		computer.SetPlayer('X');
	}

	board.printBoard();

	// loops till there is a winner
	while (board.Winner() == 0)
	{
		// checks whos turn it is
		if (board.turn == Playerturn::X)
		{
			if (human.getStone() == 'X')
			{
				human.Move(board);
			}
			else
			{
				computer.Move(board);
			}
		}
		else
		{
			if (human.getStone() == 'O')
			{
				human.Move(board);
			}
			else
			{
				computer.Move(board);
			}
		}
		board.printBoard();
	}

	// checks which player has won, and prints the winner
	if (board.Winner() == 1)
	{
		cout << "Player X Wins!!" << endl;
	}
	else
		cout << "Player O Wins!!" << endl;
	cout << endl;

	return 0;

}