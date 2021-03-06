// box generator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "cstdio"
#include <ctime>    
#include <cstdlib>
#include <algorithm>
using namespace std;

const int boxSize = 37;
int workspace[boxSize][boxSize];
int numberOfRooms = 100;
int directions[4];


void displayWorkspace()
{
	//display workspace
	for (int i = 0; i < boxSize; i++)
	{
		for (int j = 0; j < boxSize; j++)
		{
			
			switch (workspace[i][j])
			{
			case 0:
				cout << 0 << " ";
				break;
			case 1:
				cout << "  ";
				break;
			case 2:
				cout << "C" << " ";
				break;
			case 3:
				cout << "*" << " ";
				break;
			case 4:
				cout << "O ";
				break;
			case 5:
				cout << "~ ";
				break;
			case 6:
				cout << "H ";
				break;
			}//switch
			
			
		}//for
		cout << endl;
	}//for

}//displayWorkspace

void clearWorkspace()
{
	;//fills workspace with 0
	for (int i = 0; i < boxSize; i++)
	{
		for (int j = 0; j < boxSize; j++)
		{
			workspace[i][j] = 0;
		}//for
	}//for
	 //clears edges
	for (int i = 0; i < boxSize; i++)
		workspace[i][0] = 4;
	for (int i = 0; i < boxSize; i++)
		workspace[i][boxSize - 1] = 4;
	for (int j = 0; j < boxSize; j++)
		workspace[0][j] = 4;
	for (int j = 0; j < boxSize; j++)
		workspace[boxSize - 1][j] = 4;

}//clearWorkspace

void generateStartZone()
{
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			workspace[i][j] = 1;
		}//for
	}//for
}//generateStartZone

void generateRooms()
{
	srand(time(0));
	int roomStartX;
	int roomStartY;
	int roomEndX;
	int roomEndY;
	int collision = 0;
	int roomWidth;
	int roomHeight;

	for (int i = 0; i < numberOfRooms; i++)
	{
		roomWidth = ((rand() % 4) + 6);
		roomHeight = ((rand() % 4) + 6);

		roomStartX = ((rand() % (boxSize - roomWidth)) + 1);
		roomStartY = ((rand() % (boxSize - roomHeight)) + 1);
		roomEndX = roomStartX + roomWidth - 2;
		roomEndY = roomStartY + roomHeight - 2;
		collision = 0;
		//if ((roomStartX < (boxSize - 5)) && (roomStartY < (boxSize - 5)));
		{

			for (int i = roomStartY; i < roomEndY; i++)
			{
				for (int j = roomStartX; j < roomEndX; j++)
				{
					if (workspace[i][j] != 1 &&
						workspace[i][j + 1] != 1 &&
						workspace[i][j - 1] != 1 &&
						workspace[i + 1][j + 1] != 1 &&
						workspace[i + 1][j - 1] != 1 &&
						workspace[i + 1][j] != 1 &&
						workspace[i - 1][j] != 1 &&
						workspace[i - 1][j + 1] != 1 &&
						workspace[i - 1][j - 1] != 1
						)//checking to make sure no collision
					{
						workspace[i][j] = 2;
					}//if
					else
					{
						collision = 1;
						break;
					}
				}//for
				if (collision == 1)
					break;
			}//for
			if (collision == 1)
			{
				for (int i = 0; i < boxSize; i++)
				{
					for (int j = 0; j < boxSize; j++)// cleaning up if there was a collision
					{
						if (workspace[i][j] == 2)
							workspace[i][j] = 0;
					}//for
				}//for
			}//if
			else
			{
				for (int i = 0; i < boxSize; i++)//offically making a room
				{
					for (int j = 0; j < boxSize; j++)
					{
						if (workspace[i][j] == 2)
							workspace[i][j] = 1;
					}//for
				}//for				
			}//else
		}//if
	}//for
}

void lazyDoors()
{
	for (int i = 0; i < boxSize; i++)//puts doors where there are adjacent rooms
	{
		for (int j = 0; j < boxSize; j++)
		{
			if ((workspace[i][j + 1] == 1 &&
				workspace[i][j - 1] == 1) ||
				(workspace[i + 1][j] == 1 &&
					workspace[i - 1][j] == 1))
				workspace[i][j] = 1;
		}//for
	}//for	
}//lazyDoors

void swap(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}

//generates a random order of directions for the maze to try
void generateRandomDirections()
{
	for (int i = 0; i < 4; i++)
	{
		directions[i] = i;
		random_shuffle(&directions[0], &directions[10]);
	}//for
}//generateRandomDirections



