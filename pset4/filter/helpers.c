#include "helpers.h"
# include <math.h>
#include <stdio.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    int numsX[3][3] = {{-1, 0, 1}, {-2,0,2}, {-1,0,1}};
    int numsY[3][3] = {{-1,-2, -1}, {0,0,0}, {1,2,1}};
    RGBTRIPLE temp[height][width];

  int r, b, g;


    int sR,eR,sC,eC;


    for(int x = 0; x < height; x++){

        for(int j = 0; j < width; j++){

    int rgX = 0, rgY = 0;
    int ggX = 0, ggY = 0;
    int bgX = 0, bgY = 0;


            for (int a = -1; a <= 1; a++)  {
            for (int q = -1; q <= 1; q++) {

                int newA = x + a;
                int newQ = j + q;

                if(newA >= 0 && newA < height && newQ >= 0 && newQ < width){

                rgX += image[newA][newQ].rgbtRed * numsX[a + 1][q + 1];
                rgY += image[newA][newQ].rgbtRed * numsY[a + 1][q + 1];

                bgX += image[newA][newQ].rgbtBlue * numsX[a + 1][q + 1];
                bgY += image[newA][newQ].rgbtBlue * numsY[a + 1][q + 1];

                ggX += image[newA][newQ].rgbtGreen * numsX[a + 1][q + 1];
                ggY += image[newA][newQ].rgbtGreen * numsY[a + 1][q + 1];
                }

            }
        }

                    r = round(sqrt((rgX * rgX) + (rgY * rgY)));
                    b = round(sqrt((bgX * bgX) + (bgY * bgY)));
                    g = round(sqrt((ggX * ggX) + (ggY * ggY)));

                    if(r > 255) temp[x][j].rgbtRed = 255;
                    else temp[x][j].rgbtRed = r;

                    if(b > 255) temp[x][j].rgbtBlue = 255;
                    else temp[x][j].rgbtBlue = b;

                    if(g > 255) temp[x][j].rgbtGreen = 255;
                    else temp[x][j].rgbtGreen = g;

        }
    }


    for(int x =0; x < height; x ++){

        for(int j = 0; j < width; j++){

            image[x][j].rgbtRed = temp[x][j].rgbtRed;
            image[x][j].rgbtBlue = temp[x][j].rgbtBlue;
            image[x][j].rgbtGreen = temp[x][j].rgbtGreen;
        }
    }

    return;
}
