#include"list.h"
#include"card.h"
#include<string.h>
#include<stdlib.h>

List* listCreate(const char* title, const char* text, int x, int y)
{
    List* newList = (List*)malloc(sizeof(List));

    newList->title = (char*)malloc(sizeof(char) * TITLE_LENGTH);
    newList->text = (char*)malloc(sizeof(char) * TEXT_LENGTH);
    strcpy(newList->title, title);
    strcpy(newList->text, text);

    //newList->img = cardCreate(x + 2, y + 2, "", 0);
    //newList->cards[0] = cardCreate(x + 2, y + 2 + CARD_HEIGHT + 3);
    //newList->selectedCard = 0;
    newList->cardCount = 0;
    newList->xPos = x;
    newList->yPos = y;
    newList->width = LIST_WIDTH;
    ///newList->height = LIST_HEIGHT;
    newList->height = LIST_HEIGHT;//initial height
    /* Setting up list frame (window) */
    nodelay(newList->win, 1); /* Not sure of this */

    newList->win = newwin(LIST_HEIGHT, LIST_WIDTH, newList->yPos, newList->xPos);


    ///wattron(newList->win, COLOR_PAIR(5));
    ///box(newList->win, 0, 0);
    ///wattroff(newList->win, COLOR_PAIR(5));

    wbkgd(newList->win, COLOR_PAIR(1));

    //refresh();
    ///wrefresh(newList->win);
    wnoutrefresh(newList->win);
    doupdate();

    return newList;
}

void listMove(List* list, char direction, int distance)
{
    //erase(); /* added here to avoid flickering*/
    if(direction == 'w')
        list->yPos -= distance;
    if(direction == 'a')
        list->xPos -= distance;
    if(direction == 's')
        list->yPos += distance;
    if(direction == 'd')
        list->xPos += distance;

    //cardMove(list->img, direction, distance);

    for(int i = 0; i < list->cardCount; i++)
    	cardMove(list->cards[i], direction, distance);
    //wrefresh(list->win); /* added here to avoid flickering*/

}

void listAddCard(List* list, const char * text, int textLength)
{
	erase();
	wresize(list->win, list->height + (textLength / CARD_LINE_LENGTH + 2), list->width);
	list->height = list->height + textLength / CARD_LINE_LENGTH + 2;
	//wattron(list->win, COLOR_PAIR(5));
    //box(list->win, 0, 0);
    //wattroff(list->win, COLOR_PAIR(5));
	//refresh();
	wrefresh(stdscr);
	wnoutrefresh(list->win);
	//doupdate();
	if(list->cardCount == 0)
		list->cards[list->cardCount] = cardCreate(list->xPos + 1, list->yPos + 3 + list->cardCount * (textLength / 17 + 1) + (1 * list->cardCount), text, textLength);
	else
		list->cards[list->cardCount] = cardCreate(list->xPos + 1, list->cards[list->cardCount - 1]->yPos + list->cards[list->cardCount - 1]->height + 1, text, textLength);
	
    list->cardCount++;
}

int listRemoveCard(List* list, int cardIndex)
{
    if(list->cardCount <= 0 || cardIndex < 0)
        return -1;

    for(int i = list->cardCount - 1; i > cardIndex; i--)
        list->cards[i]->yPos = list->cards[i - 1]->yPos;

    //Resizing list height
    erase();
    list->height = list->height - (list->cards[cardIndex]->textLength / CARD_LINE_LENGTH + 2);
    wresize(list->win, list->height, list->width);
    //wrefresh(stdscr);
    wnoutrefresh(list->win);


    delwin(list->cards[cardIndex]->win);
    list->cardCount--;


    //int yY = list->cards[cardIndex]->yPos;
    //int lH = list->cards[cardIndex]->height;
    list->cards[cardIndex] = NULL;

    int nY = 0;
    //if(cardIndex + 1 < list->cardCount)
        //list->cards[cardIndex + 1]->yPos = yY;
    //shift the cards to avoid null card and move cards one tile up
    for(int i = cardIndex; i < list->cardCount; i++)
    {
        //nY = list->cards[i + 1]->yPos;
        list->cards[i] = list->cards[i + 1];
        //list->cards[i]->yPos = nY;
    }

    return 0;
}

void listChangeColor(List* list, int pair)
{
	wbkgd(list->win, COLOR_PAIR(pair));
}

void listChangeCardColor(List* list, int index, int pair)
{
    wbkgd(list->cards[index]->win, COLOR_PAIR(pair));
}

void listDraw(List* list)
{
    /*list->win = newwin(LIST_HEIGHT, LIST_WIDTH, list->yPos, list->xPos);
    box(list->win, 0, 0);
    //refresh();
    wrefresh(list->win);*/

    //wattron(list->win, COLOR_PAIR(2));
    //wattrset(list->win, A_BLINK);
    mvwprintw(list->win, 1, 1, list->title);
    //mvwprintw(list->win, list->height - 3, 1, list->text);
    //wattroff(list->win, COLOR_PAIR(2));

    //wborder(list->win, '-', '-', '~', ' ', 'o', 'o', 'o', 'o');
    mvwin(list->win, list->yPos, list->xPos);
    //wrefresh(list->win);
    wnoutrefresh(list->win);
    //doupdate();

    //cardDraw(list->img);
    for(int i = 0; i < list->cardCount; i++)
    	cardDraw(list->cards[i]);
}
