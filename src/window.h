/*
 * window.h
 *
 *  Created on: Oct 21, 2021
 *      Author: Gyy
 */

#ifndef WINDOW_H_
#define WINDOW_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

class window {
public:
	window(unsigned int u_width, unsigned int u_heigth, int cells_r, int cells_c);
	void drawLife(std::vector<int> cell);
	void setDisplayMode(bool mode);
	bool gameEnd = false;
	virtual ~window();
private:
	//user interface
	 bool displayMode = false;
	 SDL_Event event;
	 int checkEvents();
	 //screen setup
	 int width {800};
	 int heigth {600};
	 int cell_h {0};
	 int cell_w {0};
	 int cell_r {0};
	 int cell_c {0};
	int makeWindow();
	void drawWindow();
	SDL_Window* gameWindow = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* gRenderer = NULL;

};

#endif /* WINDOW_H_ */
