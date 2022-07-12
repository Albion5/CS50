#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int rgbav = 0;
    for (int i; i = 0; i < height)
    {
        for (int j; j = 0; j < width)
        {
            RGBTRIPLE pixel = image[i][j];
            rgbav = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3);
            pixel.rgbtRed = rgbav;
            pixel.rgbtGreen = rgbav;
            pixel.rgbtBlue = rgbav;
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
