/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				Seikasahara
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

int liveOrDeath(Color *color) {
	if (color->B == 255 && color->G == 255 && color->R == 255) {
		return 1;
	} else if (color->B == 0 && color->G == 0 && color->R == 0) {
		return 0;
	} else {
		return -1;
	}
}

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Color *result = (Color *) malloc(sizeof(Color));
	if (result == NULL) {
		perror("failed to allocate memory for color");
		return NULL;
	}
	int directions[8][2] = {
		{-1, 0},
		{1, 0},
		{0, 1},
		{0, -1},
		{1, 1},
		{1, -1},
		{-1, 1},
		{-1, -1},
	};
	int LiveCount = 0;
	int DeathCount = 0;
	for (int i = 0; i < 8; i++) {
		int newRow = (row + directions[i][0] + image->rows) % image->rows;
		int newCol = (col + directions[i][1] + image->cols) % image->cols;
		int neighborStatus = liveOrDeath(&image->image[newRow][newCol]);
		if (neighborStatus == 1) {
			LiveCount++;
		} else if (neighborStatus == 0) {
			DeathCount++;
		}
	}
	int currentStatus = liveOrDeath(&image->image[row][col]);
	if ((currentStatus == 1 && ((rule >> LiveCount) & 1)) || 
		(currentStatus == 0 && ((rule >> (DeathCount + 9)) & 1))) {
		result->B = 255;
		result->G = 255;
		result->R = 255;
	} else {
		result->B = 0;
		result->G = 0;
		result->R = 0;
	}
	return result;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
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
			Color *Cell = evaluateOneCell(image, i, j, rule);
			if (Cell == NULL) {
                // Clean up previously allocated memory before returning NULL
                freeImage(result);
                return NULL;
            }
			result->image[i][j] = *Cell;
			free(Cell);
		}
	}
	return result;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <rule>\n", argv[0]);
        return -1;
    }
	uint32_t rule = strtoul(argv[2], NULL, 16);
	Image * image = readData(argv[1]);
	if (image == NULL) {
        fprintf(stderr, "Failed to read image from %s\n", argv[1]);
        return -1;
    }
	Image * newImage = life(image, rule);
	if (newImage == NULL) {
        fprintf(stderr, "Failed to compute the next iteration of the game of life\n");
        freeImage(image);
        return -1;
    }
	writeData(newImage);
	freeImage(image);
	freeImage(newImage);
	return 0;
}
