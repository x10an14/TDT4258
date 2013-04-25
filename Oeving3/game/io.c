//Whatever includes we need to utilize our drivers.
#include <stdio.h>
#include <errno.h>
FILE* buttonsDriver;

int A(void){
	return 0;
}

int B(void){
	return 0;
}

int C(void){
	return 0;
}

int initiateButtons(){
	buttonsDriver = (FILE*) fopen("/dev/swdriver","r+");
	printf("Opened buttons-driver file: %d errno %s?22\n", buttonsDriver, strerror(errno));
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