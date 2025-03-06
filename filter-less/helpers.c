#include "helpers.h"
#include <math.h>
#include <stdlib.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
             // Take average of red, green, and blue
             int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Update pixel values
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
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get original colors
            int original_red = image[i][j].rgbtRed;
            int original_green = image[i][j].rgbtGreen;
            int original_blue = image[i][j].rgbtBlue;

            // Compute sepia values with the standars to convert
            int sepiaRed = round(0.393 * original_red + 0.769 * original_green + 0.189 * original_blue);
            int sepiaGreen = round(0.349 * original_red + 0.686 * original_green + 0.168 * original_blue);
            int sepiaBlue = round(0.272 * original_red + 0.534 * original_green + 0.131 * original_blue);

            // finally Cap values at 255
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row
    for (int i = 0; i < height; i++)
    {
        // Only go halfway across each row
        for (int j = 0; j < width / 2; j++)
        {
            // Find opposite pixel index
            int opposite_index = width - 1 - j;

            // Swap pixels using a temporary variable
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][opposite_index];
            image[i][opposite_index] = temp;
        }
    }
}
// Blur image with descriptive variable names
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image
    RGBTRIPLE originalImage[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            originalImage[row][col] = image[row][col];
        }
    }

    // Apply blur effect
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int pixelCount = 0;

            // Iterate through the  pixels including the current one
            for (int dRow = -1; dRow <= 1; dRow++)
            {
                for (int dCol = -1; dCol <= 1; dCol++)
                {
                    int neighborRow = row + dRow;
                    int neighborCol = col + dCol;

                    // Check if neighbor is within image bounds
                    if (neighborRow >= 0 && neighborRow < height && neighborCol >= 0 && neighborCol < width)
                    {
                        RGBTRIPLE pixel = originalImage[neighborRow][neighborCol];
                        totalRed += pixel.rgbtRed;
                        totalGreen += pixel.rgbtGreen;
                        totalBlue += pixel.rgbtBlue;
                        pixelCount++;
                    }
                }
            }

            // Calculate average color values
            image[row][col].rgbtRed = round((float) totalRed / pixelCount);
            image[row][col].rgbtGreen = round((float) totalGreen / pixelCount);
            image[row][col].rgbtBlue = round((float) totalBlue / pixelCount);
        }
    }
}
