#Empty..
#For now...
CC := avr32-linux-gcc
TARGET := BoxDefense.out
PROGRAM_C_FILES := $(wildcard *.c)
program_C_OBJS  := ${PROGRAM_C_FILES:.c=.o}
INCLUDE_DIRS :=

#LDFLAGS=-g -Wall -pedantic -Llib -lm
CFLAGS +=$(foreach includedir,$(INCLUDE_DIRS), -I$s(includedir) -g -Wall --std=c99)

##################### RULES ###########################
.PHONY : all

#Game C-files
$(TARGET): $(program_C_OBJS)
	$(CC) $(program_C_OBJS) -o $(TARGET)

all: gitCmd $(TARGET)

test: $(TARGET)
	scp ./$(TARGET) root@129.241.103.186:/usr/

gitCmd:
	git pull

.PHONY : clean
clean:
	rm -rf *.out *.o *.*~

