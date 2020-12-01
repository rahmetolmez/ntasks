#ifndef IMAGE_H
#define IMAGE_H

#include<ncurses.h>

#define IMAGE_WINDOW_WIDTH 18
#define IMAGE_WINDOW_HEIGHT 10
#define IMAGE_WIDTH 16
#define IMAGE_HEIGHT 8

#define BLACK 'b'
#define CYAN 'c'
#define WHITE 'w'

typedef struct Image
{
	WINDOW* win;
	char img[IMAGE_HEIGHT][IMAGE_WIDTH];
	int xPos, yPos;

}Image;

Image* imageCreate(int x, int y);
void imageDraw(Image* image);
void imageMove(Image* image, char direction, int distance);
void imageSet(Image* image, char img[IMAGE_HEIGHT][IMAGE_WIDTH]);

#endif
