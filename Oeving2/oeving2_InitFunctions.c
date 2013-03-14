#include <stdlib.h>
#include "oeving2.h"
#include "sys/interrupts.h"

//Since this is the file utilizing the extern type-modified pointers below, we initialize them here with the values given in the code supplied to us.
volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;
volatile avr32_pm_t *pm = &AVR32_PM;
volatile avr32_abdac_t *abdac = &AVR32_ABDAC;


/* funksjon for å initialisere maskinvaren, må utvides */
void initHardware(void){
	initIntc();
	initAudio();
	initLeds();
	initButtons();
}

//Function of initializing interruptController.
void initIntc(void){
	set_interrupts_base((void *)AVR32_INTC_ADDRESS);
	init_interrupts();
}

//Function for initalizing buttons
void initButtons(void){
	//The below line tells the interruptController to call the button_isr() function when the buttons send an interrupt, with the interrupt priority-level set in a macro given to us in the supplied code.
	register_interrupt(button_isr, AVR32_PIOB_IRQ/32, AVR32_PIOB_IRQ % 32, BUTTONS_INT_LEVEL);


	//The below line initializes variable 'active' with the combined values of the switches listes on the right hand side of the equals sign.
	short active = SW7+SW6+SW5+SW4+SW3+SW2+SW0;

	//Below we activate the switches by writing to the PIOEnableRegister, Pull-upEnableRegister, and InterruptEnableRegister
	piob->per = active;
	piob->puer = active;
	piob->ier = active;

	//Below we disable the rest of the switches by sending the inverted value of the 'active' variable to the buttons InterruptDisableRegister
	piob->idr = SW1;
}

//Function for initializing LEDs
void initLeds(void){
	//Below we initialize all the LEDs by writing the hex-value 0xff to the PIOEnableRegister for the LEDs
	pioc->per = 0xff; //0xff == all LEDs
	//Below we allow all the LEDs to have an output vale (AKA enabling the LEDs SetOutputData and ClearOutputData Register)
	pioc->oer = 0xff;

	//Below we first turn all the LEDs off, before we turn on the LED for SW0 (Indicating that we start with silence...)
	pioc->codr = 0xff;
	pioc->sodr = SW0;
}

//Function for initializing ABDAC (Audio)
void initAudio(void){
	//Below we use the PowerManager first to choose which oscillator we want the ABDAC to utilize
	pm->GCCTRL[6].oscsel = 1;
	//Then below we set the diven (Divide Enable) register to zero to turn it off.
	pm->GCCTRL[6].diven = 0;
	//Then below we choose which PLL we want to use
	pm->GCCTRL[6].pllsel = 0;
	//Then finally we turn the cen register (ClockEnable) to one, turning it on.
	pm->GCCTRL[6].cen = 1;

	//Below we tell the InterruptController to call the abdac_isr function each time the abdac receives an interrupt, and make each interrupt call with the ABDAC_INT_LEVEL as interrupt-priority level
	//(Much like the corresponding line in initButtons())
	register_interrupt(abdac_isr, AVR32_ABDAC_IRQ/32, AVR32_ABDAC_IRQ % 32, ABDAC_INT_LEVEL);

	//Below we setup PIOB to be used by ABDAC (Basically connecting the ABDAC to PIOB)
	piob->PDR.p20 = 1;
	piob->PDR.p21 = 1;
	piob->ASR.p20 = 1;
	piob->ASR.p21 = 1;

	//Here we call the function setAbdacOnOff with parameter 1 to turn the abdac on
	setAbdacOnOff(1);
}

//Function we wrote to easily turn ABDAC on and off
void setAbdacOnOff(int value){

	//We read in parameter value, and make sure it is not the same as the value abdac->CR.en and abdac->IER.tx_ready already have
	//(Meaning that this function will do nothing when the function is sent parameter zero and the abdac is turned off, or vica versa with parameter equalling 1)
	if(value != abdac->CR.en &&
		value != abdac->IER.tx_ready){

		//If the two values however do differ, set the abddac-members to the new value
		abdac->CR.en = value;
		abdac->IER.tx_ready = value;
	}
}
