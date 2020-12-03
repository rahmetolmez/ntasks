#ifndef IMAGE_H
#define IMAGE_H

#include<ncurses.h>

#define IMAGE_WINDOW_WIDTH 18
#define IMAGE_WINDOW_HEIGHT 5
#define IMAGE_WIDTH 15
#define IMAGE_HEIGHT 3

#define BLACK 'b'
#define CYAN 'c'
#define WHITE 'w'

typedef struct Image
{
	WINDOW* win;
	char img[IMAGE_HEIGHT][IMAGE_WIDTH];//delete this?
	char* text;
	int textLength;
	int width;
	int height;
	int xPos, yPos;

}Image;

Image* imageCreate(int x, int y, const char* text, int textLength);
void imageDraw(Image* image);
void imageMove(Image* image, char direction, int distance);
void imageSet(Image* image, char img[IMAGE_HEIGHT][IMAGE_WIDTH]);

#endif
