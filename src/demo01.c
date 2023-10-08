#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>




#include"component/component.h"
#include"component/clockable.h"
#include"component/bus_component.h"


#include"component/graphic/default_screen.c"
#include"component/graphic/default_PPU.c"




//#include"machine/machine.h"
//#include"machine/bus.c"


#include"machine/machine.c"

#include"machine/adress_logic.c"



#include"component/component_builder.c"





SDL_Texture *screen_text;





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





void test_tick_f(WEM_machine *machine , WEM_component *component,uint32_t current_tick)
{

	WEM_write_bus(machine,0, 0x4000  + (  current_tick % (128 * 128)) , (current_tick / (128 * 128) )% 256);

}




void main()
{


//-------------------SDL init--------------------------------------------------------------
	init_sdl();
	create_window();
	
	
	screen_text = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB332,SDL_TEXTUREACCESS_STREAMING,128,128);
	
	
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
	bC.inactive_bits=0xc000;
	
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
	uint8_t *data_test3 = (uint8_t*)malloc(128*128 * sizeof(uint8_t));
	
	
	//data_test[37] = 0x69;
	
	memset(&data_test,0xaa,128);
	
	memset(&data_test2,0x00,128);
	
	memset(data_test3,0x03,128*32);
	
	memset(data_test3+128*32,0xa0,128*32);
	memset(data_test3+128*64,0x1c,128*64);
	
	
	//data_test[37] = 0x69;
	
	
	
	WEM_component *compD = WEM_buildcomp_ram_basic(256);
	WEM_bus_component *bD= WEM_comp_connect_basic(&machine_test,compD,0,0x4000,0x8000);
	
	compD->data = data_test3;
	
	
	
	WEM_screen screen_test;
	
	screen_test.size_x = 128;
	screen_test.size_y =128;
	screen_test.component = compD;
	screen_test.texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB332,SDL_TEXTUREACCESS_STREAMING,screen_test.size_x,screen_test.size_y);
	
	
	screen_test.frame_f_ptr = WEM_defaultPPU_draw_frame;
	
	machine_test.screen = &screen_test;
	
	
	
	
	WEM_component *compE = WEM_buildcomp_ram_basic(8);
	WEM_bus_component *bE= WEM_comp_connect_basic(&machine_test,compD,0,0xfff8,0x0000);
	
	WEM_clockable_component clk_test;
	
	clk_test.component = compE;
	
	clk_test.tick_f_ptr = test_tick_f;
	//clk_test.tick_f_ptr = WEM_defaultPPU_tick;
	
	
	
	machine_test.clocked[0] = &clk_test;
	
	machine_test.clockable_count = 1;
	
	//machine_test.frame_clocked[0] = &clk_test;
	
	machine_test.frame_clockable_count = 0;
	
	
	compA.data = &data_test[0];
	compB.data = &data_test2[0];
	
	
	
	uint8_t read_test = WEM_read_bus( &machine_test,0,0x4012);
	
	//uint8_t read_test = WEM_read_bus( &machine_test,0,0x0015);
	
	printf( "read data : %02x\n", read_test);
	
	
	WEM_write_bus(&machine_test,0,0x4020,0x27);
	
	read_test = WEM_read_bus( &machine_test,0,0x4020);
	
	printf( "read data : %02x\n", read_test);
	
	
	
	machine_test.ticks_elapsed = 0;
	
	
	
//---------------------Loop setup----------------------------------------------

	int frame_start = SDL_GetTicks();
	int frame_ms = 16;	//TODO: take this from settings struct
	
	int sim_running = 0;
	int sim_overclocked=0;
	int frame_overclocked=1;
	
	
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
						
						
				case SDL_KEYDOWN:
				
					switch(event.key.keysym.scancode)
					{
					
						case SDL_SCANCODE_C:
						
							WEM_machine_tick(&machine_test);
							break;
						
						case SDL_SCANCODE_F:
						
						
							
							WEM_frame_tick(&machine_test);
							
							SDL_RenderCopy(renderer,screen_text,NULL,&(SDL_Rect){0,0,256,256});
							SDL_RenderPresent(renderer);
							break;
							
						case SDL_SCANCODE_D:
						
							machine_test.screen->frame_f_ptr(&machine_test , &screen_test);
							SDL_RenderCopy(renderer,screen_test.texture,NULL,&(SDL_Rect){0,0,256,256});
							SDL_RenderPresent(renderer);
							break;
							
						case SDL_SCANCODE_V:
						
							sim_running = !sim_running;
							sim_overclocked = 0;
							break;
							
						case SDL_SCANCODE_B:
						
							sim_running = 0;
							sim_overclocked = !sim_overclocked;
							break;
							
						case SDL_SCANCODE_N:
	
							frame_overclocked = !frame_overclocked;
							break;
					
					}
			}
			
		}
		
		
		
		if (sim_overclocked)
		{
		
			
			WEM_machine_tick(&machine_test);
		
			//WEM_frame_tick(&machine_test);
			
			
			if (frame_overclocked)
			{
				SDL_RenderClear(renderer);
				machine_test.screen->frame_f_ptr(&machine_test , &screen_test);
				
				//SDL_Delay(1);		
				SDL_RenderCopy(renderer,screen_test.texture,NULL,&(SDL_Rect){0,0,256,256});
				SDL_RenderPresent(renderer);
			}
		
		}
		
		if ( SDL_GetTicks() - frame_start >= frame_ms )
		
		{
		
		
		
			if (sim_running | !frame_overclocked)
			{
		
				SDL_RenderClear(renderer);
				WEM_machine_tick(&machine_test);
		
				WEM_frame_tick(&machine_test);
			
			
				machine_test.screen->frame_f_ptr(&machine_test , &screen_test);
				
				//SDL_Delay(1);		
				SDL_RenderCopy(renderer,screen_test.texture,NULL,&(SDL_Rect){0,0,256,256});
				SDL_RenderPresent(renderer);

		
			}
			
			
			frame_start = SDL_GetTicks();
		
		}
		
		
			
	}
	
}
