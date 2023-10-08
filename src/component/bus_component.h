//#include<stdio.h>
#include<stdlib.h>
//#include"component.h"



enum
{

	WEM_BUS_DIRECT = 1,		// 1 : module receive direct adress. should be used with custom R/W function
					// 0 : module receive relative adress
	WEM_BUS_MODULO = 2,		//
	WEM_BUS_CUSTOM_LIMIT=4,
	WEM_BUS_PRECISE_MODE=8,
	
	WEM_BUS_FUNCTION=256
	
	
};


typedef struct WEM_bus_component_struct
{
				
	
	int flag;
	
//		active_bits:
//those bits must be on for the component to answer

	uint16_t active_bits;
	
//		inactive_bits:
//those bits must be off for th component to answer
	uint16_t inactive_bits;
	
	
//		limit:
//can be used for mirroring data at other limits
//than component adressable_range
	uint16_t limit;
	
//		component:
//Poiner to the component struct 
//used by tick function

	WEM_component *component;
	
	
}WEM_bus_component;


