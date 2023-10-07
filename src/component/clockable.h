//#include<stdio.h>
#include<stdlib.h>
//#include"component.h"

struct WEM_machine_struct;

typedef struct WEM_clockable_struct
{
				//		delay:
	int delay;		//The tick function will only be called
				//if machine_cycle % delay == 0
		
				//		cycle:		
	uint32_t cycle;	//keeps tracks of how many cycles happened
				//since start to a component
				
//		tick_f_ptr:
//used to call specific tick() fuction from component
//should be linked on creation
				
	void (*tick_f_ptr)(struct WEM_clockable_struct*,int); 
	
//		component:
//Poiner to the component struct 
//used by tick function

	WEM_component *component;
	
	
}WEM_clockable_component;


