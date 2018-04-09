#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int login(char *hash)
{

    printf("%s", hash);
    FILE *file;
    file = fopen("pass.txt", "r");
    char buffer[256];
    int buff_len, hash_len;
    if (file==NULL)
    {
        perror("ERROR: Couldn't open password file");
        fclose ( file );
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

         for (int i = 0; i<hash_len ; i++){
          
             if (hash[i+1] == '@'){
                 return 1;
             }
             if (buffer[i] != hash[i]){
                 return 0;
             }
            
         }
        //if (strcmp(buffer, hash) == 0)
        //{
        //    return 1;
        //}
        //else
        //{
        //    return 0;
        //}
    }
}
