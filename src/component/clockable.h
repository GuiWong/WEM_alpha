//#include<stdio.h>
#include<stdlib.h>
//#include"component.h"

typedef struct WEM_machine_struct WEM_machine;

typedef struct WEM_clockable_struct
{

				//		wait_frame:
	int wait_frame;	//	if >0 : only call the tick() on complete frame
	
	
				//		delay:
	int delay;		//The tick function will only be called
				//if machine_cycle % delay == 0
		
				//		cycle:		
	uint32_t cycle;	//keeps tracks of how many cycles happened
				//since start to a component
				
//		tick_f_ptr:
//used to call specific tick() fuction from component
//should be linked on creation
				
	void (*tick_f_ptr)(WEM_machine* , WEM_component*,uint32_t); 
	
//		component:
//Poiner to the component struct 
//used by tick function

	WEM_component *component;
	
	
}WEM_clockable_component;


