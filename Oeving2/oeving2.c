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

//All below are global
short *currentSamplePtr = NULL;
int *ratePtr = NULL;
sample *flaaklypaSample, *flaa1, *flaa2, *flaa3, *flaa4,
       *squareSample, *sawSample, *triangleSample, *scaleSample, *sineSample, *currentSample;
sampleCollection *flaaklyp;

int main (int argc, char *argv[]){
  // Creating of sinus wave list 102 steps
  short *sineSampleList = (short*) malloc(102*sizeof(short));;
  //for-loop cntr
  int i;
  for (i=0; i < 102; i++){
    sineSampleList[i] = sin(M_PI/102*i)*SHRT_MAX;
  }

  //Allocate space on heap for pointers
  flaa1 = (sample*) malloc(sizeof(sample));
  flaa2 = (sample*) malloc(sizeof(sample));
  flaa3 = (sample*) malloc(sizeof(sample));
  flaa4 = (sample*) malloc(sizeof(sample));
  sawSample = (sample*) malloc(sizeof(sample));
  sineSample = (sample*) malloc(sizeof(sample));
  scaleSample = (sample*) malloc(sizeof(sample));
  squareSample = (sample*) malloc(sizeof(sample));
  triangleSample = (sample*) malloc(sizeof(sample));

  //Declare variable for above allocated short-size-members
  flaa1->size = 8;
  flaa2->size = 12;
  flaa3->size = 8;
  flaa4->size = 15;
  sawSample->size = 17;
  sineSample->size = 102;  // 17 * 6 = 102
  scaleSample->size = 8;
  squareSample->size = 17;
  triangleSample->size = 17;

  //Initialize and declare variable for above allocated short-list-members
  flaa1->list = FLAA1;
  flaa2->list = FLAA2;
  flaa3->list = FLAA3;
  flaa4->list = FLAA4;
  sawSample->list = SAW;
  sineSample->list = sineSampleList;
  scaleSample->list = SCALE;
  squareSample->list = SQUARE;
  triangleSample->list = TRIANGLE;

  //Repeat of above, but for strokeList
  flaa1->strokeList = FLAASTROKE1;
  flaa2->strokeList = FLAASTROKE2;
  flaa3->strokeList = FLAASTROKE3;
  flaa4->strokeList = FLAASTROKE4;
  scaleSample->strokeList = SCALESTROKE;

  //Repeat of all above, except that pointer is a sampleCollection* pointer
  flaaklyp = (sampleCollection*) malloc(sizeof(sampleCollection));
  flaaklyp->size = 10;
  flaaklyp->list = (sample**) malloc(flaaklyp->size*sizeof(sample*));

  /*The below for-loop declares the list member of the sampleCollection pointer to be the addresses of the above sample pointers
  (Flaaklypa variants only!)*/
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

  //Count to see how much space is needed for flaaklypaSample->list/size
  //cntr for how much space needed
  int memCntr = 0;
  for(i = 0; i < flaaklyp->size; i++){
    //Temporary variable for readability
    sample *small = flaaklyp->list[i];
    //Inner for-loop cntr
    int j, size;
    for(j = 0; j < small->size; j++){
      /*size == temp variable with how much space is needed for each tone in the final list*/
      size = (int) (ABDAC_SAMPLERATE/small->list[j]);
      //Self-explanatory (if you've read the above comments)
      memCntr += size;
      /*If tonevalue stays the same, or we've reached the end of a playlist(sample), we might want just a small, teeny-tiny break so that those with the most sensitive ears can differ.*/
      if(small->list[j-1] == small->list[j] ||
        j+1 == small->size){
        memCntr += 4; //Silence
      }
    }
  }

  //Assigning space
  flaaklypaSample = (sample*) malloc(sizeof(sample*));
  flaaklypaSample->size = memCntr;
  flaaklypaSample->list = (short*) calloc((short) 0, memCntr*sizeof(short));

  //Assigning(/Combining) values to final list (flaaklypaSample->list)
  int cntr = 0;
  for(i = 0; i < flaaklyp->size; i++){
    sample *small = flaaklyp->list[i];
    int j, size;
    for(j = 0; j < small->size; j++){
      size = (int)(ABDAC_SAMPLERATE/small->strokeList[j]);
      addFrequency(small->strokeList[j], small->list[j], flaaklypaSample->list, cntr);
      cntr += size;
/*      if(small->list[j-1] == small->list[j] ||
        j+1 == small->size){
        addZeroes(4, flaaklypaSample->list, cntr);
        cntr += 4;
      }*/
    }
  }
   
  // SAME METHOD BUT FOR SCALE
  //Count to see how much space is needed
  //cntr for how much space we need
  //cntr-list with how many times each tone is played
  memCntr = 0;
  int size;
  for(i = 0; i < scaleSample->size; i++){
    //temp variable with how many times each tone is played
    size = (int) (ABDAC_SAMPLERATE/SCALESTROKE[i]);
    //Self-explanatory
    memCntr += size;
    //If tonevalue changes, or we've reached the end of a playlist(sample)
    if(i+1 == scaleSample->size){
      memCntr += 4; //Silence
    }
  }

  //Assigning space
  scaleSample = (sample*) malloc(sizeof(sample*));
  scaleSample->size = memCntr;
  scaleSample->list = (short*) calloc((short) 0, memCntr*sizeof(short)); //Total size of tune

  //Assigning(/Combining) values to final list (flaaklypaSample->list)
  cntr = 0;
  for(i = 0; i < scaleSample->size; i++){
    size = (int) (ABDAC_SAMPLERATE/SCALESTROKE[i]);
    addFrequency(SCALESTROKE[i], SCALE[i], scaleSample->list, cntr);
    cntr += size;
    if (i+1 == scaleSample->size){
      addZeroes(4, scaleSample->list, cntr);
      cntr += 4;
    }
  }
  //The rate (amount of times we play each element) is already set with the function addFrequency. So no need to use it on this sample
  flaaklypaSample->usingStrokeList = 1;
  scaleSample->usingStrokeList = 1;

  sawSample->usingStrokeList = 0;
  sineSample->usingStrokeList = 0;
  squareSample->usingStrokeList = 0;
  triangleSample->usingStrokeList = 0;

  sawSample->rateMax = SAWRATE;
  sineSample->rateMax = SINERATE;
  squareSample->rateMax = SQUARERATE;
  triangleSample->rateMax = TRIANGLERATE;

  sawSample->rateCntr = 0;
  sineSample->rateCntr = 0;
  squareSample->rateCntr = 0;
  triangleSample->rateCntr = 0;

  initHardware();
//  pioc->sodr = 0xff;
  
  while(1);
  return 0;
}

