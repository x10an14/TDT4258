//Whatever includes we need to utilize our drivers.
#include <stdio.h>
#include <errno.h>
#include <linux/soundcard.h>

FILE* buttonsDriver;
FILE* ledDriver;
FILE *soundDriver;
FILE *cash;
FILE *beep;
FILE *bomb;
char read[1028];

int buttonStatus;

int fileSize(FILE *file){
	printf("Entered fileSize()...\n");
	int size;
	printf("Calling lseek...\n");
	fseek(file, 0, SEEK_END);
	printf("Done with lseek, calling ftell...\n");
	size = ftell(file);
	printf("Done with ftell, rewinding file...\n");
	rewind(file);
	printf("Done with fileSize(), calling return...\n");
	return size;
}


void playBeep(){
	printf("\nPLAYING SOUND!\n\n\n");
	soundDriver = (FILE*) fopen("dev/dsp", "r+");
	beep = (FILE*) fopen("/usr/beep.wav", "r");

	/* beep.wav setup for soundDriver */
	int input = 11025; /* Fix samplerate */
	ioctl(soundDriver, SOUND_PCM_WRITE_RATE, &input);
	input = 8; /* Fix bits/sample */
	ioctl(soundDriver, SOUND_PCM_WRITE_BITS, &input);
	input = 1; /* Fix amount of channels */
	ioctl(soundDriver, SOUND_PCM_WRITE_CHANNELS, &input);

	//Find size of file
	printf("Calling fileSize()...\n");
	int size = fileSize(beep);
	//Set counter
	int progress = 0;

	//read header (ignore)
	progress += fread(read, sizeof(char), 20, beep);

	printf("Starting while-loop...\n");

	while(progress < size){
		if(size - progress < 1028){
			int temp = size - progress;
			progress += fread(read, sizeof(char), temp, beep);
			fwrite(read, sizeof(char), temp, soundDriver);
		} else{
			progress += fread(read, sizeof(char), 1028, beep);
			fwrite(read, sizeof(char), 1024, soundDriver);
		}
	}

	printf("Done with while-loop and freeing files...\n");

	fclose(beep);
	fclose(soundDriver);
	printf("\nDONE PLAYING SOUND!\n\n\n");
}

// void playCash(){
// 	soundDriver = (FILE*) fopen("/dev/dsp","r+");

// 	cash = (FILE*) fopen("/usr/beep.wav","r");
// }


char pullButtonsState(){
	buttonsDriver = (FILE*) fopen("/dev/swdriver","r+");
	char buff[3];
	fgets(buff, 3, buttonsDriver);
	fclose(buttonsDriver);
	sscanf(buff, "%x\n", &buttonStatus);
	return buttonStatus;
}

int isButtonDown(int buttonNumber){
	int button;
	button = (buttonStatus >> buttonNumber) & 1;
	if (button)
		return 0;
	else
		return 1;
}

int lightLeds(int leds){
	ledDriver = (FILE*) fopen("/dev/leddriver","w");
	char buff[3];
	sprintf(buff, "%x\0", leds);
	fprintf(ledDriver, "%x", leds);
	printf("%s", buff);
	fclose(ledDriver);
	//printf("print to leddriver returns %d\n", fputs(buff, ledDriver));
	//fputc(leds, ledDriver);
	return 1;
}