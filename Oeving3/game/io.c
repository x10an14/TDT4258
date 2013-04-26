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
	int size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	return size;
}


void playBeep(){
	printf("\nPLAYING SOUND!\n\n\n");
	soundDriver = (FILE*) fopen("dev/dsp", "r+");
	printf("Finished opening soundDriver...\n");
	beep = (FILE*) fopen("/usr/beep.wav", "r");

	printf("Finished opening files...\n");

	/* beep.wav setup for soundDriver */
	int input = 11025; /* Fix samplerate */
	ioctl(soundDriver, SOUND_PCM_WRITE_RATE, &input);
	printf("First ioctl call done...\n");
	input = 8; /* Fix bits/sample */
	ioctl(soundDriver, SOUND_PCM_WRITE_BITS, &input);
	printf("Second ioctl call done...\n");
	input = 1; /* Fix amount of channels */
	ioctl(soundDriver, SOUND_PCM_WRITE_CHANNELS, &input);
	printf("Third ioctl call done...\n");

	//Find size of file
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