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

//int static FREQDIV = 20; // tonehøye = clk/FREQDIV
int static maxSteps = 188;
short static volatile newButtonState;

//short sinusWave[ARRAYSIZE] = {0, 100, 0, -100, 0};

int current_repetition = 0;
int tone_position = 0;
int wave_position = 0;
int toneCntr  = 0;
int *playListPtr = NULL;
int *ratePtr = NULL;
int sawTooth[] = {-1, -(7/8), -0.75, -(5/8), -0.50, -(3/8), -0.25, -(1/8), 0, (1/8), 0.25, (3/8), 0.50, (5/8), 0.75, (7/8), 1};
int triangleWave[] = {0, 0.25, 0.50, 0.75, 1, 0.75, 0.50, 0.25, 0, -0.25, -0.50, -0.75, -1, -0.75, -0.50, -0.25, 0};
int squareWave[SQUARESIZE] = {-1, 1};
int toneScale[TONESIZE] = {C4,D4,E4,F4,G4,A4,B4};
smallSample *FLAAKLYPA;

int main (int argc, char *argv[]){
  flaa1->size = 8;
  short foo1[] = {E4,A4,B4,C5,B4,A4,G4,E4};
  short foo2[] = {4,4,4,5,4,4,3,4};
  flaa1->list = foo1;
  flaa1->timeList = foo2;

  flaa2->size = 12;
  short foo3[] = {C4,D4,E4,F4,E4,D4,C4,D4,E4,D4,C4,B3};
  short foo4[] = {4,4,4,4,4,4,4,4,4,4,4,2};
  flaa2->list = foo3;
  flaa2->timeList = foo4;

  flaa3->size = 8;
  short foo5[] = {C4,D4,E4,D4,C4,B3,A3,A3};
  short foo6[] = {4,4,2,4,4,2,2,2};
  flaa3->list = foo5;
  flaa3->timeList = foo6;

  flaa4->size = 15;
  short foo7[] = {A3,A4,G4,F4,E4,C4,A3,B3,C4,D4,E4,F4,E4,D4,C4};
  short foo8[] = {2,2,4,4,4,4,2,4,4,2,4,4,4,4,4};
  flaa4->list = foo7;
  flaa4->timeList = foo8;

  flaaklypa->size = 10;
  smallSample foo9[] = {flaa1,flaa2,flaa1,flaa3,
    flaa4,flaa4,flaa1,flaa2,flaa1,flaa3};
  flaaklypa->list = foo9;

  //Count to see how much space is needed
  int i;
  int memCntr = 0;
  for(i = 0; i < flaaklypa->size; i++){
    int j;
    for(int j = 0; j < flaaklypa->list[i]->size; j++){
      memCntr += getFrequencySize(flaaklypa->list[i]->freqList[j], flaaklypa->list[i]->list[j],2) +2; //+2 to add when waveform shifts
      if(flaaklypa->list[i]->list[j-1] == flaaklypa->list[i]->list[j] ||
        j+1 == flaaklypa->list[i]->size){
        memCntr += 5; //Silence
      }
    }
  }

  //Assign space
  FLAAKLYPA = (smallSample*) malloc(sizeof(smallSample*));
  FLAAKLYPA->size = memCntr;
  FLAAKLYPA->list = (short) calloc(memCntr*sizeof(short)); //Total size of tune

  //Assign values to final list (FLAAKLYPA->list)
  int cntr = 0;
  for(i = 0; i < flaaklypa->size; i++){
    int j;
    for(j = 0; j < flaaklypa->list[i]->size; j++){
      smallSample *small = *flaaklypa->list[i];
      int size = getFrequencySize(small->freqList[j], small->list[j], 2);
      addFrequency(small->freqList[j],small->list[j], FLAAKLYPA->list, cntr);
      cntr += size;
      if(small->list[j-1] == small->list[j] ||
        j+1 == small->size){
        void addZeroes(5, FLAAKLYPA->list, cntr);
        cntr += 5;
      }
    }
  }

  *flaaklypa = *FLAAKLYPA;
  initHardware();

  while(1);
  return 0;
}

int getFrequencySize(int timeDiv, short tone, int waveFormSize){
  return (int) (46875*(1/(secDiv*waveFormSize*tone)));
}

/*Function to add the time a tone will be played to a list, given a tone, length (div), and list*/
void addFrequency(int timeDiv, short tone, short **list, int start){
  int cntr = 46875*(1/(timeDiv*tone));
  int i;
  for(i = start; i < cntr + start; i++){
    list[i] = tone;
  }
}

void addZeroes(int amount, short **list, int start){
  int i;
  for(i = start; i < amount + start; i++){
    list[i] = 0;
  }
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
  register_interrupt(button_isr, AVR32_PIOB_IRQ/32, AVR32_PIOB_IRQ % 32, BUTTONS_INT_LEVEL);
  short active = SW7+SW6+SW5+SW4;
  piob->per = active; //Switches 7-4 active
  piob->puer = active;
  piob->ier = active;
  //Disable the rest of the switches
  piob->idr = ~active;
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
  newButtonState = ~piob->pdsr;//Read which switch was pushed (invert)
  newButtonState &= piob->isr;//Read interrupt vector, and with pushed button-value, and enabling next interrupt
  if(newButtonState > 0){
    pioc->codr = 0xff;//Turn off all the lights
  }
  pioc->sodr = newButtonState; //Turn on the light corresponding to the button pushed

  if(newButtonState == SW7){//Switch07
    playListPtr = sawTooth;
    *ratePtr = SAWRATE;
  } else if(newButtonState == SW6){//Switch06
    playListPtr = triangleWave;
    *ratePtr = TRIANGLERATE;
  } else if(newButtonState == SW5){//Switch05
    playListPtr = squareWave;
    // *ratePtr = SQUARERATE;
    *ratePtr = toneScale[tone_position];
  } else if(newButtonState == 0x10){//Switch04
    playListPtr = FLAAKLYPA->list;
    *ratePtr = 2;
  }/* else if(newButtonState == 0x8){//Switch03

  } else if(newButtonState == 0x4){//Switch02

  } else if(newButtonState == 0x2){//Switch01

  } else if(newButtonState == 0x1){//Switch0

  }*/
}

void abdac_isr(void){
  short output = 0;
  if(playListPtr == FLAAKLYPA){

  } else if(playListPtr != NULL){
    output = playListPtr[wave_position];
    toneCntr++;
    if(toneCntr >= *ratePtr){
      toneCntr = 0;
      ++wave_position;
      *ratePtr = toneScale[tone_position];
      if(wave_position >= 9){
        ++tone_position;
        wave_position = 0;
        if(tone_position >= 7){
          tone_position = 0;
        }
      }
     /* current_repetition++;
      if (current_repetition >= *ratePtr) {
        wave_position++;
        current_repetition = 0;
        if (wave_position >= ARRAYSIZE) {
          wave_position = 0;
          //playListPtr = NULL; //Uncomment this to make it stop endless repeat
        }
      }*/
    }
  }
  abdac->SDR.channel0 = output*SHRT_MAX*0.4;
  abdac->SDR.channel1 = output*SHRT_MAX*0.4;
}
