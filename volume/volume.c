// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // unint8_t stores a 8-bit unsigned integer
    // We've created an array to store 44 bytes from the header
    uint8_t header[HEADER_SIZE];

    // From input to header then from header to output
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // We've created an address where to store samples
    // int16_t stores a 16-bit signed integer
    int16_t sample;

    // For each sample in the input file
    // Copy it to a sample variable
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        // Update volume of a sample by a given factor
        sample *= factor;
        // Copy an updated sample from sample variable to an output file
        fwrite(&sample, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
