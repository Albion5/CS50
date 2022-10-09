#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

// Update rgb values of a pixel by taking a weighted sum of the values for the surrounding pixels
void get_neighbours(int cur_y, int cur_x, int h, int w, RGBTRIPLE copy[h][w], RGBTRIPLE image[h][w]);

// Check if pixel's neighbour is beyond the image border
int check_borders(int y, int x, int height, int width);

// Count rgb value of a pixel using Sobel filter algorithm
int get_rgb_value(int Gx[3][3], int Gy[3][3]);

// Check if resulting rgb value is valid
int check_over_255(int cur_rgb);