void generateMaze(int x, int y)
{
	generateRandomDirections();

	for (int i = 0; i < 4; i++)
	{
		switch (directions[i])
		{
		case 0://left
			if (x - 3 <= 0)
				continue;
			if (workspace[x - 2][y] != 1 && //checks 3 spaces ahead so it does not run up to a room
				workspace[x - 2][y + 1] != 1 &&
				workspace[x - 2][y - 1] != 1
				)
			{
				workspace[x - 2][y] = 1;
				workspace[x - 1][y] = 1;
				generateMaze(x - 2, y);
			}//if
			break;
		case 1://down
			if (y + 3 >= boxSize - 1)
				continue;
			if (workspace[x][y + 2] != 1 &&
				workspace[x + 1][y + 2] != 1 &&
				workspace[x - 1][y + 2] != 1
				)
			{
				workspace[x][y + 2] = 1;
				workspace[x][y + 1] = 1;
				generateMaze(x, y + 2);
			}//if
			break;
		case 2://right
			if (x + 3 >= boxSize - 1)
				continue;
			if (workspace[x + 2][y] != 1 &&
				workspace[x + 2][y + 1] != 1 &&
				workspace[x + 2][y - 1] != 1
				)
			{
				workspace[x + 2][y] = 1;
				workspace[x + 1][y] = 1;
				generateMaze(x + 2, y);
			}//if
			break;
		case 3://up
			if (y - 3 <= 0)
				continue;
			if (workspace[x][y - 2] != 1 &&
				workspace[x + 1][y - 2] != 1 &&
				workspace[x - 1][y - 2] != 1
				)
			{
				workspace[x][y - 2] = 1;
				workspace[x][y - 1] = 1;
				generateMaze(x, y - 2);
			}//if
			break;
		}//switch
	}//for
}//generateMaze()

void findConnectors()
{
	for (int i = 0; i < boxSize; i++)
	{
		for (int j = 0; j < boxSize; j++)
		{
			if (workspace[i][j] == 0 && ((workspace[i + 1][j] == 1 && workspace[i - 1][j] == 1) || (workspace[i][j + 1] == 1 && workspace[i][j - 1] == 1)))
			{					
				workspace[i][j] = 2;
			}
		}
	}
}//findConnectors

void flood(int x, int y)
{
	if (workspace[x][y] == 1)
	{
		workspace[x][y] = 5;

		if (x + 1 < boxSize)
			flood(x + 1, y);
		if (x - 1 > 0)
			flood(x - 1, y);
		if (y + 1 < boxSize)
			flood(x, y+1);
		if (y - 1 > 0)
			flood(x, y-1);
	}//if

}//flood

void fillConnector(int x, int y)
{
	if (workspace[x][y] == 2)
	{
		workspace[x][y] = 0;

		if (x + 1 < boxSize)
			fillConnector(x + 1, y);
		if (x - 1 > 0)
			fillConnector(x - 1, y);
		if (y + 1 < boxSize)
			fillConnector(x, y + 1);
		if (y - 1 > 0)
			fillConnector(x, y - 1);
	}//if
}//fillConnecror

void open(int x, int y)
{
	workspace[x][y] = 1;

	if (x + 1 < boxSize)
		fillConnector(x + 1, y);
	if (x - 1 > 0)
		fillConnector(x - 1, y);
	if (y + 1 < boxSize)
		fillConnector(x, y + 1);
	if (y - 1 > 0)
		fillConnector(x, y - 1);
}//connect

void makeDoors()
{
	for (int i = 0; i < boxSize; i++)
	{
		for (int j = 0; j < boxSize; j++)
		{
			if (workspace[i][j] == 2)
				open(i, j);
			//if ((workspace[i + 1][j] == 5 && workspace[i - 1][j] == 5) || (workspace[i][j + 1] == 5 && workspace[i][j - 1] == 5))
				//fillConnector(i, j);
			if (workspace[i][j] == 1)
				flood(i, j);
		}//for
	}//for

	for (int k = 0; k < boxSize; k++)
	{
		for (int l = 0; l < boxSize; l++)
		{
			if (workspace[k][l] == 5)
				workspace[k][l] = 1;
		}//for
	}//for

	

}//makeDoors

int main()
{
	for (int i = 0; i < 1; i++)
	{


		clearWorkspace();
		generateStartZone();
		generateRooms();

		for (int i = 3; i < boxSize - 3; i++)
		{
			for (int j = 3; j < boxSize - 3; j++)
			{
				if (workspace[i][j] != 1 &&
					workspace[i][j + 1] != 1 &&
					workspace[i][j - 1] != 1 &&
					workspace[i + 1][j + 1] != 1 &&
					workspace[i + 1][j - 1] != 1 &&
					workspace[i + 1][j] != 1 &&
					workspace[i - 1][j] != 1 &&
					workspace[i - 1][j + 1] != 1 &&
					workspace[i - 1][j - 1] != 1)
					generateMaze(i, j);

				
			}
		}

	}

	

	displayWorkspace();

	findConnectors();
	cout << endl;
	displayWorkspace();

	makeDoors();
	cout << endl;
	displayWorkspace();

	system("pause");

	return 0;
}//main








