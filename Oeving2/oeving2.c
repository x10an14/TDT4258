/*****************************************************************************
 *
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include "oeving2.h"
#include "sys/interrupts.h"

volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;
volatile avr32_pm_t *pm = &AVR32_PM;
volatile avr32_abdac_t *abdac = &AVR32_ABDAC;


int main (int argc, char *argv[]){
  initHardware();

  while(1);
  return 0;
}

/* funksjon for å initialisere maskinvaren, må utvides */
void initHardware (void){
  initIntc();
  initLeds();
  initButtons();
  initAudio();
}


void initIntc(void){
  set_interrupts_base((void *)AVR32_INTC_ADDRESS);

  init_interrupts();
}

void initButtons(void){
  //No clue so far what this line does
  register_interrupt(button_isr, AVR32_PIOB_IRQ/32, AVR32_PIOB_IRQ % 32, BUTTONS_INT_LEVEL);
  piob->per = 0xe0; //Switches 7-5 active
  piob->puer = 0xe0;
  piob->ier = 0xe0;
  //Disable the rest of the switches
  piob->idr = 0x1f;
  button_isr();
}

void initLeds(void){
  //Enable all LEDs on PIOB
  pioc->per = 0xfF; //0xff == all LEDs
  pioc->oer = 0xff;
  pioc->sodr = 0x80;
  pioc->codr = 0x7f;
}

void initAudio(void){
  register_interrupt(abdac_isr, AVR32_ABDAC_IRQ/32, AVR32_ABDAC_IRQ % 32, ABDAC_INT_LEVEL);
  piob->PDR.p20 = 1;
  piob->PDR.p21 = 1;
  piob->ASR.p20 = 1;
  piob->ASR.p21 = 1;
  abdac_isr();
  abdac->CR.en = 1;
  abdac->IER.tx_ready = 1;
}

void button_isr(void){
  piob->isr;
  //Implementer debouncing...
  //Sjekk hvilken knapp som er trykket
  pioc->sodr = 0xff;
}

void abdac_isr(void){

}
