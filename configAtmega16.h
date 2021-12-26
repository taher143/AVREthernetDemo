#ifndef _CONFIG_H
#define _CONFIG_H

//atmega16
//#include <stdint.h>
#define F_CPU 8000000UL  // 11.0592 MHz
#define SPI_PORT    PORTB
#define SPI_DDR     DDRB

#define LED_PORT    PORTB
#define LED_DDR     DDRB

#define LIGHT_PORT PORTC
#define LIGHT_DDR  DDRC
#define DIMMER1_PORT PORTA
#define DIMMER1_DDR DDRA
#define DIMMER2_PORT PORTB
#define DIMMER2_DDR DDRB
#define DIMMER3_PORT PORTC
#define DIMMER3_DDR DDRC

//Interrupt 
#define INT0_INPUT_DDR DDRD
#define INT0_INPUT_DDD2 DDD2

//for Ethernet Interfacing
#define SPI_CS      PB4
#define SPI_MOSI    PB5
#define SPI_SCK     PB7
#define SPI_MISO    PINB6

//Status
#define STATUS_LED  PB0
#define STATUS_LED_DD DDB0

//SW1
#define LIGHT1     PC0     
#define LIGHT1_DD DDC0

//SW2
#define LIGHT2     PC1     
#define LIGHT2_DD DDC1

//SW3
#define LIGHT3     PC2     
#define LIGHT3_DD DDC2

//SW4
#define LIGHT4     PC3     
#define LIGHT4_DD DDC3

//SW5
#define LIGHT5     PC4     
#define LIGHT5_DD DDC4

//SW6
#define LIGHT6     PC5     
#define LIGHT6_DD DDC5

//DIMMER 1
#define DIMMER1_0     PA5     
#define DIMMER1_0_DD DDA5
#define DIMMER1_1     PA6     
#define DIMMER1_1_DD DDA6
#define DIMMER1_2     PA7     
#define DIMMER1_2_DD DDA7

//DIMMER 2
#define DIMMER2_0     PA2     
#define DIMMER2_0_DD DDA2
#define DIMMER2_1     PA3     
#define DIMMER2_1_DD DDA3
#define DIMMER2_2     PA4     
#define DIMMER2_2_DD DDA4

//DIMMER 3
#define DIMMER3_0     PB3     
#define DIMMER3_0_DD DDB3
#define DIMMER3_1     PA0     
#define DIMMER3_1_DD DDA0
#define DIMMER3_2     PA1     
#define DIMMER3_2_DD DDA1

//DIMMER 4
#define DIMMER4_0     PC6     
#define DIMMER4_0_DD DDC6
#define DIMMER4_1     PC7     
#define DIMMER4_1_DD DDC7
#define DIMMER4_2     PB2     
#define DIMMER4_2_DD DDB2

#endif
