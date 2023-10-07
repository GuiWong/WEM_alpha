#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include"component/component.h"
#include"component/clockable.h"
#include"component/bus_component.h"

#include"machine/machine.h"
#include"machine/machine.c"
#include"machine/adress_logic.c"





#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))


SDL_Window *window;
SDL_Renderer *renderer;

int init_sdl()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		SDL_Log("Error while initialising SDL subsystem %s\n" ,SDL_GetError());
		return 0;
	}
	
	IMG_Init(IMG_INIT_PNG);
	
	return 1;
}


void create_window()
{
	window = SDL_CreateWindow
	(
		"test",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,	//TODO:size from settings struct
		320,
		0
	);
	
	renderer =SDL_CreateRenderer(window,-1,0);
}

void cleanup()
{
    	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void main()
{


//-------------------SDL init--------------------------------------------------------------
	init_sdl();
	create_window();
	
	
//---------------------tests----------------------------------------
	
	WEM_bus bus01;
	WEM_machine machine_test;
	
	WEM_component compA;
	WEM_component compB;
	WEM_component compC;
	
	compA.data_size =128;
	compB.data_size =128;
	compC.data_size =128;
	

	WEM_bus_component bA;
	WEM_bus_component bB;
	WEM_bus_component bC;
	
	
	bA.active_bits=0x0000;
	bA.inactive_bits=0xfc00;
	
	bB.active_bits=0x0400;
	bB.inactive_bits=0xf800;
	
	bC.active_bits=0x1000;
	bC.inactive_bits=0x0000;
	
	bA.component = &compA;
	bB.component = &compB;
	bC.component = &compC;
	
	bus01.component[0]=&bA;
	bus01.component[1]=&bB;
	bus01.component[2]=&bC;
	
	bus01.components_connected = 3;
	
	machine_test.bus[0]=&bus01;
	
	
	//WEM_get_adressed_component(&machine_test,0,0x7680);
	//printf("rel_adress : %04x\n" , bus01.adress_buffer);
	
	
	uint8_t data_test[128];
	uint8_t data_test2[128];
	
	
	//data_test[37] = 0x69;
	
	memset(&data_test,0xaa,128);
	
	memset(&data_test2,0x00,128);
	
	data_test[37] = 0x69;
	
	compA.data = &data_test[0];
	compB.data = &data_test2[0];
	
	uint8_t read_test = WEM_read_bus( &machine_test,0,37);
	
	
	WEM_write_bus(&machine_test,0,0x0420,0x27);
	
	read_test = WEM_read_bus( &machine_test,0,0x0420);
	
	printf( "read data : %02x\n", read_test);
	
	
	
//---------------------Loop setup----------------------------------------------

	int frame_start = SDL_GetTicks();
	int frame_ms = 16;	//TODO: take this from settings struct
	
	SDL_bool run = SDL_TRUE;
	while (run)
	{
	
		SDL_Event event;
		while (SDL_PollEvent (&event))
		{
		
			switch (event.type)
			{
			
				case SDL_QUIT:
					run = SDL_FALSE;
					break;
						
			}
			
		}
		
		
		
		if ( SDL_GetTicks() - frame_start >= frame_ms )
		
		{
		
		SDL_RenderClear(renderer);
		
		
		SDL_RenderPresent(renderer);
		
		}
		
		
			
	}
	
}