/*
 * GameEngine.cpp
 *
 *  Created on: Oct 22, 2021
 *      Author: Gyy
 */

#include "GameEngine.h"

GameEngine::GameEngine(int columns, int lines, int cells, int iteration, window *screen) {
	// TODO Auto-generated constructor stub
this->columns = columns;
this->lines = lines;
this->cells = cells;
this->iteration = iteration;
this->screen = screen;
this->initCurrent();
}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}
void GameEngine::initCurrent()
{
	srand(time(NULL));
	for(int i = 0; i < this->lines; i++)
	{
		std::vector<int> table;
		for(int j= 0; j < this->columns; j++)
		{

		int ran = rand() % 9000 +1;
		int p = ran % 2;
		table.push_back(p);
		}
		this->current.push_back(table);
	}
}

void GameEngine::copyVector()
{
this->future.assign(this->current.begin(),this->current.end());
}

void GameEngine::calculateVector()
{
//todo smaller than 9 cell
	//empty current
	this->current.erase(this->current.begin(), this->current.end());

		for (unsigned i = 0; i < this->future.size(); i++)
		{
			std::vector<int> table;

			for (unsigned j = 0; j < this->future[i].size(); j++)
			{
				int sum =0;
				//first line
				if (i == 0)
				{
					//first column
					if (j == 0)
					{
						sum = this->calculateSurroundCells(i,i+1,j,j+1,i,j);

						// 5 dead cell calculate other

					}
					//last column
					else if (j == future[i].size())
					{
						sum = this->calculateSurroundCells(i,i+1,j-1,j,i,j);
					;
						// 5 dead cell calculate other
					}
					else
					{

						sum = this->calculateSurroundCells(i,i+1,j-1,j+1,i,j);
					}
				}
				//last line
				else if ( i == future.size()-1)
				{

					//first column
					if (j == 0)
					{
						sum = this->calculateSurroundCells(i-1,i,j,j+1,i,j);
						//5 dead cell calculate other
					}
					//last column
					else if (j == future[i].size())
					{
						sum = this->calculateSurroundCells(i-1,i,j-1,j,i,j);
						//5 dead cell calculate other
					}
				}
				else
				{
				sum = this->calculateSurroundCells(i-1,i+1,j-1,j+1,i,j);
					//calculate 9 cells
				}
				//modify current cell state
				int state = this->calculateState(sum);
				table.push_back(state);
			}
			this->current.push_back(table);
		}
}


int GameEngine::getCellValue(int i, int j)
{
	return this->future[i][j];
}

int GameEngine::calculateSurroundCells(int i_begin, int i_end, int j_begin, int j_end, int current_cell_position_i, int current_cell_position_j)
{
	int sum = 0;
	for (int i = i_begin; i < i_end+1; i++)
	{
		for (int j = j_begin; j < j_end+1; j++)
		{
			if (i != current_cell_position_i && j != current_cell_position_j)
			{
				sum += this->future[i][j];
			}
		}
	}
	return sum;
}

int GameEngine::calculateState(int sum)
{
	if (sum == 2 || sum == 3) {return 1;}
	else { return 0; }
}

void GameEngine::drawScreen()
{
	std::vector<int> screenData;
	for (unsigned int i = 0; i < this->current.size(); i++)
	{
		for (unsigned int j = 0; j < this->current[i].size(); j++)
		{
			screenData.push_back(this->current[i][j]);
		}
	}
	this->screen->drawLife(screenData);
}

void GameEngine::beginGame()
{
this->copyVector();
this->drawScreen();
while (this->iteration > 0)
{
	this->calculateVector();
	this->copyVector();
	this->drawScreen();
	this->iteration--;
}
}
