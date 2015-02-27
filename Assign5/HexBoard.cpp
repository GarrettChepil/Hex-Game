#include "HexBoard.h"

// default constructor
HexBoard::HexBoard(){ turn = Playerturn::X; }

//constructor passed in the size
HexBoard::HexBoard(const int size)
{
	turn = Playerturn::X;
	generateBoard(size);
}


// generates the board, attaches the nodes to its neighbors
void HexBoard::generateBoard(const int size)
{
	//clears the board first and sets the size
	reset();
	this->size = size;

	// resize the board to the value passed. the extra 4 are the virtual nodes used to test if someone has won
	nodes.resize(size*size + 4);

	for (int i = 0; i < size*size + 4; ++i)
	{
		nodes[i].nodeNum = i;
	}

	// double for loop to add the inner edges
	for (int i = 1; i < (size - 1); ++i)
	{
		for (int j = 1; j < (size - 1); ++j)
		{
			nodes[j + (size*i)].edges.push_back(Edge((j + (size*i) - size), j + (size*i), 1));
			nodes[j + (size*i)].edges.push_back(Edge((j + (size*i) - size + 1), j + (size*i), 1));
			nodes[j + (size*i)].edges.push_back(Edge((j + (size*i) - 1), j + (size*i), 1));
			nodes[j + (size*i)].edges.push_back(Edge((j + (size*i) + 1), j + (size*i), 1));
			nodes[j + (size*i)].edges.push_back(Edge((j + (size*i) + size - 1), j + (size*i), 1));
			nodes[j + (size*i)].edges.push_back(Edge((j + (size*i) + size), j + (size*i), 1));
		}
	}

	// for loop to add the edges to the sides
	for (int i = 1; i < (size - 1); ++i)
	{
		nodes[i].edges.push_back(Edge(i - 1, i, 1));
		nodes[i].edges.push_back(Edge(i + 1, i, 1));
		nodes[i].edges.push_back(Edge(i + size - 1, i, 1));
		nodes[i].edges.push_back(Edge(i + size, i, 1));

		nodes[i * size].edges.push_back(Edge(i * size - size, i * size, 1));
		nodes[i * size].edges.push_back(Edge(i * size - size + 1, i * size, 1));
		nodes[i * size].edges.push_back(Edge(i * size + 1, i * size, 1));
		nodes[i * size].edges.push_back(Edge(i * size + size, i * size, 1));

		nodes[i * size + (size - 1)].edges.push_back(Edge(i * size + (size - 1) - size, i * size + (size - 1), 1));
		nodes[i * size + (size - 1)].edges.push_back(Edge(i * size + (size - 1) - 1, i * size + (size - 1), 1));
		nodes[i * size + (size - 1)].edges.push_back(Edge(i * size + (size - 1) + size - 1, i * size + (size - 1), 1));
		nodes[i * size + (size - 1)].edges.push_back(Edge(i * size + (size - 1) + size, i * size + (size - 1), 1));

		nodes[size * (size - 1) + i].edges.push_back(Edge(size * (size - 1) + i - size, size * (size - 1) + i, 1));
		nodes[size * (size - 1) + i].edges.push_back(Edge(size * (size - 1) + i - size + 1, size * (size - 1) + i, 1));
		nodes[size * (size - 1) + i].edges.push_back(Edge(size * (size - 1) + i - 1, size * (size - 1) + i, 1));
		nodes[size * (size - 1) + i].edges.push_back(Edge(size * (size - 1) + i + 1, size * (size - 1) + i, 1));
	}

	// add the edges for the corner nodes
	nodes[0].edges.push_back(Edge(1, 0, 1));
	nodes[0].edges.push_back(Edge(size, 0, 1));

	nodes[size - 1].edges.push_back(Edge(size - 1 - 1, size - 1, 1));
	nodes[size - 1].edges.push_back(Edge(size - 1 + size - 1, size - 1, 1));
	nodes[size - 1].edges.push_back(Edge(size - 1 + size, size - 1, 1));

	nodes[size * size - size].edges.push_back(Edge(size * size - size - size, size * size - size, 1));
	nodes[size * size - size].edges.push_back(Edge(size * size - size - size + 1, size * size - size, 1));
	nodes[size * size - size].edges.push_back(Edge(size * size - size + 1, size * size - size, 1));

	nodes[size * size - 1].edges.push_back(Edge(size * size - 1 - size, size * size - 1, 1));
	nodes[size * size - 1].edges.push_back(Edge(size * size - 1 - 1, size * size - 1, 1));


	// set the vitual nodes to the right player
	nodes[size * size].value = 'X';
	nodes[size * size + 1].value = 'X';
	nodes[size * size + 2].value = 'O';
	nodes[size * size + 3].value = 'O';

	// connect the virtual nodes to the edges
	for (int i = 0; i < size; ++i)
	{
		nodes[size * size].edges.push_back(Edge(size * i, size*size, 1));
		nodes[size * size + 1].edges.push_back(Edge(size * i + size - 1, size * size + 1, 1));
		nodes[size * size + 2].edges.push_back(Edge(i, size * size + 2, 1));
		nodes[size * size + 3].edges.push_back(Edge(size * (size - 1) + i, size * size + 3, 1));

		nodes[size * i].edges.push_back(Edge(size * size, size * i, 1));
		nodes[size * i + size - 1].edges.push_back(Edge(size * size + 1, size * i + size - 1, 1));
		nodes[i].edges.push_back(Edge(size * size + 2, i, 1));
		nodes[size * (size - 1) + i].edges.push_back(Edge(size * size + 3, size * (size - 1) + i, 1));
	}
}

