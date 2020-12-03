/*REFACTOR TO CARD */
#include"card.h"
#include<stdlib.h>
#include<string.h>

Card* cardCreate(int x, int y, const char* text, int textLength)
{
	Card* newCard = (Card*)malloc(sizeof(Card));
	newCard->textLength = textLength;
	newCard->text = (char*)malloc(sizeof(char) * newCard->textLength + 1);
	//text[textLength - 1] = '\0';
	strcpy(newCard->text, text);
	newCard->width = CARD_WINDOW_WIDTH;
	newCard->height = textLength / CARD_WINDOW_WIDTH + 1;
	newCard->xPos = x;
    	newCard->yPos = y;

	//printf("%s", newCard->text);
	nodelay(newCard->win, 1); /* Not sure of this */
    	newCard->win = newwin(newCard->height, newCard->width, newCard->yPos, newCard->xPos);
    	//box(newCard->win, 0, 0);
	//wbkgd(newCard->win, COLOR_PAIR(1));

    	///refresh();
    	///wrefresh(newCard->win);
	mvwprintw(newCard->win, 0, 1, newCard->text);//why not in cardDraw??
	wnoutrefresh(newCard->win);
 
    	return newCard;
}

void cardDraw(Card* card)
{
    int i, j;
    /*for(i = 0; i < CARD_HEIGHT; i++)
    {
    	for(j = 0; j < CARD_WIDTH; j++)
	{
		if(card->img[i][j] == CYAN)
		{
			wattron(card->win, COLOR_PAIR(3));
			mvwaddch(card->win, i + 1, j + 1, card->img[i][j]);
			wattroff(card->win, COLOR_PAIR(3));
		}
		if(card->img[i][j] == BLACK)
		{
			wattron(card->win, COLOR_PAIR(2));
			mvwaddch(card->win, i + 1, j + 1, card->img[i][j]);
			wattroff(card->win, COLOR_PAIR(2));
		}
		if(card->img[i][j] == WHITE)
		{
			wattron(card->win, COLOR_PAIR(4));
			mvwaddch(card->win, i + 1, j + 1, card->img[i][j]);
			wattroff(card->win, COLOR_PAIR(4));
		}
		/*wattron(card->win, COLOR_PAIR(2));
		mvwaddch(card->win, i + 1, j + 1, card->img[i][j]);
		wattroff(card->win, COLOR_PAIR(2));
	}
	
    }*/
    wbkgd(card->win, COLOR_PAIR(4));
    mvwin(card->win, card->yPos, card->xPos);
    ///wrefresh(card->win);
    //wprintw(card->win, card->text);
    wnoutrefresh(card->win);
    //doupdate();
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

void cardSet(Card* card, char img[CARD_HEIGHT][CARD_WIDTH])
{
	int i, j;
	for(i = 0; i < CARD_HEIGHT; i++)
	{
		for(j = 0; j < CARD_WIDTH; j++)
		{
			card->img[i][j] = img[i][j];
		}
	}
}

