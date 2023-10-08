//#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include"default_screen.h"


struct WEM_machine_struct;

typedef struct WEM_component_struct WEM_component;

SDL_Texture *screen_text;



void WEM_defaultPPU_tick(WEM_machine *machine , WEM_component *component,uint32_t current_tick)
{

	
	char *lockedPixels = NULL;
	int pitch;
	//printf("test2\n");
	if(SDL_LockTexture( screen_text,NULL,(void*)&lockedPixels, &pitch) <0)
	{
		printf("eror: %s\n",SDL_GetError());
	}

	for(int l=0; l<128;l++)
	{
	
		for(int c=0; c<128;c++)
		{
			lockedPixels[128*l + c] = *(component->data + (128*l + c) );
			//lockedPixels[64*l + c] = palette[( rand() & 0x0f)];
		}
	
	}

	
	SDL_UnlockTexture( screen_text );
	
	

}



void WEM_defaultPPU_draw_frame(WEM_machine* machine,WEM_screen* screen)
{

	char *lockedPixels = NULL;
	int pitch;
	//printf("test2\n");
	if(SDL_LockTexture( screen->texture,NULL,(void*)&lockedPixels, &pitch) <0)
	{
		printf("eror: %s\n",SDL_GetError());
	}

	for(int l=0; l< screen->size_y;l++)
	{
	
		for(int c=0; c< screen->size_x;c++)
		{
			lockedPixels[128*l + c] = *(screen->component->data + (128*l + c) );
			//lockedPixels[64*l + c] = palette[( rand() & 0x0f)];
		}
	
	}

	
	SDL_UnlockTexture( screen->texture );

}





