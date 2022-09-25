typedef volatile unsigned int vuint32_t;
#define RCC_base  0x40021000
#define GPIO_base 0x40010800
#define APB2ENR 	*(volatile vuint32_t *)(RCC_base + 0x18)
#define GPIOA_CRH 	*(volatile vuint32_t *)(GPIO_base + 0x04)
#define GPIOA_ODR *(volatile vuint32_t *)(GPIO_base + 0x0C)

typedef union{

	vuint32_t all_fields;
	struct {
		vuint32_t reserved:13;
		vuint32_t p_13:1;
	} pin;
} R_ODR_t;

volatile R_ODR_t * R_ODR = (volatile R_ODR_t* )(GPIO_base + 0x0C);




int main(void)
{
	int i;
	APB2ENR |= (1<<2);
	GPIOA_CRH &= 	0xff0fffff;
	GPIOA_CRH |=	0X00200000;

	while(1)
	{
		R_ODR->pin.p_13=1;
		for( i=0;	i<5000	;i++);
		R_ODR->pin.p_13=0;
		for( i=0;i<5000;i++);
	}
}
