/*
 * GameEngine.h
 *
 *  Created on: Oct 22, 2021
 *      Author: Gyy
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "window.h"
class GameEngine {
public:
	GameEngine(int columns, int lines, int cells, int iteration, window *screen);
	virtual ~GameEngine();
	void beginGame();
	void debug();
private:
	int columns {0};
	int lines {0};
	int cells {0};
	int iteration {0};
	std::vector<std::vector<int>> current;
	std::vector<std::vector<int>> future;
	void initCurrent();

	void copyVector();
	void calculateVector();
	int getCellValue(int i, int j);
	int calculateSurroundCells(int i_begin, int i_end, int j_begin, int j_end, int current_cell_position_i, int current_cell_position_j);
	int calculateState(int sum, int currentState);
	void drawScreen();

	window * screen;

};

#endif /* GAMEENGINE_H_ */
