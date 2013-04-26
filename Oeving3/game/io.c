//Whatever includes we need to utilize our drivers.
#include <stdio.h>
#include <errno.h>
#include <linux/soundcard.h>

#define BUFFER_SIZE 2048
FILE* buttonsDriver;
FILE* ledDriver;
FILE *soundDriver;
FILE *cash;
FILE *beep;
FILE *bomb;

char read[BUFFER_SIZE];
int buttonStatus;


void playBeep(){
	soundDriver = (FILE*) fopen("/dev/dsp", "r+");
	printf("soundDriver = %d\n", soundDriver);
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
	progress += fread(&read, sizeof(char), 16, beep);
	printf("%s\n", read);
	int oldProgress = -(BUFFER_SIZE-progress);
	while(progress - oldProgress == BUFFER_SIZE){
		oldProgress = progress;
		progress += fread(&read, sizeof(char), BUFFER_SIZE, beep);
		printf("Finished reading, starting writing...\n");
		fwrite(&read, sizeof(char), BUFFER_SIZE, soundDriver);
		printf("Done with loop iteration...\n");
	}
	printf("Done with while-loop \n");
	fclose(beep);
	fclose(soundDriver);
}

void playCash(){
	soundDriver = (FILE*) fopen("/dev/dsp", "r+");
	cash = (FILE*) fopen("/root/cash.wav", "r");

	/* cash.wav setup for soundDriver */
	int input = 22050; /* Fix samplerate */
	ioctl(soundDriver, SOUND_PCM_WRITE_RATE, &input);
	input = 8; /* Fix bits/sample */
	ioctl(soundDriver, SOUND_PCM_WRITE_BITS, &input);
	input = 1; /* Fix amount of channels */
	ioctl(soundDriver, SOUND_PCM_WRITE_CHANNELS, &input);

	//Set counter
	int progress = 0;
	//read header (ignore)
	progress += fread(&read, sizeof(char), 16, cash);

	int oldProgress = -(BUFFER_SIZE-progress);
	while(progress - oldProgress == BUFFER_SIZE){
		oldProgress = progress;
		progress += fread(&read, sizeof(char), BUFFER_SIZE, cash);
		fwrite(&read, sizeof(char), BUFFER_SIZE, soundDriver);
	}

	fclose(cash);
	fclose(soundDriver);
}

void playBomb(){
	printf("Entered playBomb()...\n");
	soundDriver = (FILE*) fopen("/dev/dsp", "r+");
	bomb = (FILE*) fopen("/root/bomb.wav", "r");

	printf("Opened playBomb files...\n");
	/* bomb.wav setup for soundDriver */
	int input = 22050; /* Fix samplerate */
	ioctl(soundDriver, SOUND_PCM_WRITE_RATE, &input);
	input = 8; /* Fix bits/sample */
	ioctl(soundDriver, SOUND_PCM_WRITE_BITS, &input);
	input = 1; /* Fix amount of channels */
	ioctl(soundDriver, SOUND_PCM_WRITE_CHANNELS, &input);

	printf("Done with ioctl calls, setting counters and skipping header...\n");
	//Set counter
	int progress = 0;
	//read header (ignore)
	progress += fread(&read, sizeof(char), 16, bomb);

	printf("Entering while-loop...\n");
	int oldProgress = -(BUFFER_SIZE-progress);
	while(progress - oldProgress == BUFFER_SIZE){
		oldProgress = progress;
		progress += fread(&read, sizeof(char), BUFFER_SIZE, bomb);
		fwrite(&read, sizeof(char), BUFFER_SIZE, soundDriver);
	}

	printf("Exiting while-loop...\n");

	fclose(bomb);
	fclose(soundDriver);
}

char pullButtonsState(){
	//printf("enter pullButtonsState\n");
	buttonsDriver = (FILE*) fopen("/dev/swdriver","r+");
	char buff[3];
	fgets(buff, 3, buttonsDriver);
	fclose(buttonsDriver);
	sscanf(buff, "%x\n", &buttonStatus);
	//printf("leave pullButtonsState\n");

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
