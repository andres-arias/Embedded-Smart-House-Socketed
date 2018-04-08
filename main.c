#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "./include/photo.h"
#include "./include/lights.h"
#include "./include/doors.h"

void report_status(char *status)
{
    for (int i = 0; i < 5; ++i)
    {
        if (light_status(i + 1) == 1)
        {
            status[i] = '1';
        }
        else
        {
            status[i] = '0';
        }
    }
    for (int i = 5; i < 9; ++i)
    {
        if (door_status(i + 1) == 1)
        {
            status[i] = '1';
        }
        else
        {
            status[i] = '0';
        }
    }
}

int check_changes(char *status)
{
    for (int i = 0; i < 5; ++i)
    {
        if (status[i] != light_status(i + 1))
            return 1;
        else
            return 0;
    }
    for (int i = 0; i < 4; ++i)
    {
        if (status[i] != door_status(i + 1))
            return 1;
        else
            return 0;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        puts("Error: No port given");
        return 0;
    }
    int port_no, socket_desc, new_socket, client_len, client_count, command;
    struct sockaddr_in server_addr, client_addr;
    char *buffer, *status, *file;
    buffer = malloc(sizeof(char) * 3);
    status = malloc(sizeof(char) * 9);

    port_no = atoi(argv[1]);

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
    server_addr.sin_port = htons(port_no);

    if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error: Bind failed");
        exit(1);
    }
    puts("Bind successful");

    while (1)
    {
        listen(socket_desc, 5);
        puts("Awaiting incoming connections...");
        client_len = sizeof(client_addr);

        new_socket = accept(socket_desc, (struct sockaddr *)&client_addr, &client_len);
        if (new_socket < 0)
            perror("Error: Accepting failed");
        else
        {
            puts("Connection accepted...");
            if (write(new_socket, "ok", 2) < 0)
            {
                perror("Error: writing on socket failed.");
            }

            while (read(new_socket, buffer, sizeof(buffer)) > 0)
            {
                if (check_changes(status) == 1)
                {
                    report_status(status);
                    if (write(new_socket, status, 9) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        break;
                    }
                }
                command = atoi(buffer);
                printf("%d\n", command);
                switch (command)
                {
                case 1:
                    file = take_photo();
                    if (write(new_socket, "istr", 4) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        free(file);
                        break;
                    }
                    if (write(new_socket, file, strlen(file)) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        free(file);
                        break;
                    }
                    if (write(new_socket, "iend", 4) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        free(file);
                        break;
                    }
                    free(file);
                    break;
                case 211:
                    if (light_on(1) < 0)
                    {
                        perror("ERROR: Couldn't turn light 1 on");
                        break;
                    }
                    if (write(new_socket, "Turning light 1 on", 18) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        break;
                    }
                    break;
                case 212:
                    if (light_on(2) < 0)
                    {
                        perror("ERROR: Couldn't turn light 1 on");
                        break;
                    }
                    if (write(new_socket, "Turning light 2 on", 18) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        break;
                    }
                    break;
                case 213:
                    if (light_on(2) < 0)
                    {
                        perror("ERROR: Couldn't turn light 1 on");
                        break;
                    }
                    if (write(new_socket, "Turning light 3 on", 18) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        break;
                    }
                    break;
                case 214:
                    if (light_on(4) < 0)
                    {
                        perror("ERROR: Couldn't turn light 1 on");
                        break;
                    }
                    if (write(new_socket, "Turning light 4 on", 18) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        break;
                    }
                    break;
                case 215:
                    if (light_on(5) < 0)
                    {
                        perror("ERROR: Couldn't turn light 1 on");
                        break;
                    }
                    if (write(new_socket, "Turning light 5 on", 18) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        break;
                    }
                    break;
                case 201:
                    if (light_off(1) < 0)
                    {
                        perror("ERROR: Couldn't turn light 1 off");
                        break;
                    }
                    if (write(new_socket, "Turning light 5 off", 19) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        break;
                    }
                    break;
                case 202:
                    if (light_off(2) < 0)
                    {
                        perror("ERROR: Couldn't turn light 1 off");
                        break;
                    }
                    if (write(new_socket, "Turning light 2 off", 19) < 0)
                    {
                        perror("Error: writing on socket failed.");
                    }
                    break;
                case 203:
                    if (light_off(3) < 0)
                    {
                        perror("ERROR: Couldn't turn light 1 off");
                        break;
                    }
                    if (write(new_socket, "Turning light 3 off", 19) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        break;
                    }
                    break;
                case 204:
                    if (light_off(4) < 0)
                    {
                        perror("ERROR: Couldn't turn light 1 off");
                        break;
                    }
                    if (write(new_socket, "Turning light 4 off", 19) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        break;
                    }
                    break;
                case 205:
                    if (light_off(5) < 0)
                    {
                        perror("ERROR: Couldn't turn light 1 off");
                        break;
                    }
                    if (write(new_socket, "Turning light 5 off", 19) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        break;
                    }
                    break;
                case 3:
                    report_status(status);
                    if (write(new_socket, status, 9) < 0)
                    {
                        perror("Error: writing on socket failed.");
                        break;
                    }
                    break;
                }
            }
        }
        puts("Client disconnected...");
        puts("----------------------");
        close(new_socket);
    }

    free(buffer);
    free(status);
    close(socket_desc);
    return 0;
}