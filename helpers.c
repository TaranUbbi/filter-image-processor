#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int rgbAdded = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue);
            float rgbAverage = (rgbAdded / 3.0);
            int rgbAveRound = round(rgbAverage);

            // Update pixel values
            image[i][j].rgbtRed = rgbAveRound;
            image[i][j].rgbtGreen = rgbAveRound;
            image[i][j].rgbtBlue = rgbAveRound;
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
            float sepiaRed = (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                              .189 * image[i][j].rgbtBlue);
            float sepiaGreen = (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                .168 * image[i][j].rgbtBlue);
            float sepiaBlue = (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                               .131 * image[i][j].rgbtBlue);

            int roundSepRed = round(sepiaRed);
            int roundSepGreen = round(sepiaGreen);
            int roundSepBlue = round(sepiaBlue);
            if (roundSepRed > 255)
            {
                roundSepRed = 255;
            }

            if (roundSepGreen > 255)
            {
                roundSepGreen = 255;
            }

            if (roundSepBlue > 255)
            {
                roundSepBlue = 255;
            }

            image[i][j].rgbtRed = roundSepRed;
            image[i][j].rgbtGreen = roundSepGreen;
            image[i][j].rgbtBlue = roundSepBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            int redTemp = image[i][j].rgbtRed;
            int redGreen = image[i][j].rgbtGreen;
            int blueTemp = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtRed = redTemp;
            image[i][width - j - 1].rgbtGreen = redGreen;
            image[i][width - j - 1].rgbtBlue = blueTemp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            float counter = 0.00;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 ||
                        currentY > (width - 1))
                    {
                        continue;
                    }

                    totalRed += image[currentX][currentY].rgbtRed;
                    totalGreen += image[currentX][currentY].rgbtGreen;
                    totalBlue += image[currentX][currentY].rgbtBlue;

                    counter++;
                }
            }
            copy[i][j].rgbtRed = round(totalRed / counter);
            copy[i][j].rgbtGreen = round(totalGreen / counter);
            copy[i][j].rgbtBlue = round(totalBlue / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
