#Empty..
#For now...
CC=avr32-linux-gcc
CFLAGS=-g -Wall -Iinclude
LDFLAGS=-g -Wall -pedantic -Llib -lm
TARGET=game.out

##################### RULES ###########################
.PHONY : all
all: $(TARGET)

#Game C-files
game.out: main.c io.c graphics.c engine.c
	$(CC) $^ -o $@(LDFLAGS)

.PHONY : clean
clean:
	rm -rf *.out *.o *.*~