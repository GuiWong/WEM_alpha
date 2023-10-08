//#include<stdio.h>
#include<stdlib.h>
//#include<SDL2/SDL.h>
//#include <SDL2/SDL_image.h>


struct WEM_machine_struct;

typedef struct WEM_component_struct WEM_component;



void WEM_defaultPPU_tick(WEM_machine *machine , WEM_component *component,uint32_t current_tick);

void WEM_defaultPPU_draw_frame(WEM_machine* machine,WEM_screen* screen);
