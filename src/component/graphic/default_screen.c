//#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include"default_screen.h"


typedef struct WEM_component_struct WEM_component;

typedef struct WEM_screen_struct
{
	
	
	WEM_component *component;
	
	SDL_Texture *texture;
	
	int size_x;
	
	int size_y;
	
	void (*frame_f_ptr)(WEM_machine*,WEM_screen*);
	
	
	
}WEM_screen;
