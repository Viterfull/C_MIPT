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
#include <arpa/inet.h>

int main(int n_arg, char* arg[]){
    char server_message[256];
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9004);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    struct sockaddr_in client_address = {0};
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(9002);
    client_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    

    bind(client_socket, &client_address, sizeof(client_address));

    recvfrom(client_socket, server_message, sizeof(server_message), 0,
                &(server_address), sizeof(server_address));
    printf("ko mne prishlo messege: %s\n", server_message);

	return 0;
}



// Сокеты(розетка) - конечная точка сетевых коммуникаций:
//     взаимодействия по сети
//     характеризиется дискриптором
//     создание сокета: socket()
//     -- ifconfig - все сетевые интерфейсы


