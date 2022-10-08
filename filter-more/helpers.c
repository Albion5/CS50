#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            copy[y][x].rgbRed = image[y][x];
            copy[y][x].rgbGreen = image[y][x];
            copy[y][x].rgbBlue = imagr[y][x];
        }
    }
    int new_red, new_green, new_blue;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            new_red = get_neighbours(x, y, copy);
            new_green = get_neighbours(x, y, copy);
            new_blue = get_neighbours(x, y, copy);
            image[y][x].rgbRed = new_red;
            image[y][x].rgbGreen = new_green;
            image[y][x].rgbBlue = new_blue;
        }
    }

    return;
}

int get_neighbors(int cur_y, int cur_x, int h, int w, RGBTRIPLE image[h][w]) {
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int row = 0, col = 0;
    int new_y, new_x;
    for (int y = -1; y <= 1; y++)
    {
        new_y = cur_y + y;
        for (int x = -1; x <= 1; x++)
        {
            new_x = cur_x + x;
            if (check_borders(new_y, new_x))
            {

            }
            else
            {

            }
        }
    }

}