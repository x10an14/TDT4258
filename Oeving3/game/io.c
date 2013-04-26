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

	//Set counter
	int progress = 0;
	//read header (ignore)
	progress += fread(read, sizeof(char), 20, beep);

	printf("Starting while-loop...\n");
	int oldProgress;
	while(oldProgress < progress){
		oldProgress = progress;
		progress += fread(read, sizeof(char), 1024, beep);
		fwrite(read, sizeof(char), 1024, soundDriver);
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