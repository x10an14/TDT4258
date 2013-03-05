/*****************************************************************************
 *
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include "oeving2.h"
#include "sys/interrupts.h"
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define ARRAYSIZE 9
#define SQUARESIZE 8

volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;
volatile avr32_pm_t *pm = &AVR32_PM;
volatile avr32_abdac_t *abdac = &AVR32_ABDAC;

int static divide = 100;
int static amplitude = -500;
int static frequency = 0;
int static maxSteps = 440;
int static button_PDSR;

short sawTooth[ARRAYSIZE] = {-10, (short)-0.75*SHRT_MIN, -50, -25, 0, 25, 50, 75, 100};;//Unused
short squareWave[SQUARESIZE] = {-100, -100, -100, -100, 100, 100, 100, 100};;
short triangleWave[ARRAYSIZE] = {0, 50, 100, 50, 0, -50, -100, -50, 0};; //Unused

//short sinusWave[ARRAYSIZE] = {0, 100, 0, -100, 0};

void playSawTooth(void){
  for (i = 0; i < ARRAYSIZE; i++){
    abdac->SDR.channel0 = (short)sawTooth[i];
    abdac->SDR.channel1 = (short)sawTooth[i];
  }
}

void playSquareWave(void){
  for (i = 0; i < SQUARESIZE; i++){
    abdac->SDR.channel0 = (short)squareWave[i];
    abdac->SDR.channel1 = (short)squareWave[i];
  }
}

void playTriangleWave(void){
  for (i = 0; i < ARRAYSIZE; i++){
    abdac->SDR.channel0 = triangleWave[i];
    abdac->SDR.channel1 = triangleWave[i];
  }
}

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
}

void initAudio(void){
  //Oppsett av PowerManager for klokke og abdac...
  pm->GCCTRL[6].oscsel = 0;
  pm->GCCTRL[6].diven = 0;
  pm->GCCTRL[6].pllsel = 0;
  pm->GCCTRL[6].cen = 1;
  register_interrupt(abdac_isr, AVR32_ABDAC_IRQ/32, AVR32_ABDAC_IRQ % 32, ABDAC_INT_LEVEL);
  piob->PDR.p20 = 1;
  piob->PDR.p21 = 1;
  piob->ASR.p20 = 1;
  piob->ASR.p21 = 1;
  abdac->CR.en = 1;
  abdac->IER.tx_ready = 1;
}

void button_isr(void){
  piob->isr;
  button_PDSR = piob->pdsr;
  //Implementer debouncing...
  pioc->codr = 0xff;//Turn off all the lights
  int debounce = 0xfeff;
  do{
    debounce--;
  }while(debounce > -1);
  //Sjekk hvilken knapp som er trykket
  if(button_PDSR != piob->pdsr){
    pioc->sodr = 0x0;//If debounce check didn't work
    //Then turn on all the lights
    return;
  }
  pioc->sodr = ~button_PDSR;
}

void abdac_isr(void){
  //If-else to check what switch (buttons) are pressed
  if (button_PDSR == 0x0){//No switches
    return;
  } else if(button_PDSR == ~0x80){//Switch07
    for (i = 0; i < maxSteps; i++){

      // playSawTooth();
    }
  } else if(button_PDSR == ~0x40){//Switch06
    for (i = 0; i < maxSteps; i++){
      playTriangleWave();
    }
  } else if(button_PDSR == ~0x20){//Switch05
    for (i = 0; i < maxSteps; i++){
      playSquareWave();
    }
  }/* else if(button_PDSR == 0x10){//Switch04

  } else if(button_PDSR == 0x8){//Switch03

  } else if(button_PDSR == 0x4){//Switch02

  } else if(button_PDSR == 0x2){//Switch01

  } else if(button_PDSR == 0x1){//Switch0

  }*/
}
