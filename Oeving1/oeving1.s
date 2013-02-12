.include "io.s"  /* Include useful symbols. */
 
.macro load_base_registers
	/*Load adresses of LED, switch GPIO, and interrupt
	controllers to registers R0, R1, and R2.
	R0, R1, and R2 SHOULD NOT be modified afterwards.
	*/
        lddpc r0, pio_led_ptr
        lddpc    r1, pio_switch_ptr
        lddpc    r2, intc_ptr
.endm
 
 
.text
 
.globl  _start //Line where program starts
_start  :
	/* Enable stack. */
        lddpc    sp, stack_ptr
 
	/* Set R0, R1, R2. */
        load_base_registers
 
        /* Enable output on all 8 LEDs. */
        mov      r8,                 0xff /* Move the value 0xff into R8 */
        st.w     r0[AVR32_PIO_PER],  r8 /* Set LED Pin Enable Register to value for all  LEDs (0xff) */
        st.w     r0[AVR32_PIO_OER],  r8 /* Same as above for LED Output Enable Register *
 
        /* Enable switches 6 and 7 (including interrupts on them). */
        mov      r8,                 (1<<7)+(1<<6) /* Set bit nr.7 and 6 to value 1, and the rest to 0 in R8 */
        st.w     r1[AVR32_PIO_PER],  r8 /* Set Switch Pin Enable Register to the value in R8 */
        st.w     r1[AVR32_PIO_PUER], r8 /* Same as above for Pull Up Enable Resistor */
        st.w     r1[AVR32_PIO_IER],  r8 /* Same as above for Interrupt Enable Register */
        com      r8 			/* (One's complement)Invert the binary value of R8 */
        st.w     r1[AVR32_PIO_IDR],  r8 /* Same as previous st.w command, except this is for Interrupt Disable Register 
					We have to invert the value of R8 because the IDR register reads the opposite
					binary value as active, compared to the three other registers. */
 
        /* Set EVBA address to zero. */
        mov     r8,     0 /* Move value 0 to R8 (Temporarily for the benefit of the next line) */
        mtsr    4,      r8 /* Enable EVBA by the command as shown (mtsr 4, <empty register>) */
 
        mov     r8,     handle_interrupt /* Put the address for the macro/block "handle_interrupt" into R8 */
        st.w    r2[AVR32_INTC_IPR14], r8 /* Store word in R8 into the IPR-register for the interrupt controller (IPR14) */
 
        /* Enable interrupts globally. */
        csrf    16
 
        /* Initialize paddle pos and LEDs. */
        lddpc   r7,                  paddle_position_ptr /* Load pointer to paddle position variable into R7 relative to Program Counter */
        mov     r6,                  (1<<7) /* Set bit nr. 7 to 1 and the rest to 0 in R6 */
        st.w    r7,                  r6 /* Store value of R6 into address pointed to by R7 */
        st.w    r0[AVR32_PIO_SODR],  r6 /* Set LED Output Data Register to the value in R6 */
        com     r6			/* (One's Compliment) Invert the binary value of R6 */
        st.w    r0[AVR32_PIO_CODR],  r6 /* Set LED Clear Output Data Register to the value in R6 (inverted after SODR, due to same reason as IDR (boolean active values)) */
 
loop:	/* Enter infinite loop of sleep mode 1 
	Whenever the program finishes an interrupt routine, it will return here and go to the line "rjmp loop",
	before it continues to "sleep 1" again. */
	sleep 1
        rjmp loop
 
handle_interrupt:
        /* We have fairly good control over the registers here,
           but if this was "for real" we ought to save all registers
           we're using, and restore them.
           Strictly speaking there is no need to push registers to stack in our program.
         */
        pushm R0-R3, R4-R7, R8-R9, R10, R11, R12 
 
        load_base_registers /* Repeat loading of base registers */
        lddpc   r7,  paddle_position_ptr /* Load pointer to paddle_position variable into R7 relative to Program Counter.
	The above is strictrly speaking redundant (see comment for handle_interrupt).
	It would however be necessary if we were not in control and sure that our program was the only one running on the
	microcontroller. */
 
        /* Read the status register. (MUST be done, but we just ignore its
        value.) */
        ld.w    r8,     r1[AVR32_PIO_ISR] 
 
        /* Read switches. */
        ld.w    r8,     r1[AVR32_PIO_PDSR] /* Load switch Pin Data Status Register value into R8 */
        com     r8			   /* Invert value of R8, due to AND comparison after debouncing (Because of its 0-active boolean logic) */

        /* Spin a bit, for debouncing. */
        mov     r12,    0xffff /* Move value 0xffff (2^16) into R12 */

