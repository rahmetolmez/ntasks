#ifndef BOARD_H
#define BOARD_H

#include"list.h"
#include<ncurses.h>
#include<string.h>
#include<stdlib.h>

#define HEADER_LENGTH 20
#define MAX_NUM_OF_LISTS 50

typedef struct Board
{
	WINDOW* win;
	WINDOW* headerWin;
	List* lists[MAX_NUM_OF_LISTS];
	char* header;
	int listCount;
	int xPos, yPos;
	int width, height;
	int bgColor, hdrColor;
}Board;

Board* boardCreate(const char* header, int x, int y);
void boardDraw(Board* board);
void boardMove(Board* board, char direction, int distance);
void boardAddList(Board* board, const char* text);
int boardRemoveList(Board* board, int listIndex);
void boardAddCard(Board* board, const char* text, int textLength, int listIndex);
int boardRemoveCard(Board* board, int listIndex, int cardIndex);
void boardChangeColor(Board* board, int bgPair, int hdrPair);
void boardChangeListColor(Board* board, int index, int pair);
void boardChangeCardColor(Board* board, int listIndex, int cardIndex, int pair);
int boardChangeListOfCard(List* from, int cardIndex, List* to);

#endif