/*
 * AD5721-bipolarDAC-ezlib.c
 *
 * Created: 7/10/2021 4:14:33 PM
 * Author : audiodiwhy
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include "ad5761.h"
#include "spi3.h"

uint16_t *data;


int main(void)
{

//	UartInit();


    init_spi_master();
	spi_mode(1);
    AD5761Init1010();



	
    while (1) 
    { 
	  for (uint16_t x = 0; x <= 65536; x++)
	  // for (uint8_t x = 0; x <= 10000; x++)
	    {	
		*data = x;
		//ramp wave!
        AD5761_out(*data);
		
		}

 
        
	} // end while

}  //end main