#include "SSI0.h"



void  SSI0Init(void)
{
	SSI0_CR1 = 0;    // disable SSI0 to write on control registers
	
	RCGCSSI  |= 1;   //provide clock for SSI0
	RCGCGPIO |= 1;   //provide clock for port A to use pins PA2/SSI0Clk & PA3/SSI0Fss & PA4/SSI0Rx & PA5/SSI0Tx
	GPIOAAFSEL |= 0x0F<<2;   //set PA2, PA3, PA4, PA5 for alternate function
	GPIOAPCTL |= 0x222200;   //set PA2, PA3, PA4, PA5 alternate function for SSI0
	GPIOADEN  |= 0x0F<<2;    //enable digtal functoin for PA2, PA3, PA4, PA5 
	
	
	/* select clock polarity */
	#if  SSI0_CLK_IDLE_STATE  ==  LOW 
		//Do nothing because after reset idle state of clk is low while there's no data transfer
	#elif  SSI0_CLK_IDLE_STATE  ==  HIGH
		SET_BIT(SSI0_CR0, 6);   //set idle state of clk to be high while there's no data transfer
		SET_BIT(GPIOAPUR, 2);   // configure SSI0Clk pin (PA2) pin as a pull-up in GPIOPUR reg
	#endif
	
	
	
	/* select clock phase */
	#if  SSI0_CLK_CAPTURE_EDGE  ==  FIRST_EDGE
		//Do nothing because after reset data is captured at the first clk edge
	#elif  SSI0_CLK_CAPTURE_EDGE  ==  SECOND_EDGE
		SET_BIT(SSI0_CR0, 7);   //scapture data at the secobd clk edge
	#endif
	
	
	
	/* select format */
	#if  SSI0_FORMAT  ==  SPI_FORMAT
		//Do nothing because after reset SPI format is used
	#elif  SSI0_FORMAT  ==  TI_FORMAT
		SET_BIT(SSI0_CR0, 4);   //use SSI0 in Texas Instruments format
	#elif  SSI0_FORMAT  ==  MICROWAVE_FORMAT
		SET_BIT(SSI0_CR0, 5);   //use SSI0 in MICROWAVE format
	#endif
	
	
	
	/* select size of data bits */
	SSI0_CR0 |= (SSI0_DATA_BITS-1);
	
	
	
	/* select device mode (master or slave) */
	#if  SSI0_DEVICE_MODE  ==  MASTER
		//Do nothing because after reset device is master
	#elif  SSI0_DEVICE_MODE  ==  SLAVE
		SET_BIT(SSI0_CR1, 2);   //configure device as a slave
	#endif
	
	
	
	/* configure bit rate according to eqn --> BitRate = SysClk/(CPSDVSR * (1 + SCR)) */
	unsigned int clkDivFactor = SYSTEM_CLK / SSI0_BIT_RATE ;
	
	/* approximate clkDivFactor to an even number */
	if(clkDivFactor%2 == 1)		clkDivFactor--; 
	
	/* loop until CPSDVSR & SCR values satesfies that --> clkDivFactor = CPSDVSR * (1 + SCR) */
	unsigned char CPSDVSR_val = 254;
	unsigned char SCR_val = 0;
	while (CPSDVSR_val >= 2)
	{
		if(clkDivFactor%CPSDVSR_val == 0)
		{
			SCR_val = (unsigned char)(clkDivFactor/CPSDVSR_val - 1);
			break;
		}
		else if((CPSDVSR_val-2) * 256 > clkDivFactor)
		{
			CPSDVSR_val -= 2;
		}
		else
		{
			SCR_val = (unsigned char)(clkDivFactor/CPSDVSR_val - 1);
			break;
		}
	}
	
	/* store CPSDVSR & SCR values in the registers to get requred bit rate */
	SSI0_CR0 |= ((unsigned int)SCR_val)<<8;
	SSI0_CPSR = CPSDVSR_val;
	
	
	/* enable SSI0 */
	SET_BIT(SSI0_CR1, 1);
}


/* Tx data(parameter) & return Rx data */
unsigned short  SSI0ExchangeData(unsigned short data)
{
	while( GET_BIT(SSI0_SR, 0) == 0 );    //do nothing until SSI0 Tx FIFO empty
	
	unsigned short RxData = (unsigned short)SSI0_DR;  //read the recieved data
	SSI0_DR = data;  //send the data you want
	return RxData;
}

