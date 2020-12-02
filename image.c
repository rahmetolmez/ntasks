/*REFACTOR TO CARD */
#include"image.h"
#include<stdlib.h>

Image* imageCreate(int x, int y)
{
	Image* newImage = (Image*)malloc(sizeof(Image));

	newImage->xPos = x;
    	newImage->yPos = y;

	nodelay(newImage->win, 1); /* Not sure of this */
    	newImage->win = newwin(IMAGE_WINDOW_HEIGHT, IMAGE_WINDOW_WIDTH, newImage->yPos, newImage->xPos);
    	//box(newImage->win, 0, 0);
	//wbkgd(newImage->win, COLOR_PAIR(1));

    	///refresh();
    	///wrefresh(newImage->win);
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
    wnoutrefresh(image->win);
    doupdate();
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

