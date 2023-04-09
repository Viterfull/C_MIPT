#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <locale.h>

#define SERVER_STYLE 1
#define CLIENT_STYLE 2
#define PEOPLE_STYLE 3
#define ONLY_STYLE 4


int main() {

    setlocale(LC_ALL, "");

    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, 0);
    WINDOW *win = newwin(0,0,0,0);
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);// размер окна

    box(win, '|', '-');
    WINDOW *win_chat_out_box = subwin(win, (int)(0.8*ws.ws_row), ws.ws_col-2, 1, 1);
    WINDOW *win_chat_in_box = subwin(win, (int)(0.2*ws.ws_row)-1, ws.ws_col-2, (int)(0.8*ws.ws_row)+1, 1);
    box(win_chat_in_box, '|', '-');
    box(win_chat_out_box, '|', '-');
    WINDOW *win_chat_out = subwin(win, (int)(0.8*ws.ws_row)-2, ws.ws_col-4, 2, 2);
    WINDOW *win_chat_in = subwin(win, (int)(0.2*ws.ws_row)-3, ws.ws_col-4, (int)(0.8*ws.ws_row)+2, 2);
    touchwin(win);//изменение окон
    wrefresh(win);//изменение окон ^
    scrollok(win_chat_out, TRUE);
    
    // for (int i = 0; i < 30; i++)
    // {
    //      wprintw(win_chat_out, "%d %d\n", ws.ws_col, ws.ws_row);
    // }
    char buf[20] = {0};
    for (int i = 0; i < 4; i++)
    {
        wgetstr(win_chat_in, buf);
        wclear(win_chat_in);


        wattrset(win_chat_out, COLOR_PAIR(1));
        wprintw(win_chat_out, "%s\n", buf);
        wattrset(win_chat_out, COLOR_PAIR(1));

        touchwin(win);//изменение окон
        wrefresh(win);
    }
    
    


    touchwin(win);//изменение окон
    wrefresh(win);//изменение окон ^
    delwin(win_chat_in_box);
    delwin(win_chat_out_box);
    delwin(win_chat_in);
    delwin(win_chat_out);
    delwin(win);  
    endwin();

    return 0;
}

