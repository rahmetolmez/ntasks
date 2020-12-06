#ifndef BOARD_H
#define BOARD_H

typedef struct Board
{
	WINDOW* win;
	WINDOW* headerWin;
	List* lists[50];
	char* header;
	int listCount;
	int xPos, yPos;
	int width, height;
	int bgColor, hdrColor;
}

void boardDraw(Board* board);

#endif