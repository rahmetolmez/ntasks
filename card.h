#ifndef CARD_H
#define CARD_H

#include"image.h"
#include<ncurses.h>

#define CARD_WIDTH 20
#define CARD_HEIGHT 30
#define TITLE_LENGTH 32
#define TEXT_LENGTH 128

typedef struct Card
{
    WINDOW* win;
    char* title;
    char* text;
    Image* img;
    Image* images[50];
    int imageCount;
    int xPos, yPos;
    int width, height;
    int color;    
}Card;

Card* cardCreate(const char* title, const char* text, int x, int y);
void cardDraw(Card* card);
void cardMove(Card* card, char direction, int distance);
void cardAddImage(Card* card, const char* text, int textLength);

#endif
