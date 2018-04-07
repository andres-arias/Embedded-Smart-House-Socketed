#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "./include/photo.h"
#include "./include/lights.h"
#include "./include/doors.h"

int main(int argc, char *argv[])
{
    int port_no, socket_desc, new_socket, client_len;
    struct sockaddr_in server_addr, client_addr;
    if (argc == 1)
    {
        puts("Error: No port given");
        return 0;
    }
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
        {
            perror("Error: Accepting failed");
            exit(1);
        }
        puts("Connection accepted...");
        char buffer[12];
        char status_lights[5];
        char status_doors[4];
        char *file;
        int command;
        while (read(new_socket, buffer, sizeof(buffer)) > 0)
        {
            command = atoi(buffer);
            switch (command)
            {
            case 1:
                file = take_photo();
                if (write(new_socket, file, strlen(file)) < 0)
                {
                    perror("Error: writing on socket failed.");
                    free(file);
                    exit(1);
                }
                free(file);
                break;
            case 211:
                if (light_on(1) < 0)
                {
                    perror("Error: Could not turn on light 1");
                    exit(1);
                }
                if (write(new_socket, "Turning light 1 on", 18) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            case 212:
                if (light_on(2) < 0)
                {
                    perror("Error: Could not turn on light 2");
                    exit(1);
                }
                if (write(new_socket, "Turning light 2 on", 18) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            case 213:
                if (light_on(3) < 0)
                {
                    perror("Error: Could not turn on light 3");
                    exit(1);
                }
                if (write(new_socket, "Turning light 3 on", 18) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            case 214:
                if (light_on(4) < 0)
                {
                    perror("Error: Could not turn on light 4");
                    exit(1);
                }
                if (write(new_socket, "Turning light 4 on", 18) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            case 215:
                if (light_on(5) < 0)
                {
                    perror("Error: Could not turn on light 5");
                    exit(1);
                }
                if (write(new_socket, "Turning light 5 on", 18) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            case 221:
                if (light_off(1) < 0)
                {
                    perror("Error: Could not turn off light 1");
                    exit(1);
                }
                if (write(new_socket, "Turning light 5 off", 19) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            case 222:
                if (light_off(2) < 0)
                {
                    perror("Error: Could not turn off light 2");
                    exit(1);
                }
                if (write(new_socket, "Turning light 2 off", 19) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            case 223:
                if (light_off(3) < 0)
                {
                    perror("Error: Could not turn off light 3");
                    exit(1);
                }
                if (write(new_socket, "Turning light 3 off", 19) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            case 224:
                if (light_off(4) < 0)
                {
                    perror("Error: Could not turn off light 4");
                    exit(1);
                }
                if (write(new_socket, "Turning light 4 off", 19) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            case 225:
                if (light_off(5) < 0)
                {
                    perror("Error: Could not turn off light 5");
                    exit(1);
                }
                if (write(new_socket, "Turning light 5 off", 19) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            case 23:
                for (int i = 0; i < 5; ++i)
                {
                    if (light_status(i + 1))
                    {
                        status_lights[i] = '1';
                    }
                    else
                    {
                        status_lights[i] = '0';
                    }
                }
                if (write(new_socket, status_lights, sizeof(status_lights)) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            case 3:
                for (int i = 0; i < 4; ++i)
                {
                    if (door_status(i + 1))
                    {
                        status_doors[i] = '1';
                    }
                    else
                    {
                        status_doors[i] = '0';
                    }
                }
                if (write(new_socket, status_doors, sizeof(status_doors)) < 0)
                {
                    perror("Error: writing on socket failed.");
                    exit(1);
                }
                break;
            }
        }
        puts("Client disconnected...");
        puts("----------------------");
        close(new_socket);
    }
    return 0;
}