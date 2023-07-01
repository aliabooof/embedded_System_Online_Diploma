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

#define PORTA  *(volatile unsigned char *)(0x3B)
#define DDRA  *(volatile unsigned char *)(0x3A)
#define PINA  *(volatile unsigned char *) (0x39)


#define PORTC  *(volatile unsigned char *)(0x35)
#define DDRC  *(volatile unsigned char *)(0x34)
#define PINC  *(volatile unsigned char *) (0x33)


#endif /* MEMMAP_H_ */