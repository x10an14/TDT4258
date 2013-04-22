#ifndef OEVING_3_H_LISTS_AND_CONSTANTS
#define OEVING_3_H_LISTS_AND_CONSTANTS

/* Screen sizes/structs */
int xMax = 320;
int yMax = 240;
typedef struct mapBlock{
	//X time Y char[][]? G for grass, W for water, P for player, B for bush, T for tree, R for rock, and A for animal?
}mapBlock;
typedef struct screen{
	//Set of pointers to mapBloc-pointers so that we can "dynamically" replace the borders of the map until we have replaced the whole map?
	//(The whole set of mapBlocks creating the entire map)
}screen;
