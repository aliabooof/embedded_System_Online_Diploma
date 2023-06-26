/*
 * MemMap.h
 *
 * Created: 12/20/2022 6:03:52 PM
 *  Author: aliab
 */ 


#ifndef MEMMAP_H_
#define MEMMAP_H_

#define SET_BIT(reg,bit)	(reg = reg | (1<<bit))
#define CLEAR_BIT(reg,bit)	(reg = reg &~ (1<<bit))
#define READ_BIT(reg,bit)	((reg>>bit)&1)
#define TOGGILE_BIT(reg,bit)	(reg = reg ^ (1<<bit))


#define PORTD  *(volatile unsigned char *)(0x32)
#define DDRD  *(volatile unsigned char *)(0x31)
#define PIND  *(volatile unsigned char *) (0x30)


#endif /* MEMMAP_H_ */