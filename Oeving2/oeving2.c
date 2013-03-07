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
#define FREQDIV 20    // tonehøye = clk/FREQDIV
#define SW7 0x80
#define SW6 0x40
#define SW5 0x20
#define SW4 0x10
#define SW3 0x8

volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;
volatile avr32_pm_t *pm = &AVR32_PM;
volatile avr32_abdac_t *abdac = &AVR32_ABDAC;

int static frequencyDivide = 100;
int static maxSteps = 440;
short static volatile button_PDSR;
int static i;

short sawTooth[ARRAYSIZE] = {-1, -0.75, -0.50, -0.25, 0, 0.25, 0.50, 0.75, 1};
short squareWave[SQUARESIZE] = {-1, -1, -1, -1, 1, 1, 1, 1};
short triangleWave[ARRAYSIZE] = {0, 0.50, 1, 0.50, 0, -0.50, -1, -0.50, 0};

//short sinusWave[ARRAYSIZE] = {0, 100, 0, -100, 0};

void playSawTooth(void){
  for (i = 0; i < (ARRAYSIZE*FREQDIV); i++){
    int j;
    j =(int) floor((float)i/FREQDIV); 
    abdac->SDR.channel0 = (short)sawTooth[i]*SHRT_MAX*0.1;
    abdac->SDR.channel1 = (short)sawTooth[i]*SHRT_MAX*0.1;
  }
}

void playSquareWave(void){
  for (i = 0; i < (SQUARESIZE*FREQDIV); i++){
    int j;
    j =(int) floor((float)i/FREQDIV); 
    abdac->SDR.channel0 = (short)squareWave[i]*SHRT_MAX;
    abdac->SDR.channel1 = (short)squareWave[i]*SHRT_MAX;
  }
}

void playTriangleWave(void){
  for (i = 0; i < (ARRAYSIZE*FREQDIV); i++){
    int j;
    j =(int) floor((float)i/FREQDIV);  
    abdac->SDR.channel0 = (short)triangleWave[j]*SHRT_MAX*0.1;
    abdac->SDR.channel1 = (short)triangleWave[j]*SHRT_MAX*0.1;
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
}

void initLeds(void){
  //Enable all LEDs on PIOB
  pioc->per = 0xfF; //0xff == all LEDs
  pioc->oer = 0xff;
}

void initAudio(void){
  //Oppsett av PowerManager for klokke og abdac...
  pm->GCCTRL[6].oscsel = 0;
  pm->GCCTRL[6].diven = 1;
  pm->GCCTRL[6].div = SHRT_MAX/2;
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
  button_PDSR = piob->isr;//To read interrupt vector, enabling next interrupt
  button_PDSR = piob->pdsr;//Read which switch was pushed
  //Implementer debouncing...
  pioc->codr = 0xff;//Turn off all the lights
  int debounce = 0xffff;
  do{
    debounce--;
  }while(debounce > -1);
  /*Checking which button is pushed by and'ing them after the debouncing.*/
  button_PDSR ^= piob->pdsr;
  pioc->sodr = ~button_PDSR;


  if (button_PDSR == SW7){//No switches
    return;
  } else if(button_PDSR == SW6){//Switch07
    for (i = 0; i < maxSteps; i++){
      playSawTooth();
    }
  } else if(button_PDSR == SW5){//Switch06
    for (i = 0; i < maxSteps; i++){
      playTriangleWave();
    }
  } else if(button_PDSR == SW4){//Switch05
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

void abdac_isr(void){
  //If-else to check what switch (buttons) are pressed
//  playSawTooth();
//  playSquareWave();
  playTriangleWave();
}
