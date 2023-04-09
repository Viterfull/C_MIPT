#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>     
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ncurses.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <locale.h>

#define SIZE_OF_BUF 256

#define SERVER_STYLE 1
#define CLIENT_STYLE 2
#define PEOPLE_STYLE 3

WINDOW *win, *win_chat_out_box, *win_chat_in_box, *win_chat_out, *win_chat_in; 
char name[SIZE_OF_BUF];

int Send(int socket, char *message, int len, int flag){
    int total = 0;
    int n;
    while (total < len)
    {
        n = send(socket, message+total, len-total, flag);
        if(n==-1) break;
        total+=n;
    }
    return (n==-1?-1:total);
}

void print_with_style(char* mes, int style){
    wattrset(win_chat_out, COLOR_PAIR(style));
    wprintw(win_chat_out, "%s", mes);
    wattrset(win_chat_out, COLOR_PAIR(style));
    touchwin(win);//изменение окон
    wrefresh(win);//изменение окон ^
}
void input_in(char* str){
    touchwin(win);//изменение окон
    wrefresh(win);//изменение окон ^
    wgetstr(win_chat_in, str);
    wclear(win_chat_in);
    touchwin(win);//изменение окон
    wrefresh(win);//изменение окон ^
}
char server_work = 1;
void *server_out(void *arg){
    int network_socket = (*(int*)(arg));
    char mes[SIZE_OF_BUF];
    char name_from[SIZE_OF_BUF];
    char *mes_text;
    sleep(1);
    while (server_work)
    {
        recv(network_socket, &mes, SIZE_OF_BUF, 0);
        sscanf(mes, "%s", name_from);
        mes_text = mes + (int)strlen(name_from)+1;
        if(!strcmp(name_from, name)){
            print_with_style(name_from, CLIENT_STYLE);
            print_with_style(":", CLIENT_STYLE);
            print_with_style(mes_text, 0);
            print_with_style("\n", 0);
        } else if(!strcmp(name_from, "server")){
            if (!strcmp(mes_text, "server off\n")){
                server_work = 0;
                sleep(3);
                return 0;
            }
            print_with_style(name_from, SERVER_STYLE);
            print_with_style(":", SERVER_STYLE);
            print_with_style(mes_text, SERVER_STYLE);
            print_with_style("\n", 0);
        } else{
            print_with_style(name_from, PEOPLE_STYLE);
            print_with_style(":", PEOPLE_STYLE);
            print_with_style(mes_text, 0);
            print_with_style("\n", 0);
        }
        // printf("%s", mes);
        
    }
    return 0;
}
void *server_in(void *arg){
    int network_socket = (*(int*)(arg));
    char mes[SIZE_OF_BUF];
    touchwin(win);//изменение окон
    wrefresh(win);//изменение окон ^ч
    sleep(1);
    while (server_work)
    {
        input_in(mes);
        if (!strcmp(mes, "\n")) continue;
        if (!strcmp(mes, "!q")){
            Send(network_socket, "q", 2, 0);
            print_with_style("disconnect\n", SERVER_STYLE);
            // printf("\033[31m disconnect\033[0m");
            server_work = 0;
            sleep(3);
            return 0;
        }else{
        Send(network_socket, "m", 2, 0);
        Send(network_socket, mes, 256, 0);
        }
    }
    return 0;
}

int main() {
    initscr();
    start_color();
    init_pair(SERVER_STYLE, COLOR_YELLOW, 0);
    init_pair(CLIENT_STYLE, COLOR_BLUE, 0);
    init_pair(PEOPLE_STYLE, COLOR_GREEN, 0);
    win = newwin(0,0,0,0);
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);// размер окна
    box(win, '|', '-');
    win_chat_out_box = subwin(win, (int)(0.8*ws.ws_row), ws.ws_col-2, 1, 1);
    win_chat_in_box = subwin(win, (int)(0.2*ws.ws_row)-1, ws.ws_col-2, (int)(0.8*ws.ws_row)+1, 1);
    box(win_chat_in_box, '|', '-');
    box(win_chat_out_box, '|', '-');
    win_chat_out = subwin(win, (int)(0.8*ws.ws_row)-2, ws.ws_col-4, 2, 2);
    win_chat_in = subwin(win, (int)(0.2*ws.ws_row)-3, ws.ws_col-4, (int)(0.8*ws.ws_row)+2, 2);
    scrollok(win_chat_out, TRUE);

	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
    print_with_style("inpyt ipv4\n", SERVER_STYLE);
    char ip[20];
    input_in(ip);
    print_with_style("inpyt port\n", SERVER_STYLE);
    char port_s[20];
    input_in(port_s);
    int port = atoi(port_s);

    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(ip);
    server_address.sin_port = htons(port);

    if (connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1){
		while (connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1)
        {
		    print_with_style("There was an error making a connection to the remote socket \n", SERVER_STYLE);
            print_with_style("inpyt ipv4\n", SERVER_STYLE);
            char ip[20];
            input_in(ip);
            print_with_style("inpyt port\n", SERVER_STYLE);
            char port_s[20];
            input_in(port_s);
            int port = atoi(port_s);
            server_address.sin_addr.s_addr = inet_addr(ip);
            server_address.sin_port = htons(port);
        }
    }
    print_with_style("(connection(for exit inpyt: !q))input name\n", SERVER_STYLE);

    input_in(name);
	Send(network_socket, "c", 2, 0);
    Send(network_socket, name, 256, 0);
    sleep(0.5);
    print_with_style("connect with name: ", SERVER_STYLE);
    print_with_style(name, SERVER_STYLE);
    print_with_style("\n", SERVER_STYLE);

    pthread_t th_id;
    pthread_create(&th_id, NULL, server_in, (void*)(&network_socket));
    pthread_create(&th_id, NULL, server_out, (void*)(&network_socket));
    touchwin(win);//изменение окон
    wrefresh(win);//изменение окон ^
    while (server_work){
    }
    
    // printf("отослано %ld байт\n",Send(network_socket, "m", 2, 0));
    // printf("отослано %ld байт\n",Send(network_socket, mes, 256, 0));
	// printf("отослано %ld байт\n",Send(network_socket, "q", 2, 0));
	// recv(network_socket, &server_response, sizeof(server_response), 0);

	close(network_socket);
    delwin(win_chat_in_box);
    delwin(win_chat_out_box);
    delwin(win_chat_in);
    delwin(win_chat_out);
    delwin(win);  
    endwin();
	return 0;
}