#include <stdlib.h>
#include "oeving2.h"

//buttonState variable (Set to volatile for debugging purposes, because then it will always be kept in RAM, and its value can easily be checked)
short volatile buttonState;

//Interrupt method for the buttons
void button_isr(void){
	buttonState = ~piob->pdsr;//Read which switch was pushed (Inverted values ("active-low"), which means that it is the switch with value 0 which was pushed)
	buttonState &= piob->isr;//Read interrupt vector. We and the bitvalue in this register with the bitvalue in buttonState, which will result in a debouncing-like effect. (The time elapsed is not great, so it is not entirely correct to call it debouncing, but similar action occurs).

	//If the and-operation results in a value greater than 0 in the newBottonState variable (Implying that a value passed the debouncing check)
	if(buttonState > 0){
		pioc->codr = 0xff;//Turn off all the lights (so that whichever was last turned on is turned off)
	}

	//Turn on the light corresponding to the button pushed
	pioc->sodr = buttonState;

	//If-checks to see which button was pushed, and depending on which button was pushed, turn on or off sound, and make currentSample point to a new value.
	if(buttonState == SW7){//Switch07
		//Below is a function call to turn ON the abdac if it was turned off previously
		setAbdacOnOff(1);
		//Below we set the new address currentSample should point to
		currentSample = sawSample;
	} else if(buttonState == SW6){//Switch06
		setAbdacOnOff(1);
		currentSample = triangleSample;
	} else if(buttonState == SW5){//Switch05
		setAbdacOnOff(1);
		currentSample = squareSample;
	} else if(buttonState == SW4){//Switch04
		setAbdacOnOff(1);
		currentSample = sineSample;
	// } else if(buttonState == SW3){//Switch03/*Below code is commented out because: NOT WORKING!*/
	// 	setAbdacOnOff(1);
	// 	currentSample = flaaklypaSample;
	// } else if(buttonState == SW2){//Switch02
	// 	setAbdacOnOff(1);
	// 	currentSample = scaleSample;
	// }/* else if(buttonState == SW1){//Switch01*/

	//The below else-if is meant to let us have one button which will turn OFF sound.
	} else if(buttonState == SW0){//Switch0
		//SILENCE WILL FALL...
		currentSample = NULL;
		setAbdacOnOff(0);
	}
}

//Interrupt function for the abdac. (This method should be called 46875 times per second (ABDAC_SAMPLERATE))
void abdac_isr(void){
	/*This function is meant to happen as quickly as possible, so therefore there are no divisions, multiplications, or function calls in this function.
	It will use the sample-structures to find the next output-value it should play, if currentSample is pointing at a play-list-sample.*/

	//Declaration and initialization of output variable
	short output = 0;

	//Below is a check to see if the pointer is actually pointing at a struct (if any button except for SW0 has been pushed)
	if(currentSample != NULL){

		//Below is a check to see if we've already calculated how long to each tone should play (if we've used strokes in the calculation of the playlist)
		if(currentSample->usingStrokeList){
			//If we have, set the output variable to whatever value playCntr will as index point to in the sample's list
			output = currentSample->list[currentSample->playCntr];
			//Increment playCntr so that next time it will play the next element.
			currentSample->playCntr++;

			//Below is a check to see whether playCntr has reached the end of the sample-playlist
			if(currentSample->playCntr >= currentSample->size){
				//If so, reset it to zero, so as to repeat the tune indefinetively
				currentSample->playCntr = 0;
			}

		//Otherwise, we have not utilized strokes in the creation of the sample-playlist. We will be using rateCntr and rateMax instead
		} else{
			//Get the outputvalue which playCntr as index currently points to in currentSample's list.
			output = currentSample->list[currentSample->playCntr];
			//Increment rateCntr
			currentSample->rateCntr++;

			//Below is a check to see whether rateCntr has sent the value in currentSample's list to the output enough times
			if (currentSample->rateCntr >= currentSample->rateMax){
				//If we have, increment playCntr so that we next time play the next value in currentSample's list
				currentSample->playCntr++;
				//And reset the rateCntr to zero so each element in currentSample's list gets sent to the output rateMax amount of times.
				currentSample->rateCntr = 0;

				//Below is a iine checking whether playCntr has reached the end of currentSample's list.
				if (currentSample->playCntr >= currentSample->size){
					//If we have, reset playCntr to zero so as to repeat the tune indefinetively
					currentSample->playCntr = 0;
				}
			}
		}
	}

	//Send whatever value output has to the abdac.
	abdac->SDR.channel0 = output;
	abdac->SDR.channel1 = output;
}
