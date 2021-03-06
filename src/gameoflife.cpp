//============================================================================

// Name : gameoflife.cpp

// Author : Jani

// Version : 1.0

// Copyright : Your copyright notice

// Description : Game of life c++ & SDL2

// Require : SDL2-devel package tested version 2.0.16-3.fc34

//TESTED

// Linux distro: Fedora

// Kernel ver. : 5.14.11-200.fc34.x86_64

// cflags for compiler in Linux run: pkg-config sdl2 --cflags

// libs for compiler in Linux run: pkg-config sdl2 --libs

//TEST algorithm in screen

// for test screen with glider use debug() before beginGame.

//Program usage

// user input keys:

// A key automate / one step

// S key one generation foward

// Q key Quit game

//============================================================================

//John Conway Game of life build top of SDL2 and with c++ language

#include <iostream>
#include "window.h"
#include <vector>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "GameEngine.h"
#define WIDTH 800
#define HEIGHT 800
#define MAX_USER_INPUT 9
#define MAX_CELLS WIDTH*HEIGHT/2

void menu()
{
	std::cout<<"****Program usage****"<<std::endl;
	std::cout<<"./gameoflife (numbers of cells)"<<std::endl;
	std::cout<<"./gameoflife 9"<<std::endl;
	std::cout<<"Maximum amount of cells is: "<<MAX_CELLS<<std::endl;
	std::cout<<"Minimum amount of cells is: 2"<<std::endl;
	std::cout<<"window size: "<<WIDTH<<"X"<<HEIGHT<<std::endl;
	std::cout<<"USER INPUTS IN GAME:"<<std::endl;
	std::cout<<"a automate / one step"<<std::endl;
	std::cout<<"s step"<<std::endl;
	std::cout<<"q quit qame"<<std::endl;

}

int main(int argc, char *argv[]) {
	menu();
	if (argc > 1)
	{
		int argvLen = strlen(argv[1]);
		if (argvLen > MAX_USER_INPUT)
		{
			std::cout<<"Too many numbers in user input"<<std::endl;
			return -1;
		}
		char testUserInput[argvLen];
		strncpy(testUserInput,argv[1],argvLen);
		for (int i=0; i < argvLen; i++)
		{
			if (!std::isdigit(testUserInput[i]))
			{
				std::cout<<"Error in user input exiting"<<std::endl;
				menu();
				return -1;
			}
		}
		unsigned int cells = atoi(testUserInput);

		if (cells == 0)
		{
			std::cout<<"set bigger amount of cells"<<std::endl;
			menu();
			return -1;
		}

		if (cells > MAX_CELLS)
		{
			std::cout<<"set smaller amount of cells"<<std::endl;
			menu();
			return -1;
		}
		int columns = (int)sqrt(cells);
		int lines = (int)ceil(cells / columns);
		std::cout<<cells % columns<<std::endl;
		if (cells % columns > 0)
		{
			std::cout<<"earlier possible cell amount is: "<< cells - cells %columns<<std::endl;
			return -1;
		}
/*WINDOW OBJECT AND GAME ENGINE OBJECTS*/
window game(WIDTH,HEIGHT,lines,columns);
window *screen = &game;
GameEngine engine(columns,lines,cells,1000,screen);
//engine.debug();
engine.beginGame();
	return 0;
	}
	else
	{
		menu();
		return -1;
	}
}
