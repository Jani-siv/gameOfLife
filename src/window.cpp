/*
 * window.cpp
 *
 *  Created on: Oct 21, 2021
 *      Author: Gyy
 */

#include "window.h"

window::window(unsigned int u_width, unsigned int u_heigth, int cells_r, int cells_c) {
	// TODO Auto-generated constructor stu
	//set screen dividing fit correctly
	this->width = u_width;
	this->width -= this->width%cells_c;
	std::cout<<"cells_c & cells_r: "<<cells_c<<":"<<cells_r<<std::endl;
	this->heigth = u_heigth;
	this->heigth -= this->heigth%cells_r;
	std::cout<<"screen dimenssions:"<<this->width<<"x"<<this->heigth<<std::endl;
	this->cell_h = this->heigth / cells_r;
	std::cout<<"cell height"<<this->cell_h<<std::endl;
	this->cell_w = this->width / cells_c;
	std::cout<<"cell width"<<this->cell_w<<std::endl;
	this->cell_r = cells_r;
	this->cell_c = cells_c;
	if (this->makeWindow() < 0)
	{
		std::cerr<<"error creating window"<<std::endl;
	}
}

window::~window() {
	// TODO Auto-generated destructor stub
    SDL_DestroyWindow( this->gameWindow );
    SDL_Quit();
}

int window::makeWindow()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
      {
          //Create window
          this->gameWindow = SDL_CreateWindow( "Game Of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->heigth, SDL_WINDOW_SHOWN );
          if( gameWindow == NULL )
          {
              printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
              return -1;
          }
          else
          {
        		this->gRenderer = SDL_CreateRenderer( this->gameWindow, -1, SDL_RENDERER_ACCELERATED );
        					if( gRenderer == NULL )
        					{
        						printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        					}
        					else
        					{
        						//Initialize renderer color

        						SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

        						SDL_RenderClear( this->gRenderer );
        						this->drawWindow();
        				//	SDL_Delay(2000);
        					}
          }
      }

return 0;
}

void window::drawWindow()
{
	SDL_Rect fillRect = { this->width / 2, this->heigth / 4, this->width / 2, this->heigth / 2 };
					SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderFillRect( this->gRenderer, &fillRect );
					SDL_RenderPresent( this->gRenderer );
}

void window::drawLife(std::vector<int> cell)
{
	auto it = cell.begin();
	int current_x=0;
	int current_y=0;
for (int i = 0; i < this->cell_r; i++)
{
	current_x = 0;
	for (int j = 1; j <= this->cell_c; j++)
	{
		SDL_Rect cellPOS = {
					current_x,
					current_y,
					this->cell_w,
					this->cell_h
			};
		current_x = (j)*this->cell_w;
		current_y = i*this->cell_h;

		if (it.operator *() == 0)
		{
			SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
		}
		else
		{
			SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0x00, 0xFF, 0xFF );
		}
		it++;
		SDL_RenderFillRect( this->gRenderer, &cellPOS );


	}
	current_y += this->cell_h;
}
SDL_RenderPresent( this->gRenderer);
SDL_Delay(50);
}
