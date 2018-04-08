#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "./include/photo.h"
#include "./include/lights.h"
#include "./include/doors.h"
#include "./include/user.h"

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

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        puts("Error: No port given");
        return 0;
    }
    int port_no, socket_desc, new_socket, client_len, client_count, command, logged_in;
    struct sockaddr_in server_addr, client_addr;
    char *buffer, *status, *file;
    buffer = malloc(sizeof(char) * 64);
    status = malloc(sizeof(char) * 9);
    logged_in = 0;

    setup_lights();
    setup_doors();

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
                if (logged_in == 0)
                {
                    if (login(buffer) == 1)
                    {
                        puts("Client logged in");
                        logged_in = 1;
                        if (write(new_socket, "accepted", 8) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                    }
                    else
                    {
                        puts("Login failed");
                        if (write(new_socket, "denied", 6) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                    }
                }
                else
                {
                    command = atoi(buffer);
                    switch (command)
                    {
                    case 0:
                        puts("Nothing.");
                        break;
                    case 111:
                        puts("Take picture.");
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
                        puts("Picture taken.");
                        free(file);
                        sleep(1);
                        break;
                    case 211:
                        puts("Turn living room's lights on.");
                        light_on(1);
                        if (write(new_socket, "update", 6) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                        break;
                    case 212:
                        puts("Turn dining room's lights on.");
                        light_on(2);
                        if (write(new_socket, "update", 6) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                        break;
                    case 213:
                        puts("Turn kitchen's lights on.");
                        light_on(3);
                        if (write(new_socket, "update", 6) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                        break;
                    case 214:
                        puts("Turn master bedroom's lights on.");
                        light_on(4);
                        if (write(new_socket, "update", 6) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                        break;
                    case 215:
                        puts("Turn bedroom's lights on.");
                        light_on(5);
                        if (write(new_socket, "update", 6) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                        break;
                    case 201:
                        puts("Turn living room's lights off.");
                        light_off(1);
                        if (write(new_socket, "update", 6) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                        break;
                    case 202:
                        puts("Turn dining room's lights off.");
                        light_off(2);
                        if (write(new_socket, "update", 6) < 0)
                        {
                            perror("Error: writing on socket failed.");
                        }
                        break;
                    case 203:
                        puts("Turn kitchen's lights off.");
                        light_off(3);
                        if (write(new_socket, "update", 6) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                        break;
                    case 204:
                        puts("Turn master bedroom's lights off.");
                        light_off(4);
                        if (write(new_socket, "update", 6) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                        break;
                    case 205:
                        puts("Turn bedroom's lights off.");
                        light_off(5);
                        if (write(new_socket, "update", 6) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                        break;
                    case 333:
                        puts("Get house status.");
                        report_status(status);
                        if (write(new_socket, status, 9) < 0)
                        {
                            perror("Error: writing on socket failed.");
                            break;
                        }
                        break;
                    case 444:
                        close_lights();
                        close_doors();
                        break;
                    case 555:
                        setup_doors();
                        setup_lights();
                        break;
                    }
                    sleep(0.1);
                }
            }
        }
        puts("Client disconnected...");
        puts("----------------------");
        logged_in = 0;
        close(new_socket);
    }

    free(buffer);
    free(status);
    close_lights();
    close_doors();
    close(socket_desc);
    return 0;
}
