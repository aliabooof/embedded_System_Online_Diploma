 
 
#ifndef Math_H_
#define Math_H_

#define SET_BIT(BYTE,BIT_NO) (BYTE |= (1<<BIT_NO))
#define CLR_BIT(BYTE,BIT_NO) (BYTE &= ~(1<<BIT_NO))
#define GET_BIT(BYTE,BIT_NO) ((BYTE >>BIT_NO) & 1)	// (((BYTE & (1<<BIT_NO))>>BIT_NO) && 1)
#define TOGGLE_BIT(BYTE,BIT_NO) (BYTE ^= (1<<BIT_NO))


#endif /* Math_H_ */
