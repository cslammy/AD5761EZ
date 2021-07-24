/*
 * spi3.c
 *

 i got this off the off the AVR site's examples, 
but needed to make a few changes.

setup:
 You must set pin #define correctly in spi3.h for given hardware or this won't work.
 EG: For uno: MISO is PB4, MOSI is PB4, SCK is PB5
 SPI_CS can be whatever pin you want (make sure to set it as output).
 
 
use:

 make sure to SELECT() before i/o and DESELECT() when done with i/o
 
 use spi_mode(x) to set SPI mode 1,2,3, any other value is mode 0.
 
 AVR chip is always master while using this library.
 
 also:
 your c file with main{} will need to #include <avr/io.h> or this won't compile.
 */ 


#include <avr/io.h>
#include "spi3.h"



void init_spi_master(void)
{
	/* SPI pins */
	SPIDDR |= (SPI_MOSI | SPI_CS | SPI_SCK); /* Set outputs */
	SPIPORT |= SPI_MISO; /* Pull up on SPI_MISO within AVR chip */

	/* Master Mode, 100-400kHz clk  */
	/* Setup Peripheral Clock Prescaler */
	
	/* SPI Master mode */
	SPCR |= (1 << MSTR);
	/* Set SPI speed fast as possible */
	SPCR &= ~(1 << SPR1);  
	SPSR &= ~(1 << SPR0); // clock divided by 4
	SPSR |= (1 << SPI2X); // double speed
	
	/* SPI Enable */
	SPCR |= (1 << SPE);
}


void spi_mode(unsigned char mode)
{
if (mode == 1)
	{
	SPCR |= (0 << CPOL);
	SPCR |= (1 << CPHA);
	}
if (mode == 2)
	{
	SPCR |= (1 << CPOL);
	SPCR |= (0 << CPHA);
	}
if (mode == 3)
	{
	SPCR |= (1 << CPOL);
	SPCR |= (1 << CPHA);
	}
else
		{
    	SPCR |= (0 << CPOL);
    	SPCR |= (0 << CPHA);	
		}
	
}

 uint8_t SPI_Transfer(uint8_t data)
 {
    
	 SPDR = data;
	 while (!(SPSR & (1<<SPIF)));
	 return SPDR;
     
 }
 
 uint8_t SPI_TransferTx16(unsigned char a, unsigned char b)
 {
	 unsigned char x;
	 SELECT();
	 x = SPI_Transfer(a);
	 DESELECT();
	 SELECT();
	 x = SPI_Transfer(b);
	 DESELECT();
	 return x;

 }

