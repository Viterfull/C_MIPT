#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>     
#include <sys/socket.h>
#include <netinet/in.h>

int main(int n_arg, char* arg[]){
    char server_message[256] = "You have reached the server!";
    char client_message[256];
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    // server_address.sin_addr.s_addr = 0;

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    
    listen(server_socket, 1);
    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        recv(client_socket, &client_message, sizeof(client_message), 0);
        printf("\nclient send to me: %s\n", client_message);
        send(client_socket, server_message, sizeof(server_message), 0);
        close(client_socket);
    }
    
    

    close(server_socket);

	return 0;
}



// Сокеты(розетка) - конечная точка сетевых коммуникаций:
//     взаимодействия по сети
//     характеризиется дискриптором
//     создание сокета: socket()
//     -- ifconfig - все сетевые интерфейсы


