#ifndef OEVING_3_H_SAMPLE_STRUCTS
#define OEVING_3_H_SAMPLE_STRUCTS

/* Sample structs */
typedef struct Player{
	short playerX, playerY; //Current coordinates of player
	short health, healthMax; //Current amount of Health for player and maximum amount
	//void *graphics; //Pointer to graphics image that represent player on screen.
	int dx;
	int dy;
	int radius;
	int col_red;
	int col_green;
	int col_blue;
//	enum Form form;
}Player;

typedef struct Enemy{
	short x, y; //Current coordinates of enemy
	short health, healthMax; //Current amount of Health for enemy and maximum amount
	//void *graphics; //Pointer to graphics image that represent enemy on screen.
	int dx;
	int dy;
	int radius;
	int col_red;
	int col_green;
	int col_blue;
//	enum Form form;
}Enemy;

typedef struct Shot{
	short x,y;		//Current coordinates of shot
	short damage;	//Damage current shot does
	//void *graphics;	//Pointer to graphics image that represents the shot on the screen
	int dx;
	int dy;
	int radius;
	int col_red;
	int col_green;
	int col_blue;
	//enum Form form;
}Shot;

typedef struct Objects{
	Player **playerList;
	shot **shotList;
	enemy **enemyList;
	int playerSize, enemySize, shotSize;
} Objects;

typedef enum {
	PLAYER, SHOT, ENEMY
}Type;

//enum Form{
//	Circle,
//	Square
//}
#endif
