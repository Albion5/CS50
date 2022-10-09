#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define BLOCK_SIZE 512

typedef uint8_t BYTE;
int check_JPEG(BYTE buffer[BLOCK_SIZE]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Couldn't open the file");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    int n = 0;
    char file_name[8];
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //printf("%d ", n);
        if (check_JPEG(buffer))
        {
            if (n == 0)
            {
                sprintf(file_name, "%03i.jpg", n);
                FILE *jpeg = fopen(file_name, "w");
                printf("\nfirst jpeg\n");
            }
            else
            {
                fclose(jpeg);
                n++;
                sprintf(file_name, "%03i.jpg", n);
                // FILE *jpeg = freopen(file_name, "w", jpeg);
                printf("");
            }
            n++;
            //printf("%s ", file_name);
        }
        else
        {
            printf("");
            //printf("\nif not jpeg\n");
        }
        // else {
        //     printf("\nnot start\n");
        // }
        //n++;


    }
    fclose(raw_file);
    printf("%d", n);
}

int check_JPEG(BYTE buffer[BLOCK_SIZE])
{
    int result = 0;
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
    {
        if ((buffer[3] & 0xf0) == 0xe0)
        {
            result = 1;
        }
    }
    return result;
}