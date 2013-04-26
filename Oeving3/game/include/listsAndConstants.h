#ifndef OEVING_3_H_LISTS_AND_CONSTANTS
#define OEVING_3_H_LISTS_AND_CONSTANTS

/* Defines on stack */
#define PLAYERSPEED 2
#define ENEMYSPEED 4
#define SHOTSPEED 8

#define PLAYER1_LEFT_BUTTON 7
#define PLAYER1_RIGHT_BUTTON 6
#define PLAYER1_SHOOT_BUTTON 5
#define PLAYER2_LEFT_BUTTON 1
#define PLAYER2_RIGHT_BUTTON 0
#define PLAYER2_SHOOT_BUTTON 2


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

/*Lists with modifier extern to be used as "globally accessible" lists in every *.c file*/
extern short *enemyList;
extern short *shotList;

#endif
