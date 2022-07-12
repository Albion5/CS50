#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int rgbav = 0;
    RGBTRIPLE pixel;
    for (int i; i = 0; i < height)
    {
        for (int j; j = 0; j < width)
        {
            pixel = image[i][j]
            rgbav = pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue
            
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
