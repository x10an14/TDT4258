#ifndef OEVING3_PROTOTYPES_H
#define OEVING3_PROTOTYPES_H

#include "sampleStructs.h"

/* IO prototypes */
void playBeep(void);
void playCash(void);
void playBomb(void);
int playCurrent(void);
void initializeSound(void);
void closeSound(void);

/* Graphics prototypes */
void setImageStruct(void);
int draw_background(void);
int draw_square(int x, int y, int radius, char red, char green, char blue);
int redraw_player(Player *thePlayer);
void setUpLCDDriver(void);

/* SampleFunction prototypes */
void insertPlayers(Objects *container, int amountOfPlayers);
void insertEnemy(Objects *container, int startX, int startY, int health, int speed);
void insertShot(Objects *container, int startX, int startY, int damage);
void killPlayer(Objects *container, int listIndex);
void killEnemy(Objects *container, int listIndex);

/* Engine prototypes */
void moveEnemy(int listIndex);
void make_new_frame(void);
void movePlayer(int listIndex);
void generateMap(void); //Generate map and put player in the centre.
void startGame(void);
Objects* generateObjects(int amountOfPlayers);
void spawnEnemies(short amount, short type, short difficulty);//Self-explanatory
void playSound(/*Pointer to sound to play (we were told that we were given some in the handed out code, no?*/);
void loseHealth(Type type, int listIndex, int amount);//Lose health, maybe flash each time? Continously flash when health is <= 3? Called by shotHit, when true. If 0, kill player/enemy.
void computeMove(Type type, int listIndex); //Moves parameter object according to its role, if player, then like so, if enemy, then like so, and if shot, then like so.

#endif 
