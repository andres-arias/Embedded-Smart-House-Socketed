#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int login(char *hash)
{
    printf("%s", hash);
    FILE *file;
    char buffer[256];
    int buff_len, hash_len;
    if ((file = fopen("password.txt", "r")) < 0)
    {
        perror("ERROR: Couldn't open password file");
        return 0;
    }
    while (fgets(buffer, sizeof(buffer), file))
    {
        buff_len = strlen(buffer);
        hash_len = strlen(hash);
        if (buffer[buff_len - 1] == '\n')
            buffer[buff_len - 1] = '\0';
        hash[hash_len - 2] = '\0';
        fclose(file);
        if (strcmp(buffer, (char *)hash) == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}