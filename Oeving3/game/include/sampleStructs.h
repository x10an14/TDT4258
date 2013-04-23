#ifndef OEVING_3_H_SAMPLE_STRUCTS
#define OEVING_3_H_SAMPLE_STRUCTS

/* Sample structs */
typedef struct player{
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
}player;

typedef struct enemy{
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
}enemy;

typedef struct shot{
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
}shot;

//enum Form{
//	Circle,
//	Square
//}
#endif
