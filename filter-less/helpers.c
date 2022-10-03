#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int rgbav = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rgbav = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = rgbav;
            image[i][j].rgbtGreen = rgbav;
            image[i][j].rgbtBlue = rgbav;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed, originalGreen, originalBlue, sepiaRed, sepiaGreen, sepiaBlue;
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;
            sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            if (sepiaRed > 255) {
                sepiaRed = 255;
            }
            sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            if (sepiaGreen > 255) {
                sepiaGreen = 255;
            }
            sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
            if (sepiaBlue > 255) {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempR, tempG, tempB;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < width / 2; j++, k--)
        {
            tempR =  image[i][j].rgbtRed;
            tempG =  image[i][j].rgbtGreen;
            tempB =  image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;
            image[i][k].rgbtRed = tempR;
            image[i][k].rgbtGreen = tempG;
            image[i][k].rgbtBlue = tempB;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j].rgbtRed = image[i][j].rgbtRed;
            image_copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    int avRed, avGreen, avBlue, neighbours;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            neighbours = 0;
            avRed = 0;
            avGreen = 0;
            avBlue = 0;
            for (int y = -1; y <= 1; y++) {
                int next_y = i + y;
                for (int x = -1; x <= 1; x++) {
                    int next_x = j + x;
                    if (next_x < width && next_x >= 0 && next_y < height && next_y >= 0) {
                        neighbours += 1;
                        avRed += image_copy[next_y][next_x].rgbtRed;
                        avGreen += image_copy[next_y][next_x].rgbtGreen;
                        avBlue += image_copy[next_y][next_x].rgbtBlue;
                    }
                }
            }
            avRed = round(avRed / (neighbours * 1.0));
            avGreen = round(avGreen / (neighbours * 1.0));
            avBlue = round(avBlue / (neighbours * 1.0));
            image[i][j].rgbtRed = avRed;
            image[i][j].rgbtGreen = avGreen;
            image[i][j].rgbtBlue = avBlue;
        }
    }
    return;
}
