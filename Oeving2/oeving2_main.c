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


int main (int argc, char *argv[]){
  // Creating of sinus wave list 128 steps
  short *sineSampleList = (short*) malloc(SINEARRAYSIZE*sizeof(short));;
  //for-loop cntr
  int i;
  for (i=0; i < SINEARRAYSIZE; i++){
    sineSampleList[i] = SHRT_MAX*sin((M_PI*i)/SINEARRAYSIZE);
  }

  //Allocate space on heap for pointers (And set all member-values to zero!)
  flaa1 = (sample*) calloc(1, sizeof(sample));
  flaa2 = (sample*) calloc(1, sizeof(sample));
  flaa3 = (sample*) calloc(1, sizeof(sample));
  flaa4 = (sample*) calloc(1, sizeof(sample));
  sawSample = (sample*) calloc(1, sizeof(sample));
  sineSample = (sample*) calloc(1, sizeof(sample));
  scaleSample = (sample*) calloc(1, sizeof(sample));
  squareSample = (sample*) calloc(1, sizeof(sample));
  triangleSample = (sample*) calloc(1, sizeof(sample));
  flaaklypaSample = (sample*) calloc(1, sizeof(sample*));

  //Initialize variable for above allocated short-size-members
  flaa1->size = 8;
  flaa2->size = 12;
  flaa3->size = 9;
  flaa4->size = 15;
  sawSample->size = ARRAYSIZE;
  sineSample->size = SINEARRAYSIZE;
  scaleSample->size = 8; //An octave is eight tones long
  squareSample->size = ARRAYSIZE;
  triangleSample->size = ARRAYSIZE;

  //Assigning space for tonelists! (playlists in sample)
  flaa1->list = (short*) malloc(flaa1->size*sizeof(short));
  flaa2->list = (short*) malloc(flaa2->size*sizeof(short));
  flaa3->list = (short*) malloc(flaa3->size*sizeof(short));
  flaa4->list = (short*) malloc(flaa4->size*sizeof(short));
  sawSample->list = (short*) malloc(sawSample->size*sizeof(short));
  sineSample->list = (short*) malloc(sineSample->size*sizeof(short));
  scaleSample->list = (short*) malloc(scaleSample->size*sizeof(short));
  triangleSample->list = (short*) malloc(triangleSample->size*sizeof(short));

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
  flaa1->strokeList = (short*) malloc(flaa1->size*sizeof(short));
  flaa2->strokeList = (short*) malloc(flaa2->size*sizeof(short));
  flaa3->strokeList = (short*) malloc(flaa3->size*sizeof(short));
  flaa4->strokeList = (short*) malloc(flaa4->size*sizeof(short));
  scaleSample->strokeList = (short*) malloc(scaleSample->size*sizeof(short));

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
    }
  }

  //Assigning space
  flaaklypaSample->size = memCntr;
  flaaklypaSample->list = (short*) calloc(memCntr, sizeof(short));

  //Assigning(/Combining) values to final list (flaaklypaSample->list)
  int cntr = 0;
  for(i = 0; i < flaaklyp->size; i++){
    sample *small = flaaklyp->list[i];
    int j, size;
    for(j = 0; j < small->size; j++){
      size = (int)(ABDAC_SAMPLERATE/small->strokeList[j]);
      addFrequency(small->strokeList[j], small->list[j], flaaklypaSample->list, cntr);
      cntr += size;
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
  }

  //Assigning space
  scaleSample = (sample*) malloc(sizeof(sample*));
  scaleSample->size = memCntr;
  scaleSample->list = (short*) calloc(memCntr, sizeof(short)); //Total size of tune

  //Assigning(/Combining) values to final list (flaaklypaSample->list)
  cntr = 0;
  for(i = 0; i < scaleSample->size; i++){
    size = (int) (ABDAC_SAMPLERATE/SCALESTROKE[i]);
    addFrequency(SCALESTROKE[i], SCALE[i], scaleSample->list, cntr);
    cntr += size;
  }

  //The rate (amount of times we play each element) is already set with the function addFrequency. So no need to use it on this sample
  flaaklypaSample->usingStrokeList = 1;
  scaleSample->usingStrokeList = 1;

  sawSample->rateMax = SAWRATE;
  sineSample->rateMax = SINERATE;
  squareSample->rateMax = SQUARERATE;
  triangleSample->rateMax = TRIANGLERATE;

  initHardware();

  while(1);
  return 0;
}
