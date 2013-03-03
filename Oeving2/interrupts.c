#include "interrupts.h"
#include "oeving2.h"

__int_handler *interruptHandler(void);
void initIntc(void);


void initIntc(void) {
  set_interrupts_base((void *)AVR32_INTC_ADDRESS);
  init_interrupts();
}

__int_handler register_interrupt(__int_handler handler, int group, int line, int priority){
  asd;
}

void set_interrupts_base(void *addr){

}

void init_interrupts(void){

}

void panic(void){

}