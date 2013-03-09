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
short sawTooth[] = {-1, -(7/8), -0.75, -(5/8), -0.50, -(3/8), -0.25, -(1/8), 0, (1/8), 0.25, (3/8), 0.50, (5/8), 0.75, (7/8), 1};
short triangleWave[] = {0, 0.25, 0.50, 0.75, 1, 0.75, 0.50, 0.25, 0, -0.25, -0.50, -0.75, -1, -0.75, -0.50, -0.25, 0};
short squareWave[SQUARESIZE] = {-1, 1};
short toneScale[TONESIZE] = {C4,D4,E4,F4,G4,A4,B4};
short flaaTone[102];

smallSample flaa1, flaa2, flaa3, flaa3, flaa4;
sample flaaklyp;

flaa1.size = 8;
flaa1.list[8] = {E4,A4,B4,C5,B4,A4,G4,E4};
flaa1.timelist = {4,4,4,5,4,4,3,4};

flaa2.size = 12;
flaa2.list = {C4,D4,E4,F4,E4,D4,C4,D4,E4,D4,C4,B3};
flaa2.timelist = {4,4,4,4,4,4,4,4,4,4,4,2};

flaa3.size = 8;
flaa3.list = {C4,D4,E4,D4,C4,B3,A3,A3};
flaa3.timelist = {4,4,2,4,4,2,2,2};

flaa4.size = 15;
flaa4.list = {A3,A4,G4,F4,E4,C4,A3,B3,C4,D4,E4,F4,E4,D4,C4};
flaa4.timelist = {2,2,4,4,4,4,2,4,4,2,4,4,4,4,4};

flaaklyp.size = 10;
flaaklyp.list[10] = {&flaa1, &flaa2, &flaa1, &flaa3, &flaa4, &flaa4, &flaa1, &flaa2, &flaa1, &flaa3};

smallSample *flaaklypa;

int main (int argc, char *argv[]){
  //Repeat of above

  //Repeat of above, but here to collect them all into a sample instead of a smallSample
  flaaklyp.size = 10;
  smallSample *foo9[10];
  foo9[0] = &flaa1; foo9[2] = &flaa1; foo9[6] = &flaa1; foo9[8] = &flaa1;
  foo9[1] = &flaa2; foo9[7] = &flaa2;
  foo9[3] = &flaa3; foo9[9] = &flaa3;
  foo9[4] = &flaa4; foo9[5] = &flaa4;
  flaaklyp.list = foo9;
  //Count to see how much space is needed
  //for-loop cntr
  int i;
  //cntr for how much space we need
  int memCntr = 0;
  //cntr-list with how many times each tone is played
  for(i = 0; i < flaaklyp.size; i++){
    //for-loop cntr
    int j;
    for(j = 0; j < flaaklyp.list[i]->size; j++){
      //temp variable with how many times each tone is played
      short size = (short) getFrequencySize(flaaklyp.list[i]->timeList[j], flaaklyp.list[i]->list[j],2);
      //Self-explanatory
      memCntr += size;
      //Again, self explanatory
      flaaTone[cntr] = size;
      //If tonevalue changes, or we've reached the end of a playlist(sample)
      if(flaaklyp.list[i]->list[j-1] == flaaklyp.list[i]->list[j] ||
        j+1 == flaaklyp.list[i]->size){
        memCntr += 4; //Silence
        flaaTone[cntr] += 4;
      }
      //Dividing by 2 so that audio_isr cntrs to work in audio_isr
      flaaTone[cntr] /= 2;
      //increasing cntr to manipulate next element in flaaTone
      cntr += 1;
    }
  }

  //Assigning space
  flaaklypa = (smallSample*) malloc(sizeof(smallSample*));
  flaaklypa->size = memCntr;
  flaaklypa->list = (short*) calloc((short) 0, memCntr*sizeof(short)); //Total size of tune

  //Assign values to final list (flaaklypa->list)
  cntr = 0;
  for(i = 0; i < flaaklyp.size; i++){
    int j;
    for(j = 0; j < flaaklyp.list[i]->size; j++){
      smallSample *small = flaaklyp.list[i];
      short size = (short) getFrequencySize(small->timeList[j], small->list[j], 2);
      addFrequency(small->timeList[j], small->list[j], flaaklypa->list, cntr);
      cntr += size;
      if(small->list[j-1] == small->list[j] ||
        j+1 == small->size){
        addZeroes(4, flaaklypa->list, cntr);
        cntr += 4;
      }
    }
  }

  initHardware();

  while(1);
  return 0;
}

//Fun
int getFrequencySize(int timeDiv, short tone, int waveFormSize){
  return (int) (46875*(1/(timeDiv*waveFormSize*tone)));
}

/*Function to add the time a tone will be played to a list, given a tone, length (div), and list*/
void addFrequency(int timeDiv, short tone, short *list, int start){
  int freqCntr = 46875*(1/(timeDiv*tone));
  int i;
  for(i = start; i < freqCntr + start; i++){
    if(i < freqCntr/2){
      list[i] = -tone;
    }
    list[i] = tone;
  }
}

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
  short active = SW7+SW6+SW5+SW4;
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
    playListPtr = sawTooth;
    *ratePtr = SAWRATE;
  } else if(newButtonState == SW6){//Switch06
    playListPtr = triangleWave;
    *ratePtr = TRIANGLERATE;
  } else if(newButtonState == SW5){//Switch05
    playListPtr = squareWave;
    *ratePtr = SQUARERATE;
    *ratePtr = toneScale[tone_position];
  } else if(newButtonState == 0x10){//Switch04
    playListPtr = flaaklypa->list;
  }/* else if(newButtonState == 0x8){//Switch03

  } else if(newButtonState == 0x4){//Switch02

  } else if(newButtonState == 0x2){//Switch01

  } else if(newButtonState == 0x1){//Switch0

  }*/
}

void abdac_isr(void){
  short output = 0;
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
