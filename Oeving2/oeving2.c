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

volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;
volatile avr32_pm_t *pm = &AVR32_PM;
volatile avr32_abdac_t *abdac = &AVR32_ABDAC;

int static divide = 100;
int static amplitude = -500;
int static frequency = 0;
int static maxSteps = 440;
int static i;

short static waveform_resolution[1024];

int static waveShapesSize = 2;
short sawTooth[waveShapesSize]; //Unused
short squareWave[waveShapesSize];
short triangleWave[waveShapesSize]; //Unused

//short sinusWave[waveShapesSize] = {0, 100, 0, -100,, 0};

void playSawTooth(void){
  for (i = 0; i < waveShapesSize; i++){
    abdac->SDR.channel0 = sawTooth[i];
    abdac->SDR.channel1 = sawTooth[i];
  }
}

void playSquareWave(void){
  for (i = 0; i < waveShapesSize; i++){
    abdac->SDR.channel0 = squareWave[i];
    abdac->SDR.channel1 = squareWave[i];
  }
}

void playTriangleWave(void){
  for (i = 0; i < waveShapesSize; i++){
    abdac->SDR.channel0 = triangleWave[i];
    abdac->SDR.channel1 = triangleWave[i];
  }
}

int main (int argc, char *argv[]){
//  sawTooth = {-100, -75, -50, -25, 0, 25, 50, 75, 100};
//  short templist[9] = {-100, -100, -100, -100, 100, 100, 100, 100, 100};
//  squareWave = templist;
//  short templist[9]  = {0, 50, 100, 50, 0, -50, -100, -50, 0};
//  triangleWave = templist;
  squareWave[0] = -1; squareWave[1] = 1;

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
  abdac_isr();
  abdac->CR.en = 1;
  abdac->IER.tx_ready = 1;
}

void button_isr(void){
  piob->isr;
  //Implementer debouncing...
  //Sjekk hvilken knapp som er trykket
  pioc->codr = 0xff;
  int temp = piob->pdsr;
  pioc->sodr = ~temp;
}

void abdac_isr(void){
/*  for (i = 0; i < maxSteps; i++){
    playSawTooth();
  }
  for (i = 0; i < maxSteps; i++){
    playTriangleWave();
  }
*/
  for (i = 0; i < maxSteps; i++){
    playSquareWave();
  }
}
