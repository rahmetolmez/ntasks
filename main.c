#include"list.h"
#include<ncurses.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define COLOR_OFFSET 3.92

WINDOW* win;
int changeListOfCard(List* from, int cardIndex, List* to);

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
	WINDOW* homeWin = newwin(LINES, COLS, 0 + 3, 0);
    scrollok(homeWin, TRUE);
	//wattron(newList->win, COLOR_PAIR(5));
	//box(homeWin, 0, 0);
	//wattroff(newList->win, COLOR_PAIR(5));

	//wbkgd(newList->win, COLOR_PAIR(1));
	wnoutrefresh(homeWin);
	doupdate();

	///HEADER///
	WINDOW* headerWin = newwin(3, COLS - 2, 1, 1);
    //wborder(headerWin, '|', '|', '-', '-', '-', '-', '-', '-');
	//box(headerWin, 0, 0);
    wattrset(headerWin, A_BOLD);
    mvwprintw(headerWin, 1, (COLS - 2) / 2 - 6, "nTasks");
    //mvwprintw(headerWin, 1, COLS - 21, "tribow company (c)");
	wnoutrefresh(headerWin);
	doupdate();
    /////////////////////////////////////////


    //scrollok(win, TRUE);
    char * text;
    init_color(COLOR_RED, 245 * COLOR_OFFSET, 164 * COLOR_OFFSET, 71 * COLOR_OFFSET);
    init_color(COLOR_MAGENTA, 1000 * 89 / 255, 1000 * 4 / 255, 1000 * 68 / 255);
    
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
    
    init_color(COLOR_CYAN, 1000 * 219 / 255, 1000 * 117 / 255, 1000 * 0 / 255);
    wbkgd(headerWin, COLOR_PAIR(8));
    //printf("%d - %d\n", COLORS, COLOR_PAIRS);
    //init_color(COLOR_CYAN, 1000 * 63 / 255, 1000 * 94 / 255, 1000 * 145 / 255);

    List* list = listCreate("      Backlog", "  + Add list (c)", 1, 5);
    List* list2 = listCreate("      To Do", "  + Add list (c)", LIST_WIDTH + 2, 5);
    List* list3 = listCreate("   In Progress", "  + Add list (c)", 2 * LIST_WIDTH + 3, 5);

    List* list4 = listCreate(" Taking Too Long", "  + Add list (c)",3 * LIST_WIDTH + 4, 5);
    List* list5 = listCreate("       Done", "  + Add list (c)", 4 * LIST_WIDTH + 5, 5);
    List* list6 = listCreate("      Notes", "  + Add list (c)", 5 * LIST_WIDTH + 6, 5);
    List* list7 = listCreate("      Ideas", "  + Add list (c)", 6 * LIST_WIDTH + 7, 5);

    List* currentList = list;
    listChangeColor(list, 3);
    List* deck[7];
    deck[0] = list;
    deck[1] = list2;
    deck[2] = list3;
    deck[3] = list4;
    deck[4] = list5;
    deck[5] = list6;
    deck[6] = list7;
    int deckSize = 7;
    char whiteBg[3][14] = {
	    		{'c', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
   			{'c', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
			{'c', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'}
    			};

    //listAddCard(list);
    //cardSet(list->img, whiteBg);
    //cardSet(list->cards[0], whiteBg);

    int listCounter = 1;
    int selectedCard = -1;
    int listNum = 0;
    int ch = 'n';
    while(ch != 'q')
    {

	if(ch != ERR)
	{
		listChangeColor(list5, 6);
		//clear();
		erase();
	}

        ch = getch();

        switch(ch)
        {
            case 'w':
	    case KEY_UP:
                listMove(currentList, 'w', currentList->height / 2);
                break;
            case 'a':
	    case KEY_LEFT:
                listMove(currentList, 'a', currentList->width);
                break;
            case 's':
	    case KEY_DOWN:
                listMove(currentList, 's', currentList->height / 2);
                break;
            case 'd':
	    case KEY_RIGHT:
                listMove(currentList, 'd', currentList->width);
                break;
	    case 'c':
		  echo();
		  text = (char*)malloc(200);
		  wmove(homeWin, LINES - 10, currentList->xPos);
		  waddch(homeWin, '>');
		  wgetnstr(homeWin, text, 100);
		  //printf("text: %s, size %ld", text, strlen(text));
		  listAddCard(currentList, text, strlen(text));
		  noecho();
		  werase(homeWin);
		  doupdate();
		  break;
	    case 't':
		//getstr(currentList->cards[0]->text);
		//mvprintw(0, 39, "%s", currentList->cards[0]->text);
		//wnoutrefresh(win);
		  break;
	    case ' ':
		  listChangeColor(currentList, 1);
          if(selectedCard > -1)
            listChangeCardColor(currentList, selectedCard, 4);
		  currentList = deck[listCounter];
		  listChangeColor(currentList, 3);
		  listCounter++;
          selectedCard = -1;
		  break;
        case '\t':
            if(currentList->cardCount > 0)
            {
                if(selectedCard > -1)
                    listChangeCardColor(currentList, selectedCard, 4);
                selectedCard++;
                selectedCard %= currentList->cardCount;
                listChangeCardColor(currentList, selectedCard, 1);
            }
            break;
        case 'u':
            echo();
            wmove(homeWin, LINES - 10, currentList->xPos);
            waddch(homeWin, '>');
            listNum = wgetch(homeWin);
            noecho();
            werase(homeWin);
            doupdate();
            listNum %= deckSize;
            if(changeListOfCard(currentList, selectedCard, deck[listNum]) == 0)
            {
                selectedCard -= 1;
                //currentList = deck[listNum];
                //selectedCard = currentList->cardCount - 1;
            }
        default:
            break;

	    
        }
	
	if(listCounter == 7)
		listCounter = 0;
    //if(selectedCard == currentList->cardCount)
    //    selectedCard = 0;

	mvwin(homeWin, 0, 0);
	//box(homeWin, 0, 0);
	wnoutrefresh(homeWin);
	mvwin(headerWin, 1, 1);
	//box(headerWin, 0, 0);
	wnoutrefresh(headerWin);
    	for(int i = 0; i < 7; i++)
		listDraw(deck[i]);
	
	doupdate();
	//listDraw(list);
       	//listDraw(list2);
        //listDraw(list3);

	//listDraw(list4);
	//listDraw(list5);
	//listDraw(list6);
	//listDraw(list7);
        usleep(2000);
    }

    //todo: do all freeing
    delwin(list->win);
    delwin(list2->win);
    delwin(list3->win);

    //delwin(list->img->win);



    endwin();
    
    return 0;
}

int changeListOfCard(List* from, int cardIndex, List* to)
{
    if(from->cardCount <= 0 || cardIndex < 0 || (from == to))
        return -1;
    listAddCard(to, from->cards[cardIndex]->text, strlen(from->cards[cardIndex]->text));
    listRemoveCard(from, cardIndex);
    //werase(win);
    //doupdate();
    return 0;
}