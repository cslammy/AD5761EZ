/*
2-16-21 CL
stdio_setup.c
Derived from Elektor "learning Atmel C" course.

***Usage:
make sure to put this above main.c while(1) loop or things won't work.

UartInit();


****What this does:
Allows printf and sprintf statements 
in your Atmel 328 type C programs

Also appears to get serial data from outside world 
into the MPU (untested)

Works with UNO...
Or tap right from the TX RX pins of the MPU.


****Notes:
you must have these next 3 defines in this file.
you need to put them in your main.c as well, 
not sure why yet. Seems to not compile otherwise.

make sure to change F_CPU in both places.
*/

#define BAUD 9600
#define BAUD_TOL 2

#include <avr/io.h>
#include <stdio.h>
#include <util/setbaud.h>

void UartPutchar(char data);
int UartGetchar(void);

static FILE the_stdio = FDEV_SETUP_STREAM(UartPutchar, UartGetchar, _FDEV_SETUP_RW);

void UartInit(void)
{
	stdout = &the_stdio;
	stdin = &the_stdio;
	
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#endif

	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// 8-bit, 1 stop bit, no parity, asynchronous UART
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (0 << USBS0) |
	(0 << UPM01) | (0 << UPM00) | (0 << UMSEL01) |
	(0 << UMSEL00);
}

void UartPutchar(char data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

int UartGetchar(void)
{
	char data;
	
	while (!(UCSR0A & (1 << RXC0)));
	
	data = UDR0;
	
	if (data == '\n') {
		return -1;
	}
	UartPutchar(data);

	return data;
}