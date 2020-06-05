#include <stdint.h>
#include "UART.h"
#include "string.h"
#include "C:\Keil\EE319Kware\inc\tm4c123gh6pm.h"
int SystemInit(){
return 0;
}
typedef struct{
	int number;
	int status;// status 1(occupied),status 2(Free),status 3(cleaning)
	char password[5];
}Room;
//assuming we have one room to simulate on it
Room room={1,1,"0000"};
void LED_init(){
	SYSCTL_RCGCGPIO_R |= (1<<5);
	while((SYSCTL_PRGPIO_R & 0x20) ==0);
	GPIO_PORTF_LOCK_R=0x4C4F434B;
	GPIO_PORTF_DIR_R=0x0E;
	GPIO_PORTF_DEN_R=0x1F;
}

int main(void){
	int temp,check;
	int i;
	char temp_pass[5]="0000";
	UART_init();
	LED_init();
	while(1){
		UART_write_str("To change room data please enter room number\n");
		if( UART_check_data()== 1){
			if(((int) UART_read()-48)==room.number){
				UART_write_str("Please enter room new status\n");
				UART_write_str("1:Occupied\n2:Free\n3:Cleaning");
				temp=(int) UART_read()-48;
				if(temp==1){
					room.status=temp;
					UART_write_str("Please enter room new password\n");
					for(i=0;i<4;i++){
						room.password[i]=UART_read();
					}
				}else if(temp==2){
					room.status=temp;
				}else if(temp==3){
					room.status=temp;
				}else{
					UART_write_str("Error: unavailable status\n");
				}
			}
		}else if(UART_check_data() == 0){
			if(room.status==1){
				if(strcmp(temp_pass,room.password)==0){
					GPIO_PORTF_DATA_R=0x08;
					GPIO_PORTF_DATA_R=0x02;
				}else{
					GPIO_PORTF_DATA_R=0x02;
				}
			}else if(room.status==2){
				GPIO_PORTF_DATA_R=0x02;
			}else if(room.status==3){
				GPIO_PORTF_DATA_R=0x08;
			}
		}	
	}
	return 0;
}
