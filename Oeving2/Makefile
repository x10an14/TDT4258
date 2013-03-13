CC=avr32-gcc
CFLAGS=-g -Wall -Iinclude
LDFLAGS=-g -Wall -pedantic -Llib -lavr32b-interrupts -lm
TARGET=oeving2.elf


# Command to upload program to flash
AVR32PROGRAM = avr32program

####### RULES ##########################################################
.PHONY : all
all: $(TARGET)

#Below I have added all the c-files with the segmented code for this to compile correctly
oeving2.elf: oeving2_main.o oeving2_InitFunctions.o oeving2_InterruptFunctions.o oeving2_SampleFunctions.o
	$(CC) $^ -o $@ $(LDFLAGS)

#Below I rewrote the oeving2.c to %.c to compile ALL c-files (Read above comment for clarification if this comment confuses)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# upload to STK1000 (program flash)
.PHONY : upload
upload : $(TARGET)
	$(AVR32PROGRAM) halt
	sleep 3
	$(AVR32PROGRAM) program -e -f0,8Mb $<

.PHONY : clean
clean :
	rm -rf *.o *.elf *.*~
