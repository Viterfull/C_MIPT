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

struct type_client{
    char *c_nickname;
    int client_socket;
    char active;
    //.....
} typedef type_client;

int server_socket;
char server_work = 1;
char server_out = 1;
int count_clients = 1;
type_client clients [100] = {0};
#define SIZE_OF_BUF 256

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

int find_client_id_for_name(type_client *data, char *name, int n_of_clients){
    for (int i = 0; i < n_of_clients; i++)
    {
        if(!strcmp(data[i].c_nickname, name)){
            return i;
        }
    }
    return -1;
}
int find_client_id_for_soc(type_client *data, int soc, int n_of_clients){
    for (int i = 0; i < n_of_clients; i++)
    {
        if(data[i].client_socket == soc){
            return i;
        }   
    }
    return -1;
}
void send_to_all_clients(type_client *data, char *s_message, int id_from, int n_of_clients){
    char message[SIZE_OF_BUF];
    sprintf(message, "%s %s", data[id_from].c_nickname, s_message);

    for (int i = 1; i < n_of_clients; i++)
    {
        if(data[i].active)
            Send(data[i].client_socket, message, SIZE_OF_BUF, 0);
    }
}



void *server_control(void *arg){
    printf("[admin]контроль сервера работает, введите команду:\n");
    while(1){
        char com[20];
        fgets(com, 20, stdin);
        if(!strcmp(com, "off\n")){
            send_to_all_clients(clients, "server off\n", 0, count_clients);
            for (int i = 0; i < count_clients; i++)
            {
                free(clients[i].c_nickname);
            }
            printf("[admin]сервер завершил работу\n");
            shutdown(server_socket, SHUT_RDWR);
            close(server_socket);
            server_work = 0;
            return 0;
        } else if(!strcmp(com, "info on\n")){
            server_out = 1;
        }else if(!strcmp(com, "info off\n")){
            server_out = 0;
        }
    }
    
    return 0;
}

// сообщения серверу типа:
//     c:name
//     q:0
//     s:message
//     r:0

void *service_client(void *arg){
    int id_client;
    int client_socket = (*(int*)(arg));
    server_out == 1?printf("[server] обработка клиента(soc = %d)\n", client_socket):0;
    while(server_work){
        char com[2];
        int byt = recv(client_socket, com, 2, 0);
        server_out == 1?printf("[server] принята команда длиной в %d байт: %c\n", byt, com[0]):0;
        char buf[SIZE_OF_BUF] = {0};
        char buf_for_message[SIZE_OF_BUF] = {0};
        switch (com[0])
        {
            case 'c':
                recv(client_socket, &buf, SIZE_OF_BUF, 0);
                id_client = find_client_id_for_name(clients, buf, count_clients);
                if(id_client == -1){
                    clients[count_clients].c_nickname = strcpy(calloc(SIZE_OF_BUF, 1), buf);
                    clients[count_clients].active = 1;
                    clients[count_clients].client_socket = client_socket;
                    server_out == 1?printf("[server] новый клиетн(name = %s;socket = %d)\n", clients[count_clients].c_nickname, clients[count_clients].client_socket):0;
                    sprintf(buf_for_message, "new client (name = %s)", clients[count_clients].c_nickname);
                    send_to_all_clients(clients, buf_for_message, 0, count_clients+1);
                    sprintf(buf_for_message, "n of clients %d", count_clients);
                    send_to_all_clients(clients, buf_for_message, 0, count_clients+1);
                    count_clients++;
                    //отослать всем инфу о подключении
                }else{
                    clients[id_client].active = 1;
                    clients[id_client].client_socket = client_socket;
                    server_out == 1?printf("[server] переподключение(name = %s;socket = %d)\n", clients[id_client].c_nickname, clients[id_client].client_socket):0;
                    sprintf(buf_for_message, "reconnect client(name = %s)", clients[id_client].c_nickname);
                    send_to_all_clients(clients, buf_for_message, 0, count_clients);
                    //отослать инфу о переподключении
                }
                break;
            case 'q':
                id_client = find_client_id_for_soc(clients, client_socket, count_clients);
                clients[id_client].active = 0;
                server_out == 1?printf("[server] отключение клиента(name = %s;socket = %d) и закрытие сокета\n", clients[id_client].c_nickname, clients[id_client].client_socket):0;
                shutdown(client_socket, SHUT_RDWR);
                close(client_socket);
                sprintf(buf_for_message, "unconnect client(name = %s)", clients[id_client].c_nickname);
                send_to_all_clients(clients, buf_for_message, 0, count_clients);
                //отослать инфу о отключении
                return 0;
            case 'm':
                recv(client_socket, &buf, SIZE_OF_BUF, 0);
                id_client = find_client_id_for_soc(clients, client_socket, count_clients);
                send_to_all_clients(clients, buf, id_client, count_clients);
                server_out == 1?printf("[server] отослал сообщение от клиента(name = %s;socket = %d) для всех:\n*****************************************************\n%s\n*****************************************************\n", clients[id_client].c_nickname, clients[id_client].client_socket, buf):0;
                break;
            default:
                printf("[server]!неопознанная команда серверу!\n");
                break;
        }
    }
}

int main(int n_arg, char* arg[]){
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    char ip[20];
    int port;
    struct sockaddr_in server_address = {0};
    do {
        // perror("error to start server: ");
        printf("Введите ipv4 адрес: ");
        scanf("%s", ip);
        server_address.sin_addr.s_addr = inet_addr(ip);
        printf("Введите порт: ");
        scanf("%d", &port);
        server_address.sin_port = htons(port);
    }while(bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1);

    listen(server_socket, 1000);
    clients[0].active = 1;
    clients[0].client_socket = server_socket;
    clients[0].c_nickname = strcpy(calloc(SIZE_OF_BUF, 1), "server");

    pthread_t th_id;
    int create = pthread_create(&th_id, NULL, server_control, NULL);

    int client_socket;
    while (server_work == 1)
    {
        if((client_socket = accept(server_socket, NULL, NULL)) == -1) break;
        pthread_create(&th_id, NULL, service_client, (void*)(&client_socket));      
    }

	return 0;
}