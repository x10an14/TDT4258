#include "oeving2.h"


//buttonState variable
short volatile newButtonState;

void button_isr(void){
  newButtonState = ~piob->pdsr;//Read which switch was pushed (invert)
  newButtonState &= piob->isr;//Read interrupt vector, and with pushed button-value, and enabling next interrupt
  if(newButtonState > 0){
    pioc->codr = 0xff;//Turn off all the lights
  }
  pioc->sodr = newButtonState; //Turn on the light corresponding to the button pushed

  if(newButtonState == SW7){//Switch07
    setAbdacOnOff(1);
    currentSample = sawSample;
  } else if(newButtonState == SW6){//Switch06
    setAbdacOnOff(1);
    currentSample = triangleSample;
  } else if(newButtonState == SW5){//Switch05
    setAbdacOnOff(1);
    currentSample = squareSample;
  } else if(newButtonState == SW4){//Switch04
    setAbdacOnOff(1);
    currentSample = flaaklypaSample;
  } else if(newButtonState == SW3){//Switch03
    setAbdacOnOff(1);
    currentSample = scaleSample;
  } else if(newButtonState == SW2){//Switch02
    setAbdacOnOff(1);
    currentSample = sineSample;
  }/* else if(newButtonState == SW1){//Switch01

  }*/ else if(newButtonState == SW0){//Switch0
    /*SILENCE WILL FALL...*/
    currentSample = NULL;
    setAbdacOnOff(0);
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