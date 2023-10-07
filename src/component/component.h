//#include<stdio.h>
#include<stdlib.h>
//#include<SDL2/SDL.h>
//#include <SDL2/SDL_image.h>


struct WEM_machine_struct;


enum
{

	WEM_C_ROM = 1,
	WEM_C_RAM = 2
};


enum
{

	WEM_CF_USE_READ_POINTER = 1,
	WEM_CF_USE_WRITE_POINTER= 2,
	WEM_CF_KEEP_ABSOLUTE_ADRESS = 4,
	WEM_CF_MIRROR_MODE_MODULO = 8		//adr_variant used as modulo on adr

};

typedef struct WEM_component_struct
{



//--------------Enums--------------------------------------
				
				
				//		type : 	
				//	enum for type of component
	int type;		//Will be used probably for creation, debug info
				//enum: define what kind of component it is
	
	
	int flags;		//		flags:
				//Used By Machine Logic when reading, writing,
				// calculaating adresses.
				//
				// can affect behavior of adress_offset
	
	
//------------Adress-Info----------------------------------------------------
	
	
//		adressable_range:
//define how many "adress bit" are used by this component			TODO: update comment when Machine

	uint16_t adressable_range;	
					
				
				
				//		bus_id:
	int bus_id;		//used as arg if this component emmit a Read/Wrie
				//Allow for multiple bus
	
				//		adress_variant:
	int adress_variant;	//used as parameter for Mirroring mode
				//additionnal data for adress calc
	
//------------function-Pointers-----------------------------------------------
//
//	those get called only if the corresponding flag is set 
//
//	their purpose is to implement specific behavior when read or write happens
//	simpler component would point to a generic WEM_Component_Read()
	
	uint8_t (*read_f_ptr)(struct WEM_machine_struct*, struct WEM_component_struct*,uint16_t) ;
	void (*write_f_ptr)(struct WEM_machine_struct*, struct WEM_component_struct*,uint16_t,uint8_t) ;	//is machine needed here??
	int (*ctrl_signal_ptr)(struct WEM_machine_struct*, struct WEM_component_struct*,uint8_t) ;
	
	
	void (*test)(struct WEM_machine_struct*,uint16_t) ;
	
//------------data------------------------------------------------------------

				//		data_size:
	uint16_t data_size;	//The number of bytes allocated to this component
				//
		
				//		data:		
	uint8_t *data;		//pointer to the first byte of memory
				//should be assigned on creation from malloc
	

}WEM_component;




