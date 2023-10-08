//#include<stdio.h>
#include<stdlib.h>

#include"adress_logic.h"


//typedef struct WEM_bus_struct WEM_bus;


typedef struct WEM_bus_component_struct WEM_bus_component;

typedef struct WEM_component_struct WEM_component;


typedef struct WEM_machine_struct WEM_machine;




//-------------------Connector function------------------------------//



WEM_bus_component* WEM_comp_connect_basic(WEM_machine *machine,WEM_component *component ,int bus_id,uint16_t active, uint16_t inactive);





void WEM_write_bus(WEM_machine *machine,int bus_id,uint16_t adress, uint8_t data);

uint8_t WEM_read_bus(WEM_machine *machine,int bus_id,uint16_t adress);


void WEM_write_comp(WEM_machine *machine, WEM_component *component , uint16_t local_adress, uint8_t data);

uint8_t WEM_read_comp(WEM_machine *machine, WEM_component *component , uint16_t local_adress);

void WEM_machine_tick(WEM_machine *machine);

void WEM_default_tick(WEM_machine *machine , WEM_component *component);





