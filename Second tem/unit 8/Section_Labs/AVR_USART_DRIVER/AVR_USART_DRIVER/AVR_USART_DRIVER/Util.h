/*
 * Util.h
 *
 * Created: 9/12/2023 1:25:37 AM
 *  Author: aliab
 */ 


#ifndef UTIL_H_
#define UTIL_H_

#define SET_BIT(address,bit) address |= (1<<bit)
#define CLEAR_BIT(address,bit) address &= ~(1<<bit)
#define TOGGLE_BIT(address,bit) address ^= (1<<bit)
#define READ_BIT(address,bit) ((address >> bit)&1)



#endif /* UTIL_H_ */