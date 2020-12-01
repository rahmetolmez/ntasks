#include"card.h"
#include<ncurses.h>
#include<unistd.h>
#include<stdio.h>

#define COLOR_OFFSET 3.92

WINDOW* win;

int main(int argc, char** argv)
{
   
    win = initscr();
    curs_set(0);
    keypad(stdscr, 1);
    cbreak();
    noecho();
    nodelay(win, 1);
    start_color();
    clear();
    refresh();

    
    init_color(COLOR_RED, 245 * COLOR_OFFSET, 164 * COLOR_OFFSET, 71 * COLOR_OFFSET);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    //init_pair(2, COLOR_BLACK, COLOR_BLACK);
    //init_pair(3, COLOR_CYAN, COLOR_CYAN);
    //init_pair(4, COLOR_WHITE, COLOR_WHITE);

    //wbkgd(win, COLOR_PAIR(1));

    Card* card = cardCreate("      Backlog", "  + Add card (c)", 1, 1);
    Card* card2 = cardCreate("     To Do", "  + Add card (c)", CARD_WIDTH + 1, 1);
    Card* card3 = cardCreate("     In Progress", "    tribow (c)", 2 * CARD_WIDTH + 1, 1);

    Card* card4 = cardCreate(" Taking Too Long", "    ",3 * CARD_WIDTH + 1, 1);
    Card* card5 = cardCreate("     Done", "    ", 4 * CARD_WIDTH + 1, 1);
    Card* card6 = cardCreate("     Notes", "    ", 5 * CARD_WIDTH + 1, 1);
    Card* card7 = cardCreate("     Ideas", "    ", 6 * CARD_WIDTH + 1, 1);

    Card* currentCard = card;

    Card* deck[7];
    deck[0] = card;
    deck[1] = card2;
    deck[2] = card3;
    deck[3] = card4;
    deck[4] = card5;
    deck[5] = card6;
    deck[6] = card7;

    char blui[8][16] = {
	    		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'w', 'w', 'w', 'w', 'm', 'm', 'm', 'm'},
   			{'m', 'm', 'w', 'w', 'm', 'm', 'w', 'w', 'c', 'c', 'w', 'w', 'w', 'w', 'm', 'm'},
			{'w', 'w', 'm', 'm', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    			{'w', 'w', 'm', 'm', 'm', 'm', 'w', 'w', 'm', 'm', 'm', 'm', 'w', 'w', 'w', 'w'},
			{'w', 'w', 'w', 'w', 'w', 'w', 'm', 'm', 'm', 'm', 'w', 'w', 'w', 'w', 'w', 'w'},
			{'m', 'm', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'm', 'm'},
			{'m', 'm', 'm', 'm', 'm', 'm', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'm', 'm'},
			{'m', 'm', 'm', 'm', 'w', 'w', 'm', 'm', 'm', 'm', 'w', 'w', 'm', 'm', 'm', 'm'}
    			};

    imageSet(card->img, blui);

    int cardCounter = 1;

    char ch = 'n';
    while(ch != 'q')
    {
        
	//erase();
        ch = getch();
	
        switch(ch)
        {
            case 'w':
                cardMove(currentCard, 'w', 10);
                break;
            case 'a':
                cardMove(currentCard, 'a', 20);
                break;
            case 's':
                cardMove(currentCard, 's', 10);
                break;
            case 'd':
                cardMove(currentCard, 'd', 20);
                break;
	    case ' ':
		currentCard = deck[cardCounter];
		cardCounter++;
		break;
            default:
                break;

	    
        }
	
	if(cardCounter == 7)
		cardCounter = 0;

	if(ch != ERR)
		clear();
    	for(int i = 0; i < 7; i++)
		cardDraw(deck[i]);
	
	doupdate();
	//cardDraw(card);
       	//cardDraw(card2);
        //cardDraw(card3);

	//cardDraw(card4);
	//cardDraw(card5);
	//cardDraw(card6);
	//cardDraw(card7);
        usleep(45000);
    }

    delwin(card->win);
    delwin(card2->win);
    delwin(card3->win);

    delwin(card->img->win);



    endwin();
    
    return 0;
}
