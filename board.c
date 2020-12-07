#include"board.h"

Board* boardCreate(const char* header, int x, int y)
{
	Board* newBoard = (Board*)malloc(sizeof(Board));
	header = (char*)malloc(sizeof(HEADER_LENGTH));

	newBoard->win = newwin(LINES, COLS, y, x);
	newBoard->headerWin = newwin(3, COLS - 2, y + 1, x + 1);

	wattrset(newBoard->headerWin, A_BOLD);
    mvwprintw(newBoard->headerWin, 1, (COLS - 2) / 2 - 6, header); //remove magic nums

    wbkgd(newBoard->win, COLOR_PAIR(7));
    wbkgd(newBoard->headerWin, COLOR_PAIR(8));

    wnoutrefresh(newBoard->win);
    wnoutrefresh(newBoard->headerWin);

    doupdate();

    newBoard->listCount = 0;
    newBoard->xPos = x;
    newBoard->yPos = y;
    newBoard->width = COLS;
    newBoard->height = LINES;
    newBoard->bgColor = 7;
    newBoard->hdrColor = 8;
}

void boardDraw(Board* board)
{
	mvwin(board->headerWin, board->yPos + 1, board->xPos + 1);
	mvwin(board->win, board->yPos, board->xPos);

	wnoutrefresh(board->headerWin);
	wnoutrefresh(board->win);

	for(int i = 0; i < board->listCount; i++)
		listDraw(board->lists[i]);
}

void boardMove(Board* board, char direction, int distance)
{
	if(direction == 'w')
        board->yPos -= distance;
    if(direction == 'a')
        board->xPos -= distance;
    if(direction == 's')
        board->yPos += distance;
    if(direction == 'd')
        board->xPos += distance;

	for(int i = 0; i < board->listCount; i++)
		listMove(board->lists[i], direction, distance);
}

void boardAddList(Board* board, const char* text)
{
	board->lists[board->listCount] = listCreate(text, "", board->listCount * LIST_WIDTH + (board->listCount + 1), 5);
	board->listCount++;
}

int boardRemoveList(Board* board, int listIndex)
{

}

void boardAddCard(Board* board, const char* text, int textLength, int listIndex)
{
	listAddCard(board->lists[listIndex], text, textLength);
}

int boardRemoveCard(Board* board, int listIndex, int cardIndex)
{
	listRemoveCard(board->lists[listIndex], cardIndex);
}

void boardChangeColor(Board* board, int bgPair, int hdrPair)
{

}

void boardChangeListColor(Board* board, int index, int pair)
{
	listChangeColor(board->lists[index], pair);
}

void boardChangeCardColor(Board* board, int listIndex, int cardIndex, int pair)
{
	listChangeCardColor(board->lists[listIndex], cardIndex, pair);
}

int boardChangeListOfCard(List* from, int cardIndex, List* to)
{
    if(from->cardCount <= 0 || cardIndex < 0 || (from == to))
        return -1;
    listAddCard(to, from->cards[cardIndex]->text, strlen(from->cards[cardIndex]->text));
    listRemoveCard(from, cardIndex);

    return 0;
}