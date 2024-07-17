/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				Seikasahara
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color *targetColor = (Color *)malloc(sizeof(Color));
	if (targetColor == NULL) {
		perror("Failed to allocate memory for Color");
		return NULL;
	}
	targetColor->R = image->image[row][col].R;
	targetColor->G = image->image[row][col].G;
	targetColor->B = image->image[row][col].B;
	return targetColor;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image) {
	//YOUR CODE HERE
    Image *result = (Image *)malloc(sizeof(Image));
    if (result == NULL) {
        perror("Failed to allocate memory for Image");
        return NULL;
    }

    result->rows = image->rows;
    result->cols = image->cols;
    result->image = (Color **)malloc(result->rows * sizeof(Color *));
    if (result->image == NULL) {
        perror("Failed to allocate memory for Image rows");
        free(result);
        return NULL;
    }

    for (uint32_t i = 0; i < result->rows; i++) {
        result->image[i] = (Color *)malloc(result->cols * sizeof(Color));
        if (result->image[i] == NULL) {
            perror("Failed to allocate memory for Image cols");
            freeImage(result);
            return NULL;
        }
    }

    for (uint32_t i = 0; i < image->rows; i++) {
        for (uint32_t j = 0; j < image->cols; j++) {
            Color *pixel = evaluateOnePixel(image, i, j);
            if (pixel == NULL) {
                // Clean up previously allocated memory before returning NULL
                freeImage(result);
                return NULL;
            }

            if ((pixel->B & 1) == 1) {
                result->image[i][j].R = 255;
                result->image[i][j].G = 255;
                result->image[i][j].B = 255;
            } else {
                result->image[i][j].R = 0;
                result->image[i][j].G = 0;
                result->image[i][j].B = 0;
            }
            
            free(pixel);
        }
    }

    return result;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	Image * image = readData(argv[1]);
	Image * newImage = steganography(image);
	writeData(newImage);
	freeImage(image);
	freeImage(newImage);
	return 0;
}
