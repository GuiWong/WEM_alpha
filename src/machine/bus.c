//#include<stdio.h>
#include<stdlib.h>

//#include"adress_logic.h"


//WEM_bus_component* WEM_get_adressed_component(struct WEM_machine_struct *machine, int bus_id, uint16_t adress);

typedef struct WEM_bus_struct
{
	
	int adress_range;
	
	int components_connected;
	
	uint16_t adress_buffer;
	
	
	
	
	WEM_bus_component *component[16];			//TODO: get this from some settings
	
	
	
}WEM_bus;









