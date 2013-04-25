




/* Engine prototypes */
void generateMap(void); //Generate map and put player in the centre.
void startGame(void);
Objects* generateObjects(int amountOfPlayers);

void spawnEnemies(short amount, short type, short difficulty);//Self-explanatory
void shotHit(void); //When drawing the map (screen), check to see if a player or enemy will get hit by a shot
// void movePlayer(/*Modifiable object for directions? or simply an int/char*/); Remove?

void playSound(/*Pointer to sound to play (we were told that we were given some in the handed out code, no?*/);

void loseHealth(Type type, int listIndex, int amount);//Lose health, maybe flash each time? Continously flash when health is <= 3? Called by shotHit, when true. If 0, kill player/enemy.

void move(Type type, int listIndex); //Moves parameter object according to its role, if player, then like so, if enemy, then like so, and if shot, then like so.