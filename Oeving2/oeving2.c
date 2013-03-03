/*****************************************************************************
 *
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include "oeving2.h"

volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;
volatile avr32_pm_t *pm = &AVR32_PM;
volatile avr32_abdac_t *abdac = &AVR32_ABDAC;


int main (int argc, char *argv[]) {
  initHardware();

  while(1);
  return 0;
}

/* funksjon for å initialisere maskinvaren, må utvides */
void initHardware (void) {
  initIntc();
  initLeds();
  initButtons();
  initAudio();
}

/* Flytter denne metoden ut i en egen C fil. Legger og til tilhørende metoder der.
void initIntc(void) {
  set_interrupts_base((void *)AVR32_INTC_ADDRESS);
  init_interrupts();
}*/

void initButtons(void) {
  //No clue so far what this line does
  register_interrupt( button_isr, AVR32_PIOB_IRQ/32, AVR32_PIOB_IRQ % 32, BUTTONS_INT_LEVEL);
  piob->per = 0xe0; //Switches 7-5 active
  piob->puer = 0xe0;
  piob->ier = 0xe0;
  //Disable the rest of the switches
  piob->idr = 0x1f;
}

void initLeds(void) {
  //Enable all LEDs on PIOB
  pioc->per = 0xfF; //0xff == all LEDs
  pioc->oer = 0xff;
}

void initAudio(void) {
  register_interrupt( abdac_isr, AVR32_ABDAC_IRQ/32, AVR32_ABDAC_IRQ % 32, ABDAC_INT_LEVEL);
  /* (...) */
}

void button_isr(void) {

}

void abdac_isr(void) {

}
