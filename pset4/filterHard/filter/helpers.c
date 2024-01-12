#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float g;

    for(int x = 0; x < height; x++){
        for(int j = 0; j < width; j++){

            g = round((image[x][j].rgbtRed + image[x][j].rgbtGreen + image[x][j].rgbtBlue)/3.0);
            image[x][j].rgbtRed = g;
            image[x][j].rgbtBlue = g;
            image[x][j].rgbtGreen = g;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            int r = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int g = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int b = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtRed = (r > 255) ? 255 : r;
            image[i][j].rgbtGreen = (g > 255) ? 255 : g;
            image[i][j].rgbtBlue = (b > 255) ? 255 : b;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp;

    for(int x = 0; x < height; x++){

        for(int j = 0; j < width / 2; j++){

            temp = image[x][j].rgbtBlue;

            image[x][j].rgbtBlue = image[x][width - j - 1].rgbtBlue;
            image[x][width - j - 1].rgbtBlue = temp;


            temp = image[x][j].rgbtRed;

            image[x][j].rgbtRed = image[x][width - j - 1].rgbtRed;
            image[x][width - j - 1].rgbtRed = temp;

            temp = image[x][j].rgbtGreen;

            image[x][j].rgbtGreen = image[x][width - j - 1].rgbtGreen;
            image[x][width - j - 1].rgbtGreen = temp;


        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
   int r = 0,g = 0,b = 0;
   float qtd = 0.0;
   int d = 1;
   int sL, eL, sC, eC;


   for(int x = 0; x < height; x++){

    for(int j = 0; j< width; j++){

        if(x == 0){
            sL = x;
            eL = x + d;
        }

        else if(x == height - 1){
            sL = x - d;
            eL = x;
        }

        else{
            sL = x - d;
            eL = x + d;
        }

        if(j == 0){
            sC = j;
            eC = j + d;
        }
        else if(j == width - 1){
            sC = j - d;
            eC = j;
        }

        else{

            sC = j - d;
            eC = j + d;
        }

        for(int l = sL; l <= eL; l++){
            for(int c= sC; c <= eC;c++ ){

                r += image[l][c].rgbtRed;
                b += image[l][c].rgbtBlue;
                g += image[l][c].rgbtGreen;
                qtd++;
            }
        }

        temp[x][j].rgbtRed = round(r/qtd);
        temp[x][j].rgbtGreen = round(g/qtd);
        temp[x][j].rgbtBlue = round(b/qtd);

        r = 0;
        g = 0;
        b = 0;
        qtd = 0;

    }
   }

for(int x = 0; x < height; x++){
    for(int j = 0; j < width; j++){

        image[x][j].rgbtRed = temp[x][j].rgbtRed;
        image[x][j].rgbtGreen = temp[x][j].rgbtGreen;
        image[x][j].rgbtBlue = temp[x][j].rgbtBlue;
    }
}


    return;
}