debounce_more:
        sub     r12,    1 /* Substract the value 1 from the value in R12 */
        cp.w    r12,    0 /* Compare word value R12 with the value 0 */
        brne    debounce_more /*If not zero, jump back to debounce_more and substract again */

        /* Re-read and do an AND comparison with previous read */
        ld.w    r9,     r1[AVR32_PIO_PDSR] /* Load switch Pin-Data Status Register value into R9 */
        com     r9	/* Invert the binary value in R9 */
        and     r8,     r9 /* Do an AND comparison of the values 
	before and after debouncing (R8 & R) to make sure that after the debouncing
	the same paddle (switch) is still being pressed down by a finger */
 
        /* Load paddle position. */
        ld.w    r6,  r7  /* Load value R7 points to into R6 */
 
act_switch_left:
        /* If SW7 is down... */
        mov      r12,     (1<<7) /* Move the binary value 2⁸ into R12 */
        and      r12,     r8	/* Compare R12 and R8. If equal, SW7 is still pressed after debouncing. */
        brne     act_switch_right  /* Then jump to act_switch_right if previous comment is untrue. */

        /* ...and paddle is not at leftmost max... */
        cp.w     r6,      (1<<7)	/* Compare value of R6 with the binary value of 2⁷ */
        breq     flip_from_left		/* If equal, the light is at the leftmost position
	and we want to "flip it" all the way to the right. So jump to flip_from_left */

        /* ...move paddle pos left. */
        lsl      r6,      1	/* Else shift bit in R6 one place to the left. */
        rjmp     update_leds 	/* When done with act_switch_left, jump to update_leds */
 
act_switch_right:
        /* If SW6 is down... */
        mov      r12,     (1<<6)/* Move the binary value 2⁶ into R12 */
        and      r12,     r8	/* Compare R12 and R8. If equal, SW6 is still pressed after debouncing. */
        brne     update_leds	/* If the above comment is untrue, jump to update_leds

        /* ...and paddle is not at rightmost max... */
        cp.w     r6,     (1<<0)	/* Compare value in R6 withe the binary value of 2⁰ */
        breq     flip_from_right/* If equal, the light is at the rightmost position, 
	and we want to "flip it" all the way to the right. So jump to flip_from_right */

        /* ...move paddle pos right. */
        lsr      r6,      1	/* Otherwise, light up the LED to the right by shifting
	the binary value in R6 to the right */
 
flip_from_left:
	mov 	r6, 	(1<<0)	/* Flip the LED to the opposite end (make it cycle/wrap) */
	rjmp	update_leds

flip_from_right:
	mov	r6, 	(1<<7) /*Flip the LED to the opposite end (make it cycle/wrap) */
	rjmp 	update_leds

update_leds:
        /* Smack up the LEDs. */
        st.w  r0[AVR32_PIO_SODR], r6	/* Store the value of R6 into LED Set Output Data Register */
        com   r6			/* (One's complement) Invert the value of R6 and store result in R6 */
        st.w  r0[AVR32_PIO_CODR], r6	/* Store the value in R6 into LED Clear Output Data Register.
	We have to invert the value since the active bit in CODR is the inactive bit in SODR. */
        com   r6	/* (One's complement) Return the value in R6 to the original value */
 
        /* Write (potentially new) paddle position back to memory. */
        st.w  r7, r6	/* Store value of R6 to the memory address pointed to by the value in R7 */
 
        /* Restore registers to pre-interrupt state, and return. */
        popm R0-R3, R4-R7, R8-R9, R10, R11, R12	/* Pop all register stacks off the stack and back into 
	their original "RX" addresses. */
        rete //Return command to exit interrupt routine
 
 
pio_led_ptr:
	/* Pointer variable to GPIO PIOC Adressspace */
        .int AVR32_PIOC
pio_switch_ptr:
	/* Pointer variable to GPIO PIOB Adressspace */
        .int AVR32_PIOB
intc_ptr:
        /* Pointer variable to Interrupt Controller adresss */
	.int AVR32_INTC
paddle_position_ptr:
	/* Pointer variable to access the .data paddle_position variable */
        .int paddle_position
stack_ptr:
	/* Value which corresponds to the Stack "activation" adress */
        .int _stack
 
.data
 
paddle_position:
        /* Current position of the active LED */
        .int
