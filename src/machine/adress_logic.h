//#include<stdio.h>
#include<stdlib.h>



WEM_bus_component* WEM_get_adressed_component(struct WEM_machine_struct *machine, int bus_id, uint16_t adress);

uint16_t WEM_get_local_adress(WEM_bus_component *bus_connect, uint16_t forwarded_adress);
