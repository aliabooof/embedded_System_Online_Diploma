/* LINKER SCRIPT  CORTEXM3
END.ALI */
MEMORY
{
 	FLASH(RX) : ORIGIN = 0X8000000    , LENGTH = 128k
	SRAM(RWX)  : ORIGIN = 0X20000000 , LENGTH =	20k

}

SECTIONS
{
	
	.text : 
	{
		*(.vectors*) *(.text*) *(.rodata)
		. = ALIGN(4) ;
		_E_text = . ;
	}> FLASH
	.data :
	{    _S_data = . ;
		*(.data*)
			. = ALIGN(4) ;
		 _E_data = . ;
	}> SRAM AT> FLASH
	.bss  :
	{     _S_bss = . ;
		*(.bss*)
			. = ALIGN(4) ;
		 _E_bss = . ;
		 . = . + 0x1000;
		 Stack_top = . ;
	}> SRAM

}