// resets the board
void HexBoard::reset()
{
	nodes.clear();
	int size = 0;
	turn = Playerturn::X;
}

// method to print the board out to the console and prints the value of the node
void HexBoard::printBoard() const
{
	// string to represent the spacing on the left hand side
	string spacing = "";

	// string to print the top and bottom line depending how big the board is
	string alphaline = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// value to where to print the x on the sides
	int XLetter = size / 2;

	// int to represent which node to print
	int node = 0;
	cout << endl << "          O" << endl;
	cout << "  ";

	// for loop to print the letters depending how big the board is
	for (int i = 0; i < size; ++i)
	{
		cout << alphaline[i] << " ";
	}
	cout << endl;

	// for loops to print the rows
	for (int i = 1; i <= size; ++i)
	{
		if (XLetter == i)
		{
			cout << "X";
		}
		else if (i == 10)
			spacing.append("");
		else
			spacing.append(" ");
		cout << spacing << i << " ";

		// for loop to go through all the nodes on that line
		for (int j = 1; j <= size; ++j)
		{
			cout << nodes[node].value << " ";
			node++;
		}
		if (XLetter == i)
		{
			cout << i << "   X" << endl;
			spacing.append(" ");
		}
		else
			cout << i << endl;
	}

	cout << spacing << "   ";

	// for loop to print the letters
	for (int i = 0; i < size; ++i)
	{
		cout << alphaline[i] << " ";
	}

	cout << endl;
	cout << spacing << "            O" << endl;
	cout << endl;
}

// method to make a move and change the value of the node to the player and return true if its a valid move
bool HexBoard::makeMove(const string input)
{
	// split the input string into two string
	string alpha = input.substr(0, 1);
	string num = input.substr(1, string::npos);

	// sets the values to -1 so that if the user entered it wrong would return false
	int x = -1;
	int y = -1;

	// change the strings into intergers
	if (isalpha(alpha[0]))
		x = (int)toupper(input[0]) - 64;
	if (isdigit(num[0]))
	{
		y = atoi(num.c_str());
	}

	// check if the inputed vales are with in the board, and that the spot isnt already taken
	if (x <= size && x > 0 && y <= size && y > 0 && nodes[(y - 1) * size + x - 1].value == '.')
	{
		// checks whos turn it is and changes the value of the node to X or O depending on whos turn
		if (turn == Playerturn::X)
		{
			nodes[(y - 1) * size + x - 1].value = 'X';
			turn = Playerturn::O;
			return true;

		}
		else
		{
			nodes[(y - 1) * size + x - 1].value = 'O';
			turn = Playerturn::X;
			return true;
		}

	}

	// returns false if the move is invalid
	else
	{
		return false;
	}
}

// created a simpiler makemove method for the computer since it cant make a invalid move
void HexBoard::makeMove(int x)
{
	// checks whos turn it is and makes the move and changes the turn
	if (turn == Playerturn::X)
	{
		nodes[x].value = 'X';
		turn = Playerturn::O;
	}
	else
	{
		nodes[x].value = 'O';
		turn = Playerturn::X;
	}

}

// returns how many nodes are on the board
int HexBoard::getSize()
{
	return size * size;
}

// returns a vector of the node number for what moves are left on the board
vector<int> HexBoard::movesLeft()
{
	vector<int> legalMoves;

	// for loop that scan for availaible spaces and adds them to the vector if there empty
	for (int i = 0; i < size * size; ++i)
	{
		if (nodes[i].value == '.')
		{
			legalMoves.push_back(i);
		}
	}
	return legalMoves;
}

// method to return all the neighbors a node has
vector<Edge> HexBoard::neighbors(const int x) const
{
	return nodes[x].edges;
}

// mothod that checks if their is a winner, and returns 0 is none, 1 if player x has won, 2 is player o
int HexBoard::Winner()
{
	if (generatePath(size * size, 'X', size * size + 1))
		return 1;
	else if (generatePath(size * size + 2, 'O', size * size + 3))
		return 2;
	else
		return 0;
}

// generates a tree starting from the source node, and returns true if it can connect to the target
bool HexBoard::generatePath(const int source, const char player, const int target)
{
	// varibales used for the path
	vector<bool> finished;
	vector<Edge> edges;
	vector<Edge> openset;
	list<int> tree;
	Edge prievious;


	// resize the finished container and set all values to false
	finished.resize(size * size + 4, false);

	// add the starting node to the tree and get its neighbors
	finished[source] = true;
	tree.push_back(source);
	edges = neighbors(source);

	// checks if any of the neighbors are controlled by the player and adds it to the openset if it is
	for (auto i : edges)
	{
		if (nodes[i.target].value == player)
		{
			openset.push_back(i);
		}
	}

	// does this until all edges that are connected that belong to the player are checked
	while (!openset.empty())
	{
		// add the top node in the openset to the tree and check its neighbors 
		prievious = openset[0];
		openset.erase(openset.begin());

		// checks if that node is already in the tree and adds it to the list if not
		if (!finished[prievious.target])
		{
			finished[prievious.target] = true;
			tree.push_back(prievious.target);

			// get the new nodes neighbors
			edges.clear();
			edges = neighbors(prievious.target);

			//check if they are controlled by the player
			for (auto& i : edges)
			{
				if (!finished[i.target] && nodes[i.target].value == player)
				{
					openset.push_back(i);
				}
			}
		}
	}

	//checks if the target node is in the list of coonected nodes, and return true if it is
	for (auto i : tree)
	{
		if (i == target)
		{
			return true;
		}
	}
	return false;

}