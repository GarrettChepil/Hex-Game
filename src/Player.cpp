#include "Player.h"

// constuctor if you enter what stone they are as a argument
Player::Player(char stone)
{
	this->stone = stone;
}

// method to set the player to a stone
void Player::SetPlayer(char stone)
{
	this->stone = stone;
}

// return what stone the player is
char Player::getStone()
{
	return stone;
}

// virtual method for the humans move
void HumanPlayer::Move(HexBoard& board)
{
	// varible for the human input
	string move;

	// message to the player to enter their move and store it in the string
	cout << "Player " << stone << " turn" << endl;
	cout << "Enter your move (example a3): ";
	cin >> move;

	// while loop to continue looping if the player enters an invaild move
	while (!board.makeMove(move))
	{
		cout << "invalid input" << endl;
		cout << "Enter your move (example a3): ";
		cin >> move;
	}
}

// virtual move method for the computer player
void ComputerPlayer::Move(HexBoard& board)
{
	// declare the varibles
	HexBoard virtualBoard;
	vector<int> legalMoves = board.movesLeft();
	const int boardSize = board.getSize();
	vector<int> wins(legalMoves.size(), 0);

	// set up the romdom device for the shuffle
	// was gonna try using the new random, but after test found the old
	// random shuffle better
	//random_device rd;
	//mt19937 g(rd());

	// message to tell the user to wait
	cout << endl << "Computers turn please wait" << endl;

	// create a for loop to go through all legal moves left
	for (int i = 0; i < legalMoves.size(); ++i)
	{
		// counter for the while loop
		int count = 0;

		// while loop to apply the monte carlo move evalulation
		// enter a bigger number to make the computers move better
		while (count < 10000)
		{
			// copy the board and moves left for the simulation
			virtualBoard = board;
			vector<int> simMoves = legalMoves;

			// make the move for the piece being evaluated
			virtualBoard.makeMove(simMoves[i]);
			simMoves.erase(simMoves.begin() + i);

			// shuffles the legal moves to gemnertate a random effect
			random_shuffle(simMoves.begin(), simMoves.end());

			// for loop to fill the board up with random moves
			for (int j = 0; j < simMoves.size(); ++j)
			{
				virtualBoard.makeMove(simMoves[j]);
			}

			// after the board is full checks to see if its won and adds 1 to the wins var
			if (stone == 'X')
			{
				if (virtualBoard.generatePath(boardSize, 'X', boardSize + 1))
				{
					wins[i]++;
				}
			}
			else
			{
				if (virtualBoard.generatePath(boardSize + 2, 'O', boardSize + 3))
				{
					wins[i]++;
				}
			}
			count++;
		}
	}


	// finds the space with the largest wins 
	int biggest = *max_element(wins.begin(), wins.end());

	// for loop to go through the wins vector and when it finds the biggest
	// value, it makes that move and breaks the loop
	for (int i = 0; i < wins.size(); ++i)
	{
		if (wins[i] == biggest)
		{
			board.makeMove(legalMoves[i]);
			break;
		}
	}

}