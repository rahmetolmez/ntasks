#include"card.h"
#include<ncurses.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define COLOR_OFFSET 3.92

WINDOW* win;
const char * getString();

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

    ///////////HOME HUD/////////////////////
	WINDOW* homeWin = newwin(LINES, COLS, 0, 0);
	//wattron(newCard->win, COLOR_PAIR(5));
	//box(homeWin, 0, 0);
	//wattroff(newCard->win, COLOR_PAIR(5));

	//wbkgd(newCard->win, COLOR_PAIR(1));
	wnoutrefresh(homeWin);
	doupdate();

	///HEADER///
	WINDOW* headerWin = newwin(3, COLS - 2, 1, 1);
	//box(headerWin, 0, 0);
	wnoutrefresh(headerWin);
	doupdate();
    /////////////////////////////////////////


    //scrollok(win, TRUE);
    char * text;
    init_color(COLOR_RED, 245 * COLOR_OFFSET, 164 * COLOR_OFFSET, 71 * COLOR_OFFSET);
    if(can_change_color() && COLORS >= 16)
	init_color(15, 1000, 1000, 1000);
    if(COLORS >= 16){
	init_pair(4, COLOR_BLACK, 15);
    }
    else
	init_pair(4, COLOR_BLACK, COLOR_WHITE);

    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    init_pair(6, COLOR_BLACK, COLOR_GREEN);
    init_pair(7, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(8, COLOR_WHITE, COLOR_CYAN);
    ///init_pair(4, COLOR_WHITE, COLOR_WHITE);

    wbkgd(homeWin, COLOR_PAIR(7));
    wbkgd(headerWin, COLOR_PAIR(8));

    Card* card = cardCreate("      Backlog", "  + Add card (c)", 1, 5);
    Card* card2 = cardCreate("      To Do", "  + Add card (c)", CARD_WIDTH + 2, 5);
    Card* card3 = cardCreate("   In Progress", "  + Add card (c)", 2 * CARD_WIDTH + 3, 5);

    Card* card4 = cardCreate(" Taking Too Long", "  + Add card (c)",3 * CARD_WIDTH + 4, 5);
    Card* card5 = cardCreate("       Done", "  + Add card (c)", 4 * CARD_WIDTH + 5, 5);
    Card* card6 = cardCreate("      Notes", "  + Add card (c)", 5 * CARD_WIDTH + 6, 5);
    Card* card7 = cardCreate("      Ideas", "  + Add card (c)", 6 * CARD_WIDTH + 7, 5);

    Card* currentCard = card;
    cardChangeColor(card, 3);
    Card* deck[7];
    deck[0] = card;
    deck[1] = card2;
    deck[2] = card3;
    deck[3] = card4;
    deck[4] = card5;
    deck[5] = card6;
    deck[6] = card7;

    char whiteBg[3][14] = {
	    		{'c', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
   			{'c', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
			{'c', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'}
    			};

    //cardAddImage(card);
    //imageSet(card->img, whiteBg);
    //imageSet(card->images[0], whiteBg);

    int cardCounter = 1;

    int ch = 'n';
    while(ch != 'q')
    {

	if(ch != ERR)
	{
		cardChangeColor(card5, 6);
		//clear();
		erase();
	}

        ch = getch();

        switch(ch)
        {
            case 'w':
	    case KEY_UP:
                cardMove(currentCard, 'w', currentCard->height / 2);
                break;
            case 'a':
	    case KEY_LEFT:
                cardMove(currentCard, 'a', currentCard->width);
                break;
            case 's':
	    case KEY_DOWN:
                cardMove(currentCard, 's', currentCard->height / 2);
                break;
            case 'd':
	    case KEY_RIGHT:
                cardMove(currentCard, 'd', currentCard->width);
                break;
	    case 'c':
		echo();
		text = (char*)malloc(200);
		wmove(homeWin, LINES - 10, currentCard->xPos);
		waddch(homeWin, '>');
		wgetnstr(homeWin, text, 100);
		//printf("text: %s, size %ld", text, strlen(text));
		cardAddImage(currentCard, text, strlen(text));
		noecho();
		werase(homeWin);
		doupdate();
		break;
	    case 't':
		//getstr(currentCard->images[0]->text);
		//mvprintw(0, 39, "%s", currentCard->images[0]->text);
		//wnoutrefresh(win);
		break;
	    case ' ':
		cardChangeColor(currentCard, 1);
		currentCard = deck[cardCounter];
		cardChangeColor(currentCard, 3);
		cardCounter++;
		break;
            default:
                break;

	    
        }
	
	if(cardCounter == 7)
		cardCounter = 0;

	mvwin(homeWin, 0, 0);
	//box(homeWin, 0, 0);
	wnoutrefresh(homeWin);
	mvwin(headerWin, 1, 1);
	//box(headerWin, 0, 0);
	wnoutrefresh(headerWin);
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
        usleep(2000);
    }

    delwin(card->win);
    delwin(card2->win);
    delwin(card3->win);

    //delwin(card->img->win);



    endwin();
    
    return 0;
}

const char * getString()
{
    char* input = (char*)malloc(sizeof(char) * 200);

    // let the terminal do the line editing
    nocbreak();
    echo();

    // this reads from buffer after <ENTER>, not "raw" 
    // so any backspacing etc. has already been taken care of
    int ch = getch();
    input[0] = '\0';
    char chr = (char)ch;
    int i = 0;
    while ( ch != '\n' )
    {
	strncat(input, &chr, i + 1);
	input[i + 1] = '\0';
        //input[i] = ch;
        ch = getch();
	chr = (char)ch;
	i++;
    }

    // restore your cbreak / echo settings here
    printf("%s", input);
    printf("helllo");
    return input;
}
