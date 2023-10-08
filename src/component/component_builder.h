//#include<stdio.h>
#include<stdlib.h>
//#include"component.h"

typedef struct WEM_machine_struct WEM_machine;


typedef struct WEM_component_struct WEM_component;




WEM_component* WEM_buildcomp_ram_basic( uint16_t size);

WEM_component* WEM_buildcomp_rom_basic( uint16_t size);
