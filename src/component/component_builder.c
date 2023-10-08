//#include<stdio.h>
#include<stdlib.h>
//#include"component.h"

typedef struct WEM_machine_struct WEM_machine;


typedef struct WEM_component_struct WEM_component;





//	All the builder function do the same basic thing:
//
//	1.	Allocate memory for a component struct
//
//	2.	Setup component data
//
//	3.	Return a pointer to the struct



//Additionnal info on each func will only refer to 2.)
//unless specified otherwise









//		WEM_buildcomp_ram_basic:
//
//	arg: size
//
//	set type to ram
//	set READ_ONLY flag
//	set adressable_range = data_size = size

WEM_component* WEM_buildcomp_ram_basic( uint16_t size)
{

	WEM_component *comp = (WEM_component*)malloc(sizeof(WEM_component));
	
	comp->type = WEM_C_RAM;
	
	comp->adressable_range = size;
	comp->data_size = size;
	
	return(comp);

}


//WEM_component* WEM_buildcomp_rom_basic( uint16_t size);
