/*REFACTOR TO CARD */
#include"image.h"
#include<stdlib.h>
#include<string.h>

Image* imageCreate(int x, int y, const char* text, int textLength)
{
	Image* newImage = (Image*)malloc(sizeof(Image));
	newImage->textLength = textLength;
	newImage->text = (char*)malloc(sizeof(char) * newImage->textLength + 1);
	//text[textLength - 1] = '\0';
	strcpy(newImage->text, text);
	newImage->width = IMAGE_WINDOW_WIDTH;
	newImage->height = textLength / IMAGE_WINDOW_WIDTH + 1;
	newImage->xPos = x;
    	newImage->yPos = y;

	//printf("%s", newImage->text);
	nodelay(newImage->win, 1); /* Not sure of this */
    	newImage->win = newwin(newImage->height, newImage->width, newImage->yPos, newImage->xPos);
    	//box(newImage->win, 0, 0);
	//wbkgd(newImage->win, COLOR_PAIR(1));

    	///refresh();
    	///wrefresh(newImage->win);
	mvwprintw(newImage->win, 0, 1, newImage->text);//why not in imageDraw??
	wnoutrefresh(newImage->win);
 
    	return newImage;
}

void imageDraw(Image* image)
{
    int i, j;
    /*for(i = 0; i < IMAGE_HEIGHT; i++)
    {
    	for(j = 0; j < IMAGE_WIDTH; j++)
	{
		if(image->img[i][j] == CYAN)
		{
			wattron(image->win, COLOR_PAIR(3));
			mvwaddch(image->win, i + 1, j + 1, image->img[i][j]);
			wattroff(image->win, COLOR_PAIR(3));
		}
		if(image->img[i][j] == BLACK)
		{
			wattron(image->win, COLOR_PAIR(2));
			mvwaddch(image->win, i + 1, j + 1, image->img[i][j]);
			wattroff(image->win, COLOR_PAIR(2));
		}
		if(image->img[i][j] == WHITE)
		{
			wattron(image->win, COLOR_PAIR(4));
			mvwaddch(image->win, i + 1, j + 1, image->img[i][j]);
			wattroff(image->win, COLOR_PAIR(4));
		}
		/*wattron(image->win, COLOR_PAIR(2));
		mvwaddch(image->win, i + 1, j + 1, image->img[i][j]);
		wattroff(image->win, COLOR_PAIR(2));
	}
	
    }*/
    wbkgd(image->win, COLOR_PAIR(4));
    mvwin(image->win, image->yPos, image->xPos);
    ///wrefresh(image->win);
    //wprintw(image->win, image->text);
    wnoutrefresh(image->win);
    //doupdate();
}

void imageMove(Image* image, char direction, int distance)
{
    if(direction == 'w')
        image->yPos -= distance;
    if(direction == 'a')
        image->xPos -= distance;
    if(direction == 's')
        image->yPos += distance;
    if(direction == 'd')
        image->xPos += distance;
}

void imageSet(Image* image, char img[IMAGE_HEIGHT][IMAGE_WIDTH])
{
	int i, j;
	for(i = 0; i < IMAGE_HEIGHT; i++)
	{
		for(j = 0; j < IMAGE_WIDTH; j++)
		{
			image->img[i][j] = img[i][j];
		}
	}
}

