//Whatever includes we need to utilize our drivers.
#include <stdio.h>
#include <errno.h>

FILE* buttonsDriver;
FILE* ledDriver;


int initiateIO(){
	buttonsDriver = (FILE*) fopen("/dev/swdriver","r+");
	
	printf("Opened buttons-driver  file: %d errno %s?22\n", buttonsDriver, strerror(errno));


}


char getButtonsState(){
	char* buff[3];
	fgets(buff, 3, buttonsDriver);
	int buttonStatus;
	sscanf(buff, "%x\n", &buttonStatus);
	return buttonStatus;
}
int isButtonDown(int buttonNumber){
	char* buff[3];
	fgets(buff, 3, buttonsDriver);
	int buttonStatus;
	sscanf(buff, "%x\n", &buttonStatus);
	buttonStatus = (buttonStatus >> buttonNumber) & 1;
	if (buttonStatus)
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