#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CHUNK_SIZE 512

int take_photo()
{
    char *file_path = "/home/andres/Documents/Embebidos/Socket_Server/image.jpeg";
    if (system("fswebcam -r 1280x720 -d /dev/video0 image.jpeg -S 2") < 0)
    {
        perror("ERROR: Couldn't open camera");
        return -1;
    }
    else
    {
        return 0;
    }
}

