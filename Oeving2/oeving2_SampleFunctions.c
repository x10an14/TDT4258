#include "oeving2.h"

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
      list[j] = SHRT_MAX;
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
