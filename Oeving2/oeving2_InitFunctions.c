#include "oeving2.h"
#include "sys/interrupts.h"

/* funksjon for å initialisere maskinvaren, må utvides */
void initHardware(void){
  initIntc();
  initAudio();
  initLeds();
  initButtons();
}

void initIntc(void){
  set_interrupts_base((void *)AVR32_INTC_ADDRESS);
  init_interrupts();
}

void initButtons(void){
  register_interrupt(button_isr, AVR32_PIOB_IRQ/32, AVR32_PIOB_IRQ % 32, BUTTONS_INT_LEVEL);
  //Setting the below switch-values to variable active
  short active = SW7+SW6+SW5+SW4+SW3+SW2+SW0;
  piob->per = active; //Activating switches in variable active
  piob->puer = active; //Activating switches in variable active
  piob->ier = active; //Activating interrupt for switches in variable active
  //Disable the rest of the switches
  piob->idr = ~active;
  pioc->codr = 0xff;
  pioc->sodr = SW0;
}

void initLeds(void){
  //Enable all LEDs on PIOB
  pioc->per = 0xff; //0xff == all LEDs
  pioc->oer = 0xff;
}

void initAudio(void){
  //Oppsett av PowerManager for klokke og abdac...
  //Sampler hver 256. positive flanke
  pm->GCCTRL[6].oscsel = 1;
  pm->GCCTRL[6].diven = 0;
  //pm->GCCTRL[6].div = SHRT_MAX/2;
  pm->GCCTRL[6].pllsel = 0;
  pm->GCCTRL[6].cen = 1;
  register_interrupt(abdac_isr, AVR32_ABDAC_IRQ/32, AVR32_ABDAC_IRQ % 32, ABDAC_INT_LEVEL);
  piob->PDR.p20 = 1;
  piob->PDR.p21 = 1;
  piob->ASR.p20 = 1;
  piob->ASR.p21 = 1;
  setAbdacOnOff(1);
}

void setAbdacOnOff(int value){
  if(value != abdac->CR.en &&
    value != abdac->IER.tx_ready){
    abdac->CR.en = value;
    abdac->IER.tx_ready = value;
  }
}
