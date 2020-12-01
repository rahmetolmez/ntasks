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
  
    newCard->img = imageCreate(x + 1, y + 2);

    newCard->xPos = x;
    newCard->yPos = y;
    newCard->width = CARD_WIDTH;
    newCard->height = CARD_HEIGHT;

    /* Setting up card frame (window) */	    
    nodelay(newCard->win, 1); /* Not sure of this */
    newCard->win = newwin(CARD_HEIGHT, CARD_WIDTH, newCard->yPos, newCard->xPos);

    wattron(newCard->win, COLOR_PAIR(5));
    box(newCard->win, 0, 0);
    wattroff(newCard->win, COLOR_PAIR(5));

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

    imageMove(card->img, direction, distance);

    //wrefresh(card->win); /* added here to avoid flickering*/

}

void cardDraw(Card* card)
{
    /*card->win = newwin(CARD_HEIGHT, CARD_WIDTH, card->yPos, card->xPos);
    box(card->win, 0, 0);
    //refresh();
    wrefresh(card->win);*/

    //wattron(card->win, COLOR_PAIR(2));
    mvwprintw(card->win, 1, 1, card->title);
    mvwprintw(card->win, CARD_HEIGHT - 3, 1, card->text);
    //wattroff(card->win, COLOR_PAIR(2));


    mvwin(card->win, card->yPos, card->xPos);
    //wrefresh(card->win);
    wnoutrefresh(card->win);
    //doupdate();

    ///imageDraw(card->img);
}
