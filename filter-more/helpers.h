#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

void get_neighbors(int cur_y, int cur_x, int h, int w, RGBTRIPLE copy[h][w], RGBTRIPLE image[h][w]);

int check_borders(int y, int x, int height, int width);