#Empty..
#For now...
CC := avr32-linux-gcc
TARGET := SurvivalGame.out
PROGRAM_C_FILES := $(wildcard *.c)
program_C_OBJS  := ${PROGRAM_C_FILES:.c=.o}
INCLUDE_DIRS :=

#LDFLAGS=-g -Wall -pedantic -Llib -lm
CFLAGS +=$(foreach includedir,$(INCLUDE_DIRS), -I$s(includedir) -g -Wall --std=c99)

##################### RULES ###########################
.PHONY : all

make: $(gitCmd) $(TARGET)

test: $(compile)
	scp ./SurvivalGame.out root@129.241.103.186:/usr/SurvivalGame.out

#Game C-files
$(TARGET): $(program_C_OBJS)
	$(CC) $(program_C_OBJS) -o $(TARGET)

gitCmd:
	#git pull

.PHONY : clean
clean:
	rm -rf *.out *.o *.*~

