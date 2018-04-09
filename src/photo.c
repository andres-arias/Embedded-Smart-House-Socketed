#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

#include "../include/base64.h"

#define CHUNK_SIZE 512

char *convert_file()
{
    FILE *file;
    unsigned char *file_clean;
    char *file_converted;

    file = fopen("image.jpg", "rb");
    if (!file)
    {
        perror("ERROR: No such file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    size_t file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    file_clean = (char *)malloc(file_length + 1);
    fread(file_clean, file_length, 1, file);
    size_t output_length = 0;
    file_converted = base64_encode(file_clean, file_length, &output_length);
    fclose(file);
    return file_converted;
}

char *take_photo()
{
    if (system("fswebcam -r 1280x720 -d /dev/video0 image.jpg -S 3") < 0)
    {
        perror("ERROR: Couldn't open camera");
        exit(1);
    }
    else
    {
        return convert_file();
    }
}
