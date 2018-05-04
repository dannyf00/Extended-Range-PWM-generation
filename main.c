//#include <avr/io.h>							//we use gcc-avr
#include "gpio.h"
#include "delay.h"							//we use software delays
//generating 16-bit pwm on 8-bit pwm generators
//ATtiny85, PWM0
//
//principle: like in a DDS, pwm errors are accumlated and then automatically corrected
//when enough errors have been accumulated
//
//
#include "pwm0.h"

//hardware configuration
//end hardware configuration

//global defines


//global variables

//initialize pwm16
void pwm_init(uint8_t ps) {
	pwm0_init(ps);							//initialize pwm
}

//extending pwm to 10-bit
uint16_t pwm10_setdc(uint16_t dc) {
	static uint16_t pwm_dc=0;				//msb to pwm generator

	pwm_dc += dc;							//increment pwm_dc
	pwm0a_setdc(pwm_dc >> 2);				//output the top 8 bits
	pwm_dc &= 0x0003;						//clear the top 8 bits
	return pwm_dc;							//return the remainder
}

//extending pwm to 12-bit
uint16_t pwm12_setdc(uint16_t dc) {
	static uint16_t pwm_dc=0;				//msb to pwm generator

	pwm_dc += dc;							//increment pwm_dc
	pwm0a_setdc(pwm_dc >> 4);				//output the top 8 bits
	pwm_dc &= 0x000f;						//clear the top 8 bits
	return pwm_dc;							//return the remainder
}

//extending pwm to 16-bit
uint16_t pwm16_setdc(uint16_t dc) {
	static uint16_t pwm_dc=0;				//msb to pwm generator

	pwm_dc += dc;							//increment pwm_dc
	pwm0a_setdc(pwm_dc >> 8);				//output the top 8 bits
	pwm_dc &= 0x00ff;						//clear the top 8 bits
	return pwm_dc;							//return the remainder
}


int main(void) {

	mcu_init();								//reset the mcu
	pwm_init(TMR0_PS1x);					//initialize pwm

	while(1) {
		//pwm10_setdc(400);					//set duty cycle
		//pwm12_setdc(400);					//set duty cycle
		pwm16_setdc(400);					//set duty cycle
		delay(1000);						//let the pwm to be generated
	}

	return 0;
}
