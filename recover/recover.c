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
        printf("Error: couldn't open the file");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    int n = 0;
    char file_name[8];
    FILE *jpeg1 = NULL;
    // Repeat untill end of the file
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // If found JPEG
        if (check_JPEG(buffer))
        {
            // Create a file name with its number
            sprintf(file_name, "%03i.jpg", n);
            // If not first JPEG close previosly opened JPEG
            if (n > 0)
            {
                fclose(jpeg1);

            }
            // Open new JPEG and write to file
            jpeg1 = fopen(file_name, "w");
            fwrite(buffer, BLOCK_SIZE, 1, jpeg1);
            n++;
        }
        else
        {
            // If not start of JPEG but there is an open file, continue writing to it
            if (n > 0)
            {
                fwrite(buffer, BLOCK_SIZE, 1, jpeg1);
            }
        }

    }
    // If there is open JPEG close it
    if (jpeg1 != NULL)
    {
        fclose(jpeg1);
    }
    // Close raw file
    fclose(raw_file);
}

// Check if start of a new JPEG
int check_JPEG(BYTE buffer[BLOCK_SIZE])
{
    int result = 0;
    // Check first 4 bytes of block of size 512 bytes (0xff 0xd8 0xff 0xe*)
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
    {
        if ((buffer[3] & 0xf0) == 0xe0)
        {
            result = 1;
        }
    }
    return result;
}