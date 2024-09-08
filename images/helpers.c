#include "helpers.h"

#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the red, green, and blue values of the current pixel
            unsigned char red = image[i][j].rgbtRed;
            unsigned char green = image[i][j].rgbtGreen;
            unsigned char blue = image[i][j].rgbtBlue;

            // Calculate the average value (grayscale value)
            int average = round((red + green + blue) / 3.0);

            // Set the new red, green, and blue values to the average
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the original red, green, and blue values
            unsigned char originalRed = image[i][j].rgbtRed;
            unsigned char originalGreen = image[i][j].rgbtGreen;
            unsigned char originalBlue = image[i][j].rgbtBlue;

            // Compute the sepia values
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Ensure the values do not exceed 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Update the pixel with the sepia values
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
    // Loop over each row in the image
    for (int i = 0; i < height; i++)
    {
        // Swap pixels from left to right in the row
        for (int j = 0; j < width / 2; j++)
        {
            // Calculate the opposite pixel index
            int opposite = width - j - 1;

            // Swap the current pixel with the opposite pixel
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][opposite];
            image[i][opposite] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Loop over every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize sum of RGB values and count of pixels considered
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Loop over neighboring pixels (including the pixel itself)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newI = i + di;
                    int newJ = j + dj;

                    // Check if neighboring pixel is within bounds
                    if (newI >= 0 && newI < height && newJ >= 0 && newJ < width)
                    {
                        sumRed += copy[newI][newJ].rgbtRed;
                        sumGreen += copy[newI][newJ].rgbtGreen;
                        sumBlue += copy[newI][newJ].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average color values
            image[i][j].rgbtRed = round(sumRed / (float) count);
            image[i][j].rgbtGreen = round(sumGreen / (float) count);
            image[i][j].rgbtBlue = round(sumBlue / (float) count);
        }
    }
    return;
}
