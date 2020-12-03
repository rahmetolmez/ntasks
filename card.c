#include"card.h"
#include<string.h>
#include<stdlib.h>

Card* cardCreate(const char* title, const char* text, int x, int y)
{
    Card* newCard = (Card*)malloc(sizeof(Card));

    newCard->title = (char*)malloc(sizeof(char) * TITLE_LENGTH);
    newCard->text = (char*)malloc(sizeof(char) * TEXT_LENGTH);
    strcpy(newCard->title, title);
    strcpy(newCard->text, text);

    //newCard->img = imageCreate(x + 2, y + 2, "", 0);
    //newCard->images[0] = imageCreate(x + 2, y + 2 + IMAGE_HEIGHT + 3);

    newCard->imageCount = 0;
    newCard->xPos = x;
    newCard->yPos = y;
    newCard->width = CARD_WIDTH;
    ///newCard->height = CARD_HEIGHT;
    newCard->height = 6;//initial height
    /* Setting up card frame (window) */
    nodelay(newCard->win, 1); /* Not sure of this */
    newCard->win = newwin(6, CARD_WIDTH, newCard->yPos, newCard->xPos);

    ///wattron(newCard->win, COLOR_PAIR(5));
    ///box(newCard->win, 0, 0);
    ///wattroff(newCard->win, COLOR_PAIR(5));

    wbkgd(newCard->win, COLOR_PAIR(1));

    //refresh();
    ///wrefresh(newCard->win);
    wnoutrefresh(newCard->win);
    doupdate();

    return newCard;
}

void cardMove(Card* card, char direction, int distance)
{
    //erase(); /* added here to avoid flickering*/
    if(direction == 'w')
        card->yPos -= distance;
    if(direction == 'a')
        card->xPos -= distance;
    if(direction == 's')
        card->yPos += distance;
    if(direction == 'd')
        card->xPos += distance;

    //imageMove(card->img, direction, distance);

    for(int i = 0; i < card->imageCount; i++)
    	imageMove(card->images[i], direction, distance);
    //wrefresh(card->win); /* added here to avoid flickering*/

}

void cardAddImage(Card* card, const char * text, int textLength)
{
	erase();
	wresize(card->win, card->height + (textLength / 18 + 2), card->width);
	card->height = card->height + textLength / 18 + 2;
	//wattron(card->win, COLOR_PAIR(5));
    //box(card->win, 0, 0);
    //wattroff(card->win, COLOR_PAIR(5));
	//refresh();
	wrefresh(stdscr);
	wnoutrefresh(card->win);
	//doupdate();
	if(card->imageCount == 0)
		card->images[card->imageCount] = imageCreate(card->xPos + 1, card->yPos + 3 + card->imageCount * (textLength / 17 + 1) + (1 * card->imageCount), text, textLength);
	else
		card->images[card->imageCount] = imageCreate(card->xPos + 1, card->images[card->imageCount - 1]->yPos + card->images[card->imageCount - 1]->height + 1, text, textLength);
	card->imageCount++;
}

void cardChangeColor(Card* card, int pair)
{
	wbkgd(card->win, COLOR_PAIR(pair));
}

void cardDraw(Card* card)
{
    /*card->win = newwin(CARD_HEIGHT, CARD_WIDTH, card->yPos, card->xPos);
    box(card->win, 0, 0);
    //refresh();
    wrefresh(card->win);*/

    //wattron(card->win, COLOR_PAIR(2));
    mvwprintw(card->win, 1, 1, card->title);
    //mvwprintw(card->win, card->height - 3, 1, card->text);
    //wattroff(card->win, COLOR_PAIR(2));


    mvwin(card->win, card->yPos, card->xPos);
    //wrefresh(card->win);
    wnoutrefresh(card->win);
    //doupdate();

    //imageDraw(card->img);
    for(int i = 0; i < card->imageCount; i++)
    	imageDraw(card->images[i]);
}
