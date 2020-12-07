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

    newList->cardCount = 0;
    newList->xPos = x;
    newList->yPos = y;
    newList->width = LIST_WIDTH;

    newList->height = LIST_HEIGHT;//initial height

    nodelay(newList->win, 1); /* Not sure of this */

    newList->win = newwin(LIST_HEIGHT, LIST_WIDTH, newList->yPos, newList->xPos);

    wbkgd(newList->win, COLOR_PAIR(1));

    wnoutrefresh(newList->win);
    doupdate();

    return newList;
}

void listMove(List* list, char direction, int distance)
{
    if(direction == 'w')
        list->yPos -= distance;
    if(direction == 'a')
        list->xPos -= distance;
    if(direction == 's')
        list->yPos += distance;
    if(direction == 'd')
        list->xPos += distance;

    for(int i = 0; i < list->cardCount; i++)
    	cardMove(list->cards[i], direction, distance);
}

void listAddCard(List* list, const char * text, int textLength)
{
	erase();
	wresize(list->win, list->height + (textLength / CARD_LINE_LENGTH + 2), list->width);
	list->height = list->height + textLength / CARD_LINE_LENGTH + 2;

	wrefresh(stdscr);
	wnoutrefresh(list->win);

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
    wnoutrefresh(list->win);

    delwin(list->cards[cardIndex]->win);
    list->cardCount--;
    list->cards[cardIndex] = NULL;

    for(int i = cardIndex; i < list->cardCount; i++)
    {
        list->cards[i] = list->cards[i + 1];
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
    mvwprintw(list->win, 1, 1, list->title);

    mvwin(list->win, list->yPos, list->xPos);

    wnoutrefresh(list->win);

    for(int i = 0; i < list->cardCount; i++)
    	cardDraw(list->cards[i]);
}
