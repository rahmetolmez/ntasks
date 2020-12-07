#ifndef CARD_H
#define CARD_H

#include<ncurses.h>

#define CARD_WINDOW_WIDTH 18
#define CARD_WINDOW_HEIGHT 5
#define CARD_WIDTH 15
#define CARD_HEIGHT 3
#define CARD_LINE_LENGTH 18
#define BLACK 'b'
#define CYAN 'c'
#define WHITE 'w'

typedef struct Card
{
	WINDOW* win;
	char* text;
	int textLength;
	int width;
	int height;
	int xPos, yPos;

}Card;

Card* cardCreate(int x, int y, const char* text, int textLength);
void cardDraw(Card* card);
void cardMove(Card* card, char direction, int distance);

#endif
