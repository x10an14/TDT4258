/*****************************************************************************
 *
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "sys/interrupts.h"
#include "oeving2.h"
#include "listsAndConstants.h"

volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;
volatile avr32_pm_t *pm = &AVR32_PM;
volatile avr32_abdac_t *abdac = &AVR32_ABDAC;

//buttonState variable
short static volatile newButtonState;

//All below are global, CAPS are
int current_repetition = 0;
int tone_position = 0;
int wave_position = 0;
int toneCntr = 0;
int volatile cntr = 0;
short *playListPtr = NULL;
int *ratePtr = NULL;

sample *flaaklypa, *flaa1, *flaa2, *flaa3, *flaa4, *playList;
sampleCollection *flaaklyp;

int main (int argc, char *argv[]){
  //Allocate space on heap for pointers
  flaa1 = (sample*) malloc(sizeof(sample));
  flaa2 = (sample*) malloc(sizeof(sample));
  flaa3 = (sample*) malloc(sizeof(sample));
  flaa4 = (sample*) malloc(sizeof(sample));
  //Declare variable for above allocated short-size-members
  flaa1->size = 8;
  flaa2->size = 12;
  flaa3->size = 8;
  flaa4->size = 15;
  //Initialize and declare variable for above allocated short-list-members
  flaa1->list = FLAA1;
  flaa2->list = FLAA2;
  flaa3->list = FLAA3;
  flaa4->list = FLAA4;
  //Repeat of above, but for timeList
  flaa1->timeList = TIME1;
  flaa2->timeList = TIME2;
  flaa3->timeList = TIME3;
  flaa4->timeList = TIME4;

  //Repeat of all above, except that pointer is a sampleCollection* pointer
  flaaklyp = (sampleCollection*) malloc(sizeof(sampleCollection));
  flaaklyp->size = 10;
  flaaklyp->list = (sample**) malloc(flaaklyp->size*sizeof(sample*));
  //The below line declares the list member of the sampleCollection pointer to be the addresses of the above sample pointers
  //for-loop cntr
  int i;
  for (i = 0; i < 10; i++){
    if(i == 0 || i == 2 || i == 8 || i == 6){
      flaaklyp->list[i] = flaa1;
    } else if(i == 1 || i == 7){
      flaaklyp->list[i] = flaa2;
    } else if(i == 3 || i == 9){
      flaaklyp->list[i] = flaa3;
    } else{
      flaaklyp->list[i] = flaa4;
    }
  }

  //Count to see how much space is needed
  //cntr for how much space we need
  int memCntr = 0;
  //cntr-list with how many times each tone is played
  for(i = 0; i < flaaklyp->size; i++){
    //Temporary variable for readability
    sample *small = flaaklyp->list[i];
    //for-loop cntr
    int j;
    for(j = 0; j < small->size; j++){
      //temp variable with how many times each tone is played
      short size = (short) getPeriodAmount(small->timeList[j], small->list[j],2)*2;
      //Self-explanatory
      memCntr += size;
      //If tonevalue changes, or we've reached the end of a playlist(sample)
      if(small->list[j-1] != small->list[j] ||
        j+1 == small->size){
        memCntr += 4; //Silence
      }
    }
  }

  //Assigning space
  flaaklypa = (sample*) malloc(sizeof(sample*));
  flaaklypa->size = memCntr;
  flaaklypa->list = (short*) calloc((short) 0, memCntr*sizeof(short)); //Total size of tune

  //Assigning(/Combining) values to final list (flaaklypa->list)
  cntr = 0;
  for(i = 0; i < flaaklyp->size; i++){
    sample *small = flaaklyp->list[i];
    int j;
    for(j = 0; j < small->size; j++){
      short size = (short) getPeriodAmount(small->timeList[j], small->list[j], 2)*2;
      addFrequency(small->timeList[j], small->list[j], flaaklypa->list, cntr);
      cntr += size;
      if(small->list[j-1] != small->list[j] ||
        j+1 == small->size){
        addZeroes(4, flaaklypa->list, cntr);
        cntr += 4;
      }
    }
  }

  //The rate (amount of times we play each element) is already set with the function addFrequency. So no need to use it on this sample
  flaaklypa->rateMax = 0;

  initHardware();

  while(1);
  return 0;
}

//Fun
int getPeriodAmount(int timeDiv, short tone, int waveFormSize){
  return (int) (49152*(1/(timeDiv*waveFormSize*tone)));
  // return (int) (486875*(1/(timeDiv*waveFormSize*tone)));
}

/*Function to add the time a tone will be played to a list, given a tone, length (div), and list*/
void addFrequency(int timeDiv, short tone, short *list, int start){
  //First get the amount of periods each tone has to be played to get the correct pitch, but multiply result with 2 so that below for-loop will set amplitude values correctly
  int periods = getPeriodAmount(timeDiv, tone, 2)*2;
  int i;
  for(i = start; i < periods + start; i += 2){
    list[i] = -1;
    list[++i] = 1;
  }
}

/*Function to add 0 an amount of times to a list*/
void addZeroes(int amount, short *list, int start){
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
  //Setting the below switch-values to variable active
  short active = SW7+SW6+SW5+SW4+SW3;
  piob->per = active; //Activating switches in variable active
  piob->puer = active; //Activating switches in variable active
  piob->ier = active; //Activating interrupt for switches in variable active
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
    playListPtr = sawToothWave;
    *ratePtr = SAWRATE;
  } else if(newButtonState == SW6){//Switch06
    playListPtr = triangleWave;
    *ratePtr = TRIANGLERATE;
  } else if(newButtonState == SW5){//Switch05
    playListPtr = squareWave;
    *ratePtr = SQUARERATE;
  } else if(newButtonState == 0x10){//Switch04
    playList = flaaklypa;
  } else if(newButtonState == 0x8){//Switch03
    //Play toneScale
  } /*else if(newButtonState == 0x4){//Switch02

  } else if(newButtonState == 0x2){//Switch01

  } else if(newButtonState == 0x1){//Switch0

  }*/
}

//This function needs to be rewritten so that all it takes is a sample, checks whether it should use rateCntr, or if function addFrequency has been used, and then plays the sample with the use of the cntrs in the struct alone (to get rid of all these global variables.)
void abdac_isr(void){
  short output = 0;
  /*General sample-list play without rate*/
  if(playList->rateMax == 0){
    /* code */
  }

  if(playListPtr == flaaklypa->list){
    output = playListPtr[toneCntr];
    //toneCntr iterates over the WHOLE tune
    ++toneCntr;
    //Below I check to see if we're at the end of the file
    if(toneCntr == cntr){
      toneCntr = 0;
      tone_position = 0;
    }
  } else if(playListPtr != NULL &&
    playListPtr != flaaklypa->list){
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
