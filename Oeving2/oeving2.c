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

#define ARRAYSIZE 17
#define SW7 0x80
#define SW6 0x40
#define SW5 0x20
#define SW4 0x10
#define SW3 0x8

#define SAWRATE 20
#define SQUARERATE 15
#define TRIANGLERATE 18

volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;
volatile avr32_pm_t *pm = &AVR32_PM;
volatile avr32_abdac_t *abdac = &AVR32_ABDAC;

//int static FREQDIV = 20; // tonehøye = clk/FREQDIV
int static maxSteps = 440;
short static volatile newButtonState;

//short sinusWave[ARRAYSIZE] = {0, 100, 0, -100, 0};

int current_repetition = 0;
int wave_position = 0;
int *playListPtr = NULL;
int *ratePtr = NULL;
int sawTooth[] = {-1, -(7/8), -0.75, -(5/8), -0.50, -(3/8), -0.25, -(1/8), 0, (1/8), 0.25, (3/8), 0.50, (5/8), 0.75, (7/8), 1};
int triangleWave[] = {0, 0.25, 0.50, 0.75, 1, 0.75, 0.50, 0.25, 0, -0.25, -0.50, -0.75, -1, -0.75, -0.50, -0.25, 0};
int squareWave[] = {-1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

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
}

void initLeds(void){
  //Enable all LEDs on PIOB
  pioc->per = 0xfF; //0xff == all LEDs
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
  abdac->CR.en = 1;
  abdac->IER.tx_ready = 1;
}

void button_isr(void){
  newButtonState = ~piob->pdsr;//Read which switch was pushed
  newButtonState &= piob->isr;//To read interrupt vector, enabling next interrupt
  pioc->codr = 0xff;//Turn off all the lights
  pioc->sodr = newButtonState; //Turn on the light corresponding to the button pushed

  if(newButtonState == SW7){//Switch07
    playListPtr = sawTooth;
    *ratePtr = SAWRATE;
  } else if(newButtonState == SW6){//Switch06
    playListPtr = triangleWave;
    *ratePtr = TRIANGLERATE;
  } else if(newButtonState == SW5){//Switch05
    playListPtr = squareWave;
    *ratePtr = SQUARERATE;
  }/* else if(newButtonState == 0x10){//Switch04

  } else if(newButtonState == 0x8){//Switch03

  } else if(newButtonState == 0x4){//Switch02

  } else if(newButtonState == 0x2){//Switch01

  } else if(newButtonState == 0x1){//Switch0

  }*/
}

void abdac_isr(void){
  short output = 0;
  if (playListPtr != NULL){
    output = playListPtr[wave_position];
    current_repetition++;
    if (current_repetition >= *ratePtr) {
      wave_position++;
      current_repetition = 0;
      if (wave_position >= ARRAYSIZE) {
        wave_position = 0;
        //playListPtr = NULL;
      }
    }
  }
  abdac->SDR.channel0 = output*SHRT_MAX*0.05;
  abdac->SDR.channel1 = output*SHRT_MAX*0.05;
}
