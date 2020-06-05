#include <stdint.h>
#include "C:\Keil\EE319Kware\inc\tm4c123gh6pm.h"
void UART_init(void);
char UART_read(void);
void UART_write (char c);
void UART_write_str(char *string);
int UART_check_data(void);
