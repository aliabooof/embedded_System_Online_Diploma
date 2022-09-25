//startup.c
//eng.ali
#include <stdint.h>

void Reset_Handler();

void Default_Handler()
{
	Reset_Handler();
}

void H_Fault_Handler()__attribute__((weak, alias("Default_Handler")));;

void NMI_Handler()__attribute__((weak, alias("Default_Handler")));;

void MM_Fault_Handler()__attribute__((weak, alias("Default_Handler")));;

void Bus_Fault()__attribute__((weak, alias("Default_Handler")));;

void Usage_Fault_Handler()__attribute__((weak, alias("Default_Handler")));;

extern unsigned int _stack_top;

uint32_t vectors[] __attribute__((section(".vectors"))) = {
	(uint32_t) &_stack_top,
	(uint32_t) &Reset_Handler,
	(uint32_t) &H_Fault_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &MM_Fault_Handler,
	(uint32_t) &Bus_Fault,
	(uint32_t) &Usage_Fault_Handler,
	
};


extern unsigned int _E_text;
extern unsigned int _S_data;
extern unsigned int _E_data;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
void Reset_Handler()
{
	int i;
	unsigned int DATA_size=  (unsigned char *)&_E_data -  (unsigned char *)&_S_data ;
	unsigned char* p_src = (unsigned char*) _E_text ;
	unsigned char* p_dst = (unsigned char*) _S_data;
	//copy data section from flash to ram.
	
	for( i =0; i < DATA_size; i++)
	{
		*((unsigned char *)p_dst++) = *((unsigned char *)p_src++) ;
		
	}
	//init .bss sectoin in sram =0 
	unsigned int BSS_size = (unsigned char *)&_E_bss -  (unsigned char *)&_S_bss;
	p_dst = (unsigned char *)&_S_bss ;
	for( i =0; i < BSS_size; i++)
	{
		*((unsigned char *)p_dst++) = (unsigned char) 0 ;
		
	}
	// jump main

	
	main();
}
