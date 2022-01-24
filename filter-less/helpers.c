#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue, green = image[i][j].rgbtGreen, red = image[i][j].rgbtRed;
            average = (int) round((blue + green + red) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = (int) round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            // making sure the values are b/n 0-255 inclusive
            sepiaRed = (sepiaRed > 255) ? 255 : sepiaRed;
            sepiaRed = (sepiaRed < 0) ? 0 : sepiaRed;
            sepiaGreen = (int) round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            // making sure the values are b/n 0-255 inclusive
            sepiaGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            sepiaGreen = (sepiaGreen < 0) ? 0 : sepiaGreen;
            sepiaBlue = (int) round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            // making sure the values are b/n 0-255 inclusive
            sepiaBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
            sepiaBlue = (sepiaBlue < 0) ? 0 : sepiaBlue;

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][width - 1 - col];
            image[row][width - 1 - col] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // check for an edge
            if ((i == 0 && (j >= 0 && j <= width - 1))
                || ((i >= 0 && i <= height - 1) && j == 0)
                || (i == height - 1 && (j >= 0 && j <= width - 1))
                || ((i >= 0 && i <= height - 1) && j == width - 1))
            {
                //check if it is a corner
                if ((i == 0 && j == 0)
                    || (i == 0 && j == width - 1)
                    || (i == height - 1 && j == 0)
                    || (i == height - 1 && j == width - 1))
                {
                    if (i == 0 && j == 0)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j +

                          1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j +
                         1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j +
                          1].rgbtBlue) / 4.0);
                    }

                    if (i == 0 && j == width - 1)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i + 1 ][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i][j -
                            1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i][j -
                            1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i][j -
                         1].rgbtBlue) / 4.0);
                    }

                    if (i == height - 1 && j == 0)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j +
                           1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j +
                          1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j +
                          1].rgbtBlue) / 4.0);
                    }

                    if (i == height - 1 && j == width - 1)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j -
                           1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j -
                          1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j -
                         1].rgbtBlue) / 4.0);
                    }
                }
                // if not a corner index
                else
                {
                    if (i == 0 && (j >= 1 && j <= width - 2))
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed +
                         copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i +
                          1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i +
                          1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                    }

                    if ((i >= 1 && i <= height - 2) && j == 0)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j + 1].rgbtRed +
                         copy[i - 1][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j +
                         1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j +
                         1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                    }

                    if (i == height - 1 && (j >= 1 && j <= width - 2))
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed +
                          copy[i - 1][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i - 1][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                         copy[i - 1][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 6.0);
                    }

                    if ((i >= 1 && i <= height -2) && j == width - 1)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j - 1].rgbtRed +
                           copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j -
                           1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j -
                          1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6.0);
                    }
                }
            }
            // for normal pixel no edge at all
            else
            {
                image[i][j].rgbtRed = (int) round(((copy[i - 1][j - 1].rgbtRed) + (copy[i - 1][j].rgbtRed) + (copy[i - 1][j + 1].rgbtRed) +
                 (copy[i][j - 1].rgbtRed) + (copy[i][j].rgbtRed) + (copy[i][j + 1].rgbtRed) + (copy[i + 1][j - 1].rgbtRed) + (copy[i + 1][j].rgbtRed) +
                 (copy[i + 1][j + 1].rgbtRed)) / 9.0);
                image[i][j].rgbtGreen = (int) round(((copy[i - 1][j - 1].rgbtGreen) + (copy[i - 1][j].rgbtGreen) + (copy[i - 1][j + 1].rgbtGreen) +
                 (copy[i][j - 1].rgbtGreen) + (copy[i][j].rgbtGreen) + (copy[i][j + 1].rgbtGreen) + (copy[i + 1][j - 1].rgbtGreen) + (copy[i + 1][j].rgbtGreen) +
                 (copy[i + 1][j + 1].rgbtGreen)) / 9.0);
                image[i][j].rgbtBlue = (int) round(((copy[i - 1][j - 1].rgbtBlue) + (copy[i - 1][j].rgbtBlue) +
                 (copy[i - 1][j + 1].rgbtBlue) +
                 (copy[i][j - 1].rgbtBlue) + (copy[i][j].rgbtBlue) + (copy[i][j + 1].rgbtBlue) + (copy[i + 1][j - 1].rgbtBlue) +
                 (copy[i + 1][j].rgbtBlue) +
                 (copy[i + 1][j + 1].rgbtBlue)) / 9.0);
            }

        }
    }

    return;
}