/*Function to add the time a tone will be played to a list, given a tone, length (stroke), and list*/
void addFrequency(short stroke, short tone, short *list, int start){
  int periods = (int) (tone/stroke);
  int periodSize = (int) ABDAC_SAMPLERATE/tone;
  int halfPeriod = periodSize/2;
  int i;
  for(i = start; i < periods + start; i++){
    int j;
    for (j = 0; j < halfPeriod; j++){
      list[j] = -SHRT_MAX;
    }
    for (j = halfPeriod; j < periodSize; j++){
      list[++j] = SHRT_MAX;
    }
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
  short active = SW7+SW6+SW5+SW4+SW3+SW2+SW0;
  piob->per = active; //Activating switches in variable active
  piob->puer = active; //Activating switches in variable active
  piob->ier = active; //Activating interrupt for switches in variable active
  //Disable the rest of the switches
  piob->idr = ~active;
}

void initLeds(void){
  //Enable all LEDs on PIOB
  pioc->per = 0xff-SW1; //0xff == all LEDs
  pioc->oer = 0xff-SW1;
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
    currentSample = sawSample;
  } else if(newButtonState == SW6){//Switch06
    currentSample = triangleSample;
  } else if(newButtonState == SW5){//Switch05
    currentSample = squareSample;
  } else if(newButtonState == SW4){//Switch04
    currentSample = flaaklypaSample;
  } else if(newButtonState == SW3){//Switch03
    currentSample = scaleSample;
  } else if(newButtonState == SW2){//Switch02
    currentSample = sineSample;
  }/* else if(newButtonState == SW1){//Switch01

  }*/ else if(newButtonState == SW0){//Switch0
    /*SILENCE WILL FALL...*/
    currentSample = NULL;
    // pioc->codr = 0xff; //Unsure if this works as intended
  }
}

//This function should play the next element in a pre-computed list
void abdac_isr(void){
  short output = 0;

  if(currentSample != NULL){ /*Check to see if the pointer is actually pointing at a struct (General sample-list play without rate)*/

    if(currentSample->usingStrokeList){ /*Check to see if we've already calculated how long to 'dwell' on each element in member list*/
      output = currentSample->list[currentSample->playCntr];
      currentSample->playCntr++;

      if (currentSample->playCntr >= currentSample->size){ /*If we've reached the end of the list, reset playCntr to 0*/
        currentSample->playCntr = 0;
      }
    } else{ /*If we are NOT using timelist, and we're using rateCntr to 'dwell' on each element a rateMax amount of times*/
      output = currentSample->list[currentSample->playCntr];
      currentSample->rateCntr++;

      if (currentSample->rateCntr >= currentSample->rateMax){ /*If we've dwelled the given amount of times, reset counter and start playing next tone*/
        currentSample->playCntr++;
        currentSample->rateCntr = 0;

        if (currentSample->playCntr >= currentSample->size){ /*If we've played through the whole list/tune, reset counter to start again*/
          currentSample->playCntr = 0;
        }
      }
    }
  }
  abdac->SDR.channel0 = output*0.5;
  abdac->SDR.channel1 = output*0.5;
}
