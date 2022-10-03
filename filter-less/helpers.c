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
            // For each pixel find average amount of red, green and blue
            rgbav = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Save new value to the image pixel
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
            // For each pixel find new rgb values using given formula
            int originalRed, originalGreen, originalBlue, sepiaRed, sepiaGreen, sepiaBlue;
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;
            sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            // Check if the new value is valid
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            // Check if the new value is valid
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
            // Check if the new value is valid
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // Save new rgb values to the image pixel
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
        // For each row swap rgb values of pixels on opposite sides
        for (int j = 0, k = width - 1; j < width / 2; j++, k--)
        {
            // Save the values of a current pixel to temporary variables
            tempR =  image[i][j].rgbtRed;
            tempG =  image[i][j].rgbtGreen;
            tempB =  image[i][j].rgbtBlue;
            // Save the values of a pixel on the opposite side to a current pixel
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;
            // Save the values of a current pixel from temporary variables to a pixel on the opposite side
            image[i][k].rgbtRed = tempR;в
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
    // Copy pixels of the original image
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
            // For each pixel take rgb values of its neighbours
            neighbours = 0;
            avRed = 0;
            avGreen = 0;
            avBlue = 0;
            for (int y = -1; y <= 1; y++)
            {
                int next_y = i + y;
                for (int x = -1; x <= 1; x++)
                {
                    int next_x = j + x;
                    // For corner cases to avoid segmentation fault
                    if (next_x < width && next_x >= 0 && next_y < height && next_y >= 0)
                    {
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
            // Add new rgb values of a pixel to an original image
            image[i][j].rgbtRed = avRed;
            image[i][j].rgbtGreen = avGreen;
            image[i][j].rgbtBlue = avBlue;
        }
    }
    return;
}
