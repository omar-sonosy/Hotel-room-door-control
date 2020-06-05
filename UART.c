#include <stdint.h>
#include "C:\Keil\EE319Kware\inc\tm4c123gh6pm.h"
#include "UART.h"

void UART_init(void){
	int i=0,j;
	SYSCTL_RCGCUART_R |= (1<<0);
	SYSCTL_RCGCGPIO_R |= (1<<0);
	UART0_CTL_R &= ~(1<<0);
	UART0_IBRD_R=104;
	UART0_FBRD_R=11;
	UART0_LCRH_R = (7<<4);
	UART0_CTL_R = (1<<0)|(1<<8)|(1<<9);
	GPIO_PORTA_AFSEL_R |= (0x03);
	GPIO_PORTA_PCTL_R &= ~(0xFF);
	GPIO_PORTA_PCTL_R |= (1<<4) |(1<<0);
	GPIO_PORTA_DEN_R |= (0x03);
	GPIO_PORTA_AMSEL_R &= ~(0x03);
}
char UART_read(void){
	
	while((UART0_FR_R & (1<<4)) !=0);
		
		return (char)(UART0_DR_R &0xFF);
}
void UART_write (char c){
	
	while((UART0_FR_R &(1<<5)) !=0 );
	
	UART0_DR_R = c;
}
void UART_write_str(char *string){
	int i=0;
	while(string[i] !='\0'){
		UART_write(string[i]);
		i++;
	}
}
int UART_check_data(void){
	if((UART0_FR_R & (1<<4)) !=0)
		return 0;
	else
		return 1;
}
