//#include<stdio.h>
#include<stdlib.h>

#include"adress_logic.h"
#include"bus.c"



/*

typedef struct WEM_bus_struct
{
	
	int adress_range;
	
	int components_connected;
	
	uint16_t adress_buffer;
	
	
	
	
	WEM_bus_component *component[16];			//TODO: get this from some settings
	
	
	
}WEM_bus;

*/


typedef struct WEM_machine_struct
{
	
	
	uint32_t ticks_elapsed;
	int clockable_count;
	int frame_clockable_count;
	
	WEM_bus *bus[8];
	WEM_clockable_component *clocked[8];
	
	WEM_clockable_component *frame_clocked[8];
	
	WEM_screen *screen;
	
	
	
}WEM_machine;




//--------------------connector-------------------------------------------




WEM_bus_component* WEM_comp_connect_basic(WEM_machine *machine, WEM_component *component ,int bus_id,uint16_t active, uint16_t inactive)
{

	WEM_bus_component *bus_item = (WEM_bus_component*)malloc(sizeof(WEM_bus_component));
	
	bus_item->active_bits = active;
	bus_item->inactive_bits = inactive;
	
	bus_item->flag = WEM_BUS_MODULO;
	
	bus_item->component = component;
	
	
	
	machine->bus[bus_id]->component[ machine->bus[bus_id]->components_connected ] = bus_item;
	
	machine->bus[bus_id]->components_connected+=1;
	
	return(bus_item);

}





uint8_t WEM_read_comp(WEM_machine *machine, WEM_component *component , uint16_t local_adress)
{
	/*
	uint8_t (*memory)[component->data_size];
	memory = component->data;
	uint8_t data = *memory[local_adress];
	
	*/
	uint8_t data = *(component->data + local_adress);
	
	return (data);
	
}



uint8_t WEM_read_bus(WEM_machine *machine,int bus_id,uint16_t adress)
{

	WEM_bus_component *selected = WEM_get_adressed_component(machine,  bus_id,  adress);
	
	
	uint16_t mapped_adr = WEM_get_local_adress(selected, machine->bus[bus_id]->adress_buffer);		//should i call a func in bus.c?
	
	return (WEM_read_comp(machine , selected->component, mapped_adr));


}

void WEM_write_comp(WEM_machine *machine, WEM_component *component , uint16_t local_adress, uint8_t data)
{

	*(component->data + local_adress) = data;

}


void WEM_write_bus(WEM_machine *machine,int bus_id,uint16_t adress, uint8_t data)
{

	WEM_bus_component *selected = WEM_get_adressed_component(machine,  bus_id,  adress);
	
	
	uint16_t mapped_adr = WEM_get_local_adress(selected, machine->bus[bus_id]->adress_buffer);

	WEM_write_comp(machine ,selected->component , mapped_adr , data);
}











void WEM_machine_tick(WEM_machine *machine){


	//printf("MACHINE TICK : %d\n" , machine->ticks_elapsed);
	
	machine->ticks_elapsed+=1;
	
	if (machine->clockable_count > 0)
	{
	
		for(int i=0;i<machine->clockable_count;i++)
		{
		
			machine->clocked[i]->tick_f_ptr(machine, machine->clocked[i]->component , machine->clocked[i]->cycle);
			machine->clocked[i]->cycle +=1;
		
		}
	
	}

}



void WEM_frame_tick(WEM_machine *machine){


	//printf("FRAME TICK \n");//machine->ticks_elapsed);
	
	//machine->ticks_elapsed+=1;
	
	if (machine->frame_clockable_count > 0)
	{
	
		for(int i=0;i<machine->frame_clockable_count;i++)
		{
		
			machine->frame_clocked[i]->tick_f_ptr(machine, machine->frame_clocked[i]->component , machine->frame_clocked[i]->cycle);
			machine->frame_clocked[i]->cycle +=1;
		
		}
	
	}

}




void WEM_default_tick(WEM_machine *machine , WEM_component *component,uint32_t current_tick)
{

	printf("one clockable component has no tick() pointer \n");

}






