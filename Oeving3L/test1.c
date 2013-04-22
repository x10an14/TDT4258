#include<stdio.h>

int main (void) {
	printf(":::: test initiated: \n");
	FILE* led_driver;
	led_driver = fopen("/dev/leddriver", "r");
	int intToOutput;
	fscanf(led_driver, "%x", &intToOutput);
	printf(":::: test closed, read %x\n", intToOutput);
  return 0;
}