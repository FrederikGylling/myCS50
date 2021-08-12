#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate over each pixel in the 2d matrix
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // take the average of the 3 colors and set all colors to average
            float avg = 0;
            avg = image[i][j].rgbtRed;
            avg += image[i][j].rgbtGreen;
            avg += image[i][j].rgbtBlue;
            avg = round(avg / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate over each pixel in the first half of the 2d matrix
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            // swap the first pixel with the last and so on until the middle
            RGBTRIPLE swap;
            swap = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // set image buffer to keep original
    // set blur box to determine the size of the blurred area
    RGBTRIPLE blurred[height][width];
    int BLURBOX = 3;

    // iterate over each pixel in the 2d matrix
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for each pixel, find the avearge color of the BLURBOX area
            int red = 0, green = 0, blue = 0, cnt = 0;
            for (int k = 0; k < BLURBOX; k++)
            {
                for (int l = 0; l < BLURBOX; l++)
                {
                    if ( 0 <= i + k - 1 && i + k - 1 < height && 0 <= j + l - 1 && j + l - 1 < width)
                    {
                        red += image[i + k - 1][j + l - 1].rgbtRed;
                        green += image[i + k - 1][j + l - 1].rgbtGreen;
                        blue += image[i + k - 1][j + l - 1].rgbtBlue;
                        cnt += 1;
                    }
                }
            }

            // for each pixel, print the blurred pixel to the buffer image
            blurred[i][j].rgbtRed = round( red / (float) cnt);
            blurred[i][j].rgbtGreen = round( green / (float) cnt);
            blurred[i][j].rgbtBlue = round( blue / (float) cnt);
        }
    }
    // iterating over each pixel, to print the buffer image to the orignal image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurred[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // set image buffer to keep original
    // set cap value to be within data type limit (oxff)
    // set box to determine the size of the matrix area
    RGBTRIPLE edged[height][width];
    int CAP_VALUE = 255;
    int BOX = 3;

    // make Gx and Gy matrix
    int Gx [3][3];
    Gx[0][0] = -1;
    Gx[0][1] = 0;
    Gx[0][2] = 1;
    Gx[1][0] = -2;
    Gx[1][1] = 0;
    Gx[1][2] = 2;
    Gx[2][0] = -1;
    Gx[2][1] = 0;
    Gx[2][2] = 1;

    int Gy [3][3];
    Gy[0][0] = -1;
    Gy[0][1] = -2;
    Gy[0][2] = -1;
    Gy[1][0] = 0;
    Gy[1][1] = 0;
    Gy[1][2] = 0;
    Gy[2][0] = 1;
    Gy[2][1] = 2;
    Gy[2][2] = 1;

    // iterate over each pixel in the 2d matrix
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for each pixel, collect Gx and Gy for each color channel
            double Gxred = 0, Gxgreen = 0, Gxblue = 0;
            double Gyred = 0, Gygreen = 0, Gyblue = 0;

            for (int k = 0; k < BOX; k++)
            {
                for (int l = 0; l < BOX; l++)
                {
                    // if matrix point is within image, find product of convolution and color value
                    // (if not, assume 0)
                    if ( 0 <= i + k - 1 && i + k - 1 < height && 0 <= j + l - 1 && j + l - 1 < width)
                    {
                        Gxred += (Gx[k][l] * image[i + k - 1][j + l - 1].rgbtRed);
                        Gxgreen += (Gx[k][l] * image[i + k - 1][j + l - 1].rgbtGreen);
                        Gxblue += (Gx[k][l] * image[i + k - 1][j + l - 1].rgbtBlue);
                        Gyred += (Gy[k][l] * image[i + k - 1][j + l - 1].rgbtRed);
                        Gygreen += (Gy[k][l] * image[i + k - 1][j + l - 1].rgbtGreen);
                        Gyblue += (Gy[k][l] * image[i + k - 1][j + l - 1].rgbtBlue);
                    }
                }
            }
            // Cap value at max 255 for each pixel
            int red, green, blue;

            if (round(sqrt( pow(Gxred, 2) + pow(Gyred, 2))) > CAP_VALUE)
            {
                red = 255;
            }
            else
            {
                red = round(sqrt( pow(Gxred, 2) + pow(Gyred, 2)));
            }

            if (round(sqrt( pow(Gxgreen, 2) + pow(Gygreen, 2))) > CAP_VALUE)
            {
                green = 255;
            }
            else
            {
                green = round(sqrt( pow(Gxgreen, 2) + pow(Gygreen, 2)));
            }

            if (round(sqrt( pow(Gxblue, 2) + pow(Gyblue, 2))) > CAP_VALUE)
            {
                blue = 255;
            }
            else
            {
                blue = round(sqrt( pow(Gxblue, 2) + pow(Gyblue, 2)));
            }

            // write to buffer image
            edged[i][j].rgbtRed = red;
            edged[i][j].rgbtGreen = green;
            edged[i][j].rgbtBlue = blue;
        }
    }

    // iterating over each pixel, to print the buffer image to the orignal image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edged[i][j];
        }
    }
    return;
}
