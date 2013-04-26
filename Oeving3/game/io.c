//Whatever includes we need to utilize our drivers.
#include <stdio.h>
#include <errno.h>
#include <linux/soundcard.h>

#define BUFFER_SIZE 1024
FILE* buttonsDriver;
FILE* ledDriver;
FILE *soundDriver;
FILE *cash;
FILE *beep;
FILE *bomb;
char read[BUFFER_SIZE];

int buttonStatus;


void playBeep(){
	printf("Entering playBeep...\n");
	soundDriver = (FILE*) fopen("dev/dsp", "r+");
	beep = (FILE*) fopen("/root/beep.wav", "r");

	/* beep.wav setup for soundDriver */
	int input = 11025; /* Fix samplerate */
	ioctl(soundDriver, SOUND_PCM_WRITE_RATE, &input);
	input = 8; /* Fix bits/sample */
	ioctl(soundDriver, SOUND_PCM_WRITE_BITS, &input);
	input = 1; /* Fix amount of channels */
	ioctl(soundDriver, SOUND_PCM_WRITE_CHANNELS, &input);

	//Set counter
	int progress = 0;
	//read header (ignore)
	printf("Testy...\n");
	printf("&read = %d, sizeof(char) = %d, BUFFER_SIZE = %d, and beep = %d\n", &read, sizeof(char), BUFFER_SIZE, beep);
	progress += fread(&read, sizeof(char), 20, beep);

	printf("Entering while loop...\n");

	int oldProgress;
	while(progress - oldProgress == BUFFER_SIZE){
		oldProgress = progress;
		progress += fread(&read, sizeof(char), BUFFER_SIZE, beep);
		fwrite(&read, sizeof(char), BUFFER_SIZE, soundDriver);
	}
	printf("Exiting while-loop...\n");
	fclose(beep);
	fclose(soundDriver);
	printf("Exiting playBeep...\n");
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