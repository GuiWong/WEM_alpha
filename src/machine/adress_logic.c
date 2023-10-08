//#include<stdio.h>
#include<stdlib.h>

#include"machine.h"




WEM_bus_component*  WEM_get_adressed_component( WEM_machine *machine, int bus_id, uint16_t adress){


	//printf("starting decode...\n %d component found \n " , machine->bus[bus_id]->components_connected);
	for(int i = 0; i < machine->bus[bus_id]->components_connected ; i++)
	{
	
	
		//printf("trying component : %d\n", i );
		
		//printf("\n active bits: %04x \n", machine->bus[bus_id]->component[i]->active_bits);
		//printf("\n active mask result : %04x \n", machine->bus[bus_id]->component[i]->active_bits & adress);
		//printf("\n inactv mask result : %04x \n",  machine->bus[bus_id]->component[i]->inactive_bits & adress );
		
		//uint16_t effective_adress;
		if ( (( machine->bus[bus_id]->component[i]->active_bits & adress ) || machine->bus[bus_id]->component[i]->active_bits == 0) && 
			(( machine->bus[bus_id]->component[i]->inactive_bits & adress ) == 0 ) )
			
		{
		
			//printf("component selected : %d\n", i );
			machine->bus[bus_id]->adress_buffer = adress - machine->bus[bus_id]->component[i]->active_bits;
			return(machine->bus[bus_id]->component[i] );
		
		}
	
	}
	
	//TODO have a NOTHING component in bus
	
}


uint16_t WEM_get_local_adress(WEM_bus_component *bus_connect, uint16_t forwarded_adress)
{
	
	return (forwarded_adress);		//TODO: handle flags, mirroring etc
	
}



