#ifndef OEVING_3_H_SAMPLE_STRUCTS
#define OEVING_3_H_SAMPLE_STRUCTS

/* Sample structs */

typedef enum {
	SQUARE, TRIANGLE, CIRCLE
} FormType;

typedef struct Form{
	short x;
	short y;
	short dx;
	short dy;
	int radius;
	int red;
	int green;
	int blue;
	FormType formType;
} Form;

typedef struct Player{
	short health, healthMax; //Current amount of Health for player and maximum amount
	//void *graphics; //Pointer to graphics image that represent player on screen.
	Form* form;
}Player;

typedef struct Enemy{
	short health, healthMax; //Current amount of Health for enemy and maximum amount
	//void *graphics; //Pointer to graphics image that represent enemy on screen.
	Form* form;
}Enemy;

typedef struct Objects{
	Player **playerList;
	Enemy **enemyList;
	int playerSize, enemySize;
	int playerMax, enemyMax;
} Objects;

typedef enum {
	PLAYER, ENEMY
}Type;

#endif
