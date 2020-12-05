#ifndef LIST_H
#define LIST_H

#include"card.h"
#include<ncurses.h>

#define LIST_WIDTH 20
#define LIST_HEIGHT 30
#define TITLE_LENGTH 32
#define TEXT_LENGTH 128

typedef struct List
{
    WINDOW* win;
    char* title;
    char* text;
    Card* cards[50];
    int cardCount;
    int xPos, yPos;
    int width, height;
    int color;    
    //int selectedCard;
}List;

List* listCreate(const char* title, const char* text, int x, int y);
void listDraw(List* list);
void listMove(List* list, char direction, int distance);
void listAddCard(List* list, const char* text, int textLength);
int listRemoveCard(List* list, int cardIndex);
void listChangeColor(List* list, int pair);
void listChangeCardColor(List* list, int index, int pair);

#endif
