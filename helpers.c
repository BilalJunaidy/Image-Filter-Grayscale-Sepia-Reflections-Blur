#include "helpers.h"
#include <math.h>
#include <stdio.h>


//helper function to be used for the grayscale function.
RGBTRIPLE average(RGBTRIPLE image);


//Function definition prototype for blurAverage used in the blur function
void blurAverage(int height, int width, int i, int j, RGBTRIPLE image[height][width]);


//helper function to be used for the grayscale function.
//void average(RGBTRIPLE image[height][width]);

// Convert image to grayscale


void grayscale(int height, int width, RGBTRIPLE image[height][width])

{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
        image[i][j] = average(image[i][j]);
        }
    }
    return;
}

//purpose of this function is to update the rbg values of the given pixel to be equal to the average of that pixels rgb values

RGBTRIPLE average(RGBTRIPLE image)
{
    int avg = round((image.rgbtBlue + image.rgbtGreen + image.rgbtRed) / 3.0);

    image.rgbtBlue = avg;
    image.rgbtGreen = avg;
    image.rgbtRed = avg;

    return image;
}



// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
        int red = round((.393 * (float) image[i][j].rgbtRed) + (.769 * (float) image[i][j].rgbtGreen) + (.189 * (float) image[i][j].rgbtBlue));
        int green = round((.349 * (float) image[i][j].rgbtRed) + (.686 * (float) image[i][j].rgbtGreen) + (.168 * (float) image[i][j].rgbtBlue));
        int blue = round((.272 * (float) image[i][j].rgbtRed) + (.534 * (float) image[i][j].rgbtGreen) + (.131 * (float) image[i][j].rgbtBlue));

        if(red > 255)
        {
            red = 255;
        }

        if(green > 255)
        {
            green = 255;
        }

        if(blue > 255)
        {
            blue = 255;
        }

        image[i][j].rgbtBlue = blue;
        image[i][j].rgbtGreen = green;
        image[i][j].rgbtRed = red;
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    int mid_width = floor(width/2.0);

    for (int i = 0; i < height; i++)

    //if(width % 2 != 0)
    {
        for (int j = 0; j < mid_width; j++)
        {

        //purpose of the following code is to copy the integer BGR values of the pixel in column j row i to a temp int variable.
        RGBTRIPLE temp = image[i][j];

        //purpose of the following code is to copy the integer BGR values of the pixel in column (mid_width + diff) row i to the pixel in column j row i.
         image[i][j] = image[i][width - 1 - j];

         //purpose of the following code is to the copy the integer BGR values of the pixel in the temp int varable created in the stack above, into the integer BGR values of the pixel in column (mid_width + diff) row i
         image[i][width - 1 - j] = temp;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blurAverage(height, width, i, j, image);
        }
    }
    return;
}

void blurAverage(int height, int width, int i, int j, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    int div = 0;

    for (int x = 0; x < 2; x++)
    {
        for (int y = 0; y < 2; y++)
        {
            if(i + x - 1> 0 && j + y - 1> 0 && i + x - 1 < height && j + y - 1 < width)
            {
                temp.rgbtBlue+= image[x][y].rgbtBlue;
                temp.rgbtGreen+=  image[x][y].rgbtGreen;
                temp.rgbtRed+= image[x][y].rgbtRed;
                div++;
            }
        }
    }


    //image[i][j].rgbtBlue = temp.rgbtBlue/div;
    //image[i][j].rgbtGreen = temp.rgbtGreen/div;
    //image[i][j].rgbtRed = temp.rgbtRed/div;
}



