/*
 * GameEngine.cpp
 *
 *  Created on: Oct 22, 2021
 *      Author: Jani
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
	//std::cout<<"current size"<<this->current.size()<<std::endl;
	this->current.erase(this->current.begin(), this->current.end());
	//std::cout<<"current size"<<this->current.size()<<std::endl;
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
						//std::cout<<"first line first column: "<<sum<<std::endl;
					}
					//last column
					else if (j == this->future[i].size()-1)
					{
						sum = this->calculateSurroundCells(i,i+1,j-1,j,i,j);
					//std::cout<<"first line last column: "<<sum<<std::endl;
						// 5 dead cell calculate other
					}
					else
					{

						sum = this->calculateSurroundCells(i,i+1,j-1,j+1,i,j);
						//std::cout<<"first line middle of calculation:"<<sum<<std::endl;
					}
				}
				//last line
				else if ( i == this->future.size()-1)
				{

					//first column
					if (j == 0)
					{
						sum = this->calculateSurroundCells(i-1,i,j,j+1,i,j);
						//std::cout<<"last line first column:"<<sum<<std::endl;
						//5 dead cell calculate other
					}
					//last column
					else if (j == this->future[i].size()-1)
					{
						sum = this->calculateSurroundCells(i-1,i,j-1,j,i,j);
						//5 dead cell calculate other
						//std::cout<<"last line last column:"<<sum<<std::endl;
					}
					else
					{
						sum = this->calculateSurroundCells(i-1,i,j-1,j+1,i,j);
						//std::cout<<"last line middle column:"<<sum<<std::endl;
					}
				}
				//middle first column
				else if (j == 0)
				{
					sum = this->calculateSurroundCells(i-1,i+1,j,j+1,i,j);
					//std::cout<<"Middle first column: "<<sum<<std::endl;
				}
				//middle last column
				else if (j == this->current[i].size()-1)
				{
					sum = this->calculateSurroundCells(i-1,i+1,j-1,j,i,j);
					//std::cout<<"Middle last column: "<<sum<<std::endl;
				}
				//middle
				else
				{
				sum = this->calculateSurroundCells(i-1,i+1,j-1,j+1,i,j);
				//std::cout<<"Middle middle column: "<<sum<<std::endl;
					//calculate 9 cells
				}
				//modify current cell state
				int currentState = this->future[i][j];
				int state = this->calculateState(sum,currentState);
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
	//std::cout<<"current position"<<current_cell_position_i<<","<<current_cell_position_j<<std::endl;
	int sum = 0;
	for (int i = i_begin; i < i_end+1; i++)
	{
		for (int j = j_begin; j < j_end+1; j++)
		{

				sum += this->future[i][j];
				//std::cout<<"pos: "<<i<<","<<j<<"val: "<<future[i][j];
		}
		//std::cout<<std::endl;
	}

	sum -= this->future[current_cell_position_i][current_cell_position_j];
	//std::cout<<"sum of neighbours: "<<sum<<std::endl;
	return sum;
}

int GameEngine::calculateState(int sum, int currentState)
{
	if(sum > 3) {
		//std::cout<<"cell is now dead"<<std::endl;
		return 0;
	}
	else if (sum == 2) {
		if (currentState == 1)
		{
		//std::cout<<"still alive"<<std::endl;
		return 1;
		}
		else {
			//std::cout<<"staying dead"<<std::endl;
			return 0;
		}
	}
	else if (sum == 3) {
		//std::cout<<"dead change to alive"<<std::endl;
		return 1;
	}

	else return 0;
}

void GameEngine::drawScreen()
{
	std::vector<int> screenData;
	for (unsigned int i = 0; i < this->future.size(); i++)
	{
		for (unsigned int j = 0; j < this->future[i].size(); j++)
		{
			screenData.push_back(this->future[i][j]);
		}
	}
	this->screen->drawLife(screenData);
}

void GameEngine::beginGame()
{
this->copyVector();
this->drawScreen();
while (this->screen->gameEnd == false)
{
	this->calculateVector();
	this->copyVector();
	this->drawScreen();
//	this->iteration--;
}
}

void GameEngine::debug()
{
	int i = this->current.size();
	int j = this->current[0].size();
	this->current.erase(this->current.begin(),this->current.end());
	std::vector<int> first, second, third, rest;
	first.push_back(0);
	first.push_back(1);
	first.push_back(0);
	second.push_back(0);
	second.push_back(0);
	second.push_back(1);
	third.push_back(1);
	third.push_back(1);
	third.push_back(1);
	rest.push_back(0);
	rest.push_back(0);
	rest.push_back(0);
	for (int k = 3; k < j; k++)
	{
		first.push_back(0);
		second.push_back(0);
		third.push_back(0);
		rest.push_back(0);
	}
	this->current.push_back(first);
	this->current.push_back(second);
	this->current.push_back(third);

	for (int k = 3; k < i; k++)
	{
		this->current.push_back(rest);
	}

}
