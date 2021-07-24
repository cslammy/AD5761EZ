/*
 * ad5721.c
 *
 * Created: 7/10/2021 4:15:20 PM
 *  author AudioDiWHY
 */ 
//you send to 5761
#include <avr/io.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "ad5761.h"
#include "spi3.h"
#include "stdio_setup.h"


 

void AD5761Init1010(void)
{

//reset
 
SELECT();
//SPI_Transfer(0x0F); // full reset
SPI_Transfer(7); // soft reset
SPI_Transfer(0); //don't care
SPI_Transfer(0); // don't care
DESELECT();

 
SELECT();
SPI_Transfer(0x04); //control data
SPI_Transfer(0x02); // nominal setup zero at reset
SPI_Transfer(0x00); // 0= nominal setup  -10 to + 10 at output; midscale for data

DESELECT();
 

}

 void AD5761ControlRead(void)
    {
	uint8_t byte0, byte1, byte2;	
 
    SELECT();
    SPI_Transfer(0b00001100); // get ready to read control register
    SPI_Transfer(0xFF); //don't care
    SPI_Transfer(0xFF); // don't care
    DESELECT();
 

 
    SELECT();
    byte0 = SPI_Transfer(0b00001100); // read control register
    byte1 = SPI_Transfer(0xFF); //don't care
    byte2 = SPI_Transfer(0xFF); // don't care
 
    DESELECT();
    printf("\nContents of control reg 0: %x \n",byte0);
    printf("\nContents of control reg 1: %x \n",byte1);
    printf("\nContents of control reg 2: %x \n",byte2);
	}

void AD5761_out(uint16_t x)
        {
		
		
		SELECT();
		SPI_Transfer(3); // write dac register
		SPI_Transfer(x >> 8); //MSB data
		SPI_Transfer(x & 0xFF); //LSB  data 

		DESELECT();
		}
		

