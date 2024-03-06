//Example ATmega2560 Project
//File: ATmega2560Project.c
//An example file for second year mechatronics project

//include this .c file's header file
#include "Controller.h"

//static function prototypes, functions only called in this file

int main(void)
{
  DDRA = 0;//put PORTA into input mode
  DDRA |= (1<<PA3); //PA3 output mode
  PORTA = 0; //set output of PORTA to low
  PORTA |= (1<<PA7); //enable internal pullup PA7

  DDRC = 0xFF; //put PORTC into output mode
  PORTC = 0; //low voltage

  adc_init(); //initialse ADC
  _delay_ms(20); //it's a good idea to wait a bit after your init section

  uint16_t adcVal = 0;
  uint8_t adc3 = 0;
  while(1)//main loop
  {
    if(!(PINA & (1<<7))){ //PA7 low / button pressed
      PORTA |= (1<<PA3);
      adcVal = adc_read(3); //read the voltage at ADC3 - returns 10bit value
      adc3 = (adcVal>>2); //Divide by 4 and express as 8bit value
    }
    else{ //PA7 high / button not pressed
      PORTA &= ~(1<<PA3);
      adcVal = adc_read(4); //read the voltage at ADC4 - returns 10bit value
      adc3 = (adcVal>>7); //Bitshift down to 3bit value and express as 8bits
    }
    switch(adc3){  //pins in portC set to high depending on position of joystick
      case 0:
        PORTC = 0;
        break;
      case 1:
        PORTC |= (1<<PA0);
        break;
      case 2:
        PORTC |= (1<<PA0)|(1<<PA1);
        break;
      case 3:
        PORTC |= (1<<PA0)|(1<<PA1)|(1<<PA2);
        break;
      case 4:
        PORTC |= (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3);
        break;
      case 5:
        PORTC |= (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4);
        break;
      case 6:
        PORTC |= (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5);
        break;
      case 7:
        PORTC |= (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6);
        break;
      case 8:
        PORTC |= (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7);
        break;
    }
  }
  return(1);
}//end main 

