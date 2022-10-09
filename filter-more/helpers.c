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

// Check if pixel's neighbour is beyond the image border
int check_borders(int y, int x, int height, int width)
{
    int border = 0;
    if (y < 0 || y >= height || x < 0 || x >= width)
    {
        border = 1;
    }
    return border;
}

// Count rgb value of a pixel using Sobel filter algorithm
int get_rgb_value(int Gx[3][3], int Gy[3][3])
{
    int gx = 0;
    int gy = 0;
    // Compute two weighed sums for detecting horisontal and vertical edges
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            gx += Gx[y][x];
            gy += Gy[y][x];
        }
    }
    return round(sqrt(gx * gx + gy * gy));

}

// Check if resulting rgb value is valid
int check_over_255(int cur_rgb)
{
    if (cur_rgb > 255)
    {
        cur_rgb = 255;
    }
    return cur_rgb;
}

// Update rgb values of a pixel by taking a weighted sum of the values for the surrounding pixels
void get_neighbours(int cur_y, int cur_x, int h, int w, RGBTRIPLE copy[h][w], RGBTRIPLE image[h][w])
{
    // Create Gx and Gy matrixes for Sobel filter algorithm
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // Create empty matrixes for writing to them new rgb values of pixel's neighbours
    int Gx_matrix_red[3][3], Gx_matrix_green[3][3], Gx_matrix_blue[3][3];
    int Gy_matrix_red[3][3], Gy_matrix_green[3][3], Gy_matrix_blue[3][3];
    int new_y, new_x, red, green, blue;
    int new_red, new_green, new_blue;
    // For each pixel's neighbor
    for (int y = -1, row = 0; y <= 1; y++, row++)
    {
        new_y = cur_y + y;
        for (int x = -1, col = 0; x <= 1; x++, col++)
        {
            new_x = cur_x + x;
            // If it's position is beyond the border
            if (check_borders(new_y, new_x, h, w))
            {
                // Consider it's a black pixel with values 0, 0, 0
                red = 0;
                green = 0;
                blue = 0;
            }
            else
            {
                // Use the values of the pixel in the given image
                red = copy[new_y][new_x].rgbtRed;
                green = copy[new_y][new_x].rgbtGreen;
                blue = copy[new_y][new_x].rgbtBlue;
            }
            // Write to mini-matrixes new rgb values of pixels's neighbours
            Gx_matrix_red[row][col] = red * Gx[row][col];
            Gy_matrix_red[row][col] = red * Gy[row][col];
            Gx_matrix_green[row][col] = green * Gx[row][col];
            Gy_matrix_green[row][col] = green * Gy[row][col];
            Gx_matrix_blue[row][col] = blue * Gx[row][col];
            Gy_matrix_blue[row][col] = blue * Gy[row][col];
        }
    }
    // Count final rgb value using Sobel filter algorithm
    new_red = get_rgb_value(Gx_matrix_red, Gy_matrix_red);
    new_green = get_rgb_value(Gx_matrix_green, Gy_matrix_green);
    new_blue = get_rgb_value(Gx_matrix_blue, Gy_matrix_blue);
    // Write new valid rgb values of a pixel to an image
    image[cur_y][cur_x].rgbtRed = check_over_255(new_red);
    image[cur_y][cur_x].rgbtGreen = check_over_255(new_green);
    image[cur_y][cur_x].rgbtBlue = check_over_255(new_blue);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create image copy
    RGBTRIPLE copy[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            copy[y][x].rgbtRed = image[y][x].rgbtRed;
            copy[y][x].rgbtGreen = image[y][x].rgbtGreen;
            copy[y][x].rgbtBlue = image[y][x].rgbtBlue;
        }
    }
    // For each pixel
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Update its rgb values using Sobel filter algorithm
            get_neighbours(y, x, height, width, copy, image);
        }
    }
    return;
}
