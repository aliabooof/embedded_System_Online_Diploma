#define SYSCTL_RCGC2_R		(*((volatile unsigned int*) 0x400fe108))
#define GPIO_PORTF_DIR_R	(*((volatile unsigned int*) 0x4002551c))
#define GPIO_PORTF_DEN_R	(*((volatile unsigned int*) 0x40025400))
#define GPIO_PORTF_DATA_R	(*((volatile unsigned int*) 0x400253fc))


int main()	
{
	volatile unsigned long delay_count;
	SYSCTL_RCGC2_R = 0x00000020;
	for(delay_count = 0; delay_count < 200; delay_count++);
	GPIO_PORTF_DIR_R |= (1<<3);
	GPIO_PORTF_DEN_R |= (1<<3);
	while(1)
	{
		for(delay_count = 0; delay_count < 200000; delay_count++)
			GPIO_PORTF_DATA_R |= (1<<3);
		for(delay_count = 0; delay_count < 200000; delay_count++)
			GPIO_PORTF_DATA_R &= ~(1<<3);
		
	}
	return 0;
}