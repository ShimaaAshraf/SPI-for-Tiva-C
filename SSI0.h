#ifndef  SSI_H_
#define  SSI_H_

// PA2 --> SSI0 CLK
// PA3 --> SSI0 frame signal
// PA4 --> SSI0 RX
// PA5 --> SSI0 TX


#include "Bit_Math.h"



/* configrations constants */
#define  LOW      0 
#define  HIGH     1 

#define  DISABLE     0 
#define  ENABLE      1 

#define  FIRST_EDGE      1 
#define  SECOND_EDGE     2

#define  SPI_FORMAT         0 
#define  TI_FORMAT          1 
#define  MICROWAVE_FORMAT   2

#define  MASTER    0 
#define  SLAVE     1 





/* SSI0 configrations */
#define  SSI0_BIT_RATE             1000000      //data rate = 1Mb/s
#define  SSI0_CLK_IDLE_STATE       LOW          //idle state of clk is low while there's no data transfer
#define  SSI0_CLK_CAPTURE_EDGE     FIRST_EDGE   //capture data at the first clk edge
#define  SSI0_FORMAT               SPI_FORMAT   //use SSI0 in SPI format
#define  SSI0_DATA_BITS            8            //SSI0 data size = 8-bits, (you can configure it as 4, 5, 6, ... 15, or 16 bits)
#define  SSI0_DEVICE_MODE          MASTER       //SSI0 is master
#define  SYSTEM_CLK               16000000UL    // Assume system clock is 16 MHz 



/* SSI0 necessary register defintoins */
#define  SSI0_CR0     (*(volatile int *)(0x40008000))    // SSI0 Control Register 0
#define  SSI0_CR1     (*(volatile int *)(0x40008004))    // SSI0 Control Register 1
#define  SSI0_DR      (*(volatile int *)(0x40008008))    // SSI0 Data Register
#define  SSI0_SR      (*(volatile int *)(0x4000800C))    // SSI0 staus Register
#define  SSI0_CPSR    (*(volatile int *)(0x40008010))    // SSI0 Clk Prescaler
#define  SSI0_IM      (*(volatile int *)(0x40008014))    // SSI0 Interrupts Mak register
#define  SSI0_RIS     (*(volatile int *)(0x40008018))    // SSI0 Interrupts Status register
#define  SSI0_ICR     (*(volatile int *)(0x40008020))    // SSI0 Interrupts Clear register


/* other register defintoins related to SSI0 */
#define  INTR_EN0      (*(volatile int *)(0xE000E100))    // Interrupts 0:32 enable register
#define  RCGCSSI       (*(volatile int *)(0x400FE61C))    // SSI clock control register
#define  RCGCGPIO      (*(volatile int *)(0x400FE608))    // GPIO clock control register
#define  GPIOAAFSEL    (*(volatile int *)(0x40004420))    // GPIOA Alternate Function Select register
#define  GPIOAPCTL     (*(volatile int *)(0x4000452C))    // GPIOA Port Control register
#define  GPIOADEN      (*(volatile int *)(0x4000451C))    // GPIOA Port Digital Enable
#define  GPIOAPUR      (*(volatile int *)(0x40004510))    // GPIOA Port PullUp Risitor


#define  NULL  (void *)0 


/* SSI0 necessary functions ptototypes */

/* Initialize SSI module 0 */
void  SSI0Init(void);

/* Tx data(parameter) & return Rx data */
unsigned short  SSI0ExchangeData(unsigned short data);


#endif
