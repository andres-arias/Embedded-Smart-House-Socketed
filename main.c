#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "./include/photo.h"

int main(int argc, char *argv[])
{
    int socket_desc, new_socket, port_no, client_len;
    struct sockaddr_in server_addr, client_addr;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0)
    {
        puts("Could not create socket.");
        exit(1);
    }
    puts("Socket created");

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);

    if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error: Bind failed");
        exit(1);
    }
    puts("Bind successful");

    listen(socket_desc, 5);
    puts("Awaiting incoming connections...");
    client_len = sizeof(client_addr);

    new_socket = accept(socket_desc, (struct sockaddr *)&client_addr, &client_len);
    if (new_socket < 0)
    {
        perror("Error: Accepting failed");
        exit(1);
    }
    puts("Connection accepted...");
    char buffer[12];
    int command;
    while (read(new_socket, buffer, sizeof(buffer)) > 0)
    {
        command = atoi(buffer);
        printf("%d\n", command);
        switch (command)
        {
        case 1:
            if (write(new_socket, "Taking picture...", 18) < 0)
            {
                perror("Error: writing on socket failed.");
                exit(1);
            }
            if (take_photo() < 0) {
                perror("Error: Couldn't open camera");
            }
        }
    }
    puts("Client disconnected...");
    close(new_socket);
    return 0;
}