//Whatever includes we need to utilize our drivers.
#include <stdio.h>
#include <errno.h>
#include <linux/soundcard.h>


FILE* buttonsDriver;
FILE* ledDriver;
FILE *soundDriver;

//Used in the dynamically playing function
FILE *currentWav;

char read[BUFFER_SIZE];
int buttonStatus;

void playCurrent(){
	int progress = fread(&read, sizeof(char), BUFFER_SIZE, currentWav);
	fwrite(&read, sizeof(char), BUFFER_SIZE, soundDriver);
	if(progress < BUFFER_SIZE){
		fclose(currentWav);
	}
}

void initializeSound(void){
	soundDriver = (FILE*) fopen("/dev/dsp", "r+");
}

void closeSound(void){
	fclose(soundDriver);
}

void playBeep(){
	currentWav = (FILE*) fopen("/root/beep.wav", "r");

	/* beep.wav setup for soundDriver */
	int input = 11025; /* Fix samplerate */
	ioctl(soundDriver, SOUND_PCM_WRITE_RATE, &input);
	input = 8; /* Fix bits/sample */
	ioctl(soundDriver, SOUND_PCM_WRITE_BITS, &input);
	input = 1; /* Fix amount of channels */
	ioctl(soundDriver, SOUND_PCM_WRITE_CHANNELS, &input);

	//read header (ignore it)
	input = fread(&read, sizeof(char), 16, cash);
	playCurrent();
}

void playCash(){
	currentWav = (FILE*) fopen("/root/cash.wav", "r");

	/* cash.wav setup for soundDriver */
	int input = 22050; /* Fix samplerate */
	ioctl(soundDriver, SOUND_PCM_WRITE_RATE, &input);
	input = 8; /* Fix bits/sample */
	ioctl(soundDriver, SOUND_PCM_WRITE_BITS, &input);
	input = 1; /* Fix amount of channels */
	ioctl(soundDriver, SOUND_PCM_WRITE_CHANNELS, &input);

	//read header (ignore it)
	input = fread(&read, sizeof(char), 16, currentWav);
	playCurrent();
}

void playBomb(){
	currentWav = (FILE*) fopen("/root/bomb.wav", "r");

	/* bomb.wav setup for soundDriver */
	int input = 22050; /* Fix samplerate */
	ioctl(soundDriver, SOUND_PCM_WRITE_RATE, &input);
	input = 8; /* Fix bits/sample */
	ioctl(soundDriver, SOUND_PCM_WRITE_BITS, &input);
	input = 1; /* Fix amount of channels */
	ioctl(soundDriver, SOUND_PCM_WRITE_CHANNELS, &input);

	//read header (ignore it)
	input = fread(&read, sizeof(char), 16, bomb);
	playCurrent();
}

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
	ledDriver = (FILE*) fopen("/dev/leddriver","r+");
	char buff[3];
	sprintf(buff, "%x", leds);

	fprintf(ledDriver, "%s", buff);

	int num1 = leds % 0x10;
	int num2 = leds - num1;
	fputc(num2, ledDriver);
	fputc(num1, ledDriver);

	fclose(ledDriver);
	return 1;
}
