//#include<stdio.h>
#include<stdlib.h>

#include"adress_logic.h"


WEM_bus_component* WEM_get_adressed_component(struct WEM_machine_struct *machine, int bus_id, uint16_t adress);

typedef struct WEM_bus_struct
{
	
	int adress_range;
	
	int components_connected;
	
	uint16_t adress_buffer;
	
	
	
	
	WEM_bus_component *component[16];			//TODO: get this from some settings
	
	
	
}WEM_bus;


typedef struct WEM_machine_struct
{
	
	
	uint32_t ticks_elapsed;
	
	WEM_bus *bus[8];
	WEM_clockable_component *clocked[8];
	
	
	
}WEM_machine;




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
	
	
	uint16_t mapped_adr = WEM_get_local_adress(selected, machine->bus[bus_id]->adress_buffer);
	
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

/*









void WEM_machine_tick(WEM_machine *machine);


void WEM_default_tick(WEM_machine *machine , WEM_component *component);


*/



