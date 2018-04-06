#include <stdlib.h>
#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write

int main(int argc, char *argv[])
{
    int socket_desc, new_socket, port_no, client_len;
    struct sockaddr_in server_addr;
    char server_reply[256];

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0)
    {
        puts("Could not create socket.");
        exit(1);
    }
    puts("Socket created");

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);

    if (connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error: Connect failed.");
        return 1;
    }
    puts("Connection established");
    int exit_flag = 0;
    char buffer[12];
    int command;
    while (1)
    {
        printf("Enter command: ");
        bzero(buffer, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);
        command = atoi(buffer);
        if (command == 0)
        {
            puts("Exiting...");
            break;
        }
        if (send(socket_desc, buffer, strlen(buffer), 0) < 0)
        {
            perror("Send failed");
            return 1;
        }
        if (read(socket_desc, server_reply, sizeof(server_reply)) < 0)
        {
            perror("recv failed");
        }
        puts("Server message:");
        puts(server_reply);
    }
    puts("Connection closed.");
    close(socket_desc);
    return 0;
}