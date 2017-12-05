//Program simulates a two-dimensional world in which each "cell" may be 
//occupied by an organism. The world passes through generations, bringing death 
//and new life to the world instantaneously in accordance with Conway's
//Game of Life rules.
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;

const int ROW = 22;
const int COLUMN = 80;

void createWorld(char world [][COLUMN]);
//Creates a two dimensional array.

void display(char world [][COLUMN]);
//Precondition: array world has been filled.
//Postcondition: Displays the updated world.

bool isOccupied(char cell);
//Precondition: cell == '*' || cell == ' '
//Postcondition: Returns true if cell == '*' and false if not.

bool isEmpty(char cell);
//Precondition: cell == ' ' || cell == '*'
//Postcondition: Returns true if cell == ' ' and false if not.

bool worldIsFull(char world[][COLUMN]);
//Precondition: world has been filled.
//Postcondition: Returns true if all elements of world have been intialized
//to '*' and false if not.

bool worldIsEmpty(char world[][COLUMN]);
//Precondition: All elements of world have been intialized.
//Postcondition: Returns true if all elements of world have been 
//intialized to ' ' and false if not.

int neighborCount(char world[][COLUMN], int row, int column);
//Precondition: All elements of world have been initialized. 
//Postcondition: Returns the number of occupied neighbor cells that
//world[row][column] has.

void nextGeneration(char world[][COLUMN]);
//Precondition: array world is filled.
//Postcondition: Modifies the values of elements in array world in accordance
//the Game of Life rules.

int main()
{
	char world[ROW][COLUMN];
	
	createWorld(world);
    char next;

	do
	{
		nextGeneration(world);
		cout<<"Press Return to continue or q to quit: ";
        cin.get(next);
        cout<<endl;
        if (next == '\n')
		    display(world);
	}while(next == '\n');

	return 0;
}

void createWorld(char world[][COLUMN])
{
    srand(time(NULL));
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
            world[i][j] = ((rand() % 2 + 3) *10) + 2; //Returns ' ' or '*'
            cout<<world[i][j];
		}
        cout<<endl;
	}
}

void nextGeneration(char world[][COLUMN])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			if (isOccupied(world[i][j]) && (neighborCount(world,i, j) == 0 || neighborCount(world, i, j) == 1))
				world[i][j] = ' ';
			else if (isOccupied(world[i][j]) && (neighborCount(world, i, j) > 3))
				world[i][j] = ' ';
			else if (isEmpty(world[i][j]) && (neighborCount(world, i, j) == 3))
				world[i][j] = '*';
		}
	}
}

int neighborCount(char world[][COLUMN], int row, int column)
{
	int count = 0;

	if (row != 0 && world[row-1][column] == '*')
		++count;
	if ((row != 0 && column != (COLUMN - 1)) && world[row-1][column+1] == '*')
		++count;
	if (column != (COLUMN - 1) && world[row][column+1] == '*')
		++count;
	if (row != (ROW - 1) && world[row+1][column] == '*')
		++count;
	if ((row != (ROW - 1) && column != (COLUMN - 1)) && world[row+1][column+1] == '*')
		++count;
	if ((row != 0 && column != 0) && world[row-1][column-1] == '*')
		++count;
	if (column != 0 && world[row][column-1] == '*')
		++count;
	if ((row != (ROW - 1) && column != 0) && world[row+1][column-1] == '*')
		++count;

	return count;
}

bool isEmpty(char cell)
{
	return (cell == ' ');
}

bool isOccupied(char cell)
{
	return (cell == '*');
}

void display(char world [][COLUMN])
{
    cout<<"\n\n\n\n";
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
			cout<<world[i][j];
        cout<<endl;
	}
}

bool worldIsEmpty(char world[][COLUMN])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
			if (world[i][j] == '*')
				return false;
	}

	return true;
}

bool worldIsFull(char world[][COLUMN])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
			if (world[i][j] == ' ')
				return false;
	}

	return true;
}
