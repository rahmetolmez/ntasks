#include"card.h"
#include<stdlib.h>
#include<string.h>

Card* cardCreate(int x, int y, const char* text, int textLength)
{
	Card* newCard = (Card*)malloc(sizeof(Card));
	newCard->textLength = textLength;
	newCard->text = (char*)malloc(sizeof(char) * newCard->textLength + 1);

	strcpy(newCard->text, text);
	newCard->width = CARD_WINDOW_WIDTH;
	newCard->height = textLength / CARD_WINDOW_WIDTH + 1;
	newCard->xPos = x;
    newCard->yPos = y;

	nodelay(newCard->win, 1); /* Not sure of this */
    newCard->win = newwin(newCard->height, newCard->width, newCard->yPos, newCard->xPos);

	wbkgd(newCard->win, COLOR_PAIR(4));

	mvwprintw(newCard->win, 0, 1, newCard->text);//why not in cardDraw??
	wnoutrefresh(newCard->win);
 
    return newCard;
}

void cardDraw(Card* card)
{
    int i, j;

    mvwin(card->win, card->yPos, card->xPos);
    wnoutrefresh(card->win);
}

void cardMove(Card* card, char direction, int distance)
{
    if(direction == 'w')
        card->yPos -= distance;
    if(direction == 'a')
        card->xPos -= distance;
    if(direction == 's')
        card->yPos += distance;
    if(direction == 'd')
        card->xPos += distance;
}

