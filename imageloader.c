/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				Seikasahara
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	Image *target = (Image *) malloc(sizeof(Image));
	FILE *fp = fopen(filename, 'r');
	if (target == NULL) {
        perror("Failed to allocate memory for Image");
        fclose(fp);
        return NULL;
    }
	if (fp == NULL) {
		perror("file doesn't exist");
		return NULL;
	};
	while (1) {
		int result = fscanf(fp, "%d %d", &target->cols, &target->rows);
		if (result == 2) {
			break;
		} else {
			perror("error when reading file");
			return NULL;
		}
	};
	target->image = (Color **)malloc(target->rows * sizeof(Color *));
	if (target->image == NULL) {
		perror("Failed to allocate memory");
		return NULL;
	}

	for (uint32_t i = 0; i < target->rows; i++) {
		target->image[i] = (Color *)malloc(target->cols * sizeof(Color));
		if (target->image[i] == NULL) {
			perror("Failed to allocate memory for image cols");
			for (uint32_t j = 0; j < i; j++) {
                free(target->image[j]);
            }
            free(target->image);
			return NULL; 
		}
	}

	for (uint32_t i = 0; i < target->rows; i++) {
        for (uint32_t j = 0; j < target->cols; j++) {
            if (fscanf(fp, "%hhu %hhu %hhu", &target->image[i][j].R, &target->image[i][j].G, &target->image[i][j].B) != 3) {
                fprintf(stderr, "Failed to read pixel data at (%d, %d).\n", i, j);
                for (uint32_t k = 0; k < target->rows; k++) {
                    free(target->image[k]);
                }
                free(target->image);
                fclose(fp);
                return NULL;
            }
        }
    }

	for (uint32_t i = 0; i < target->rows; i++) {
        free(target->image[i]);
    }
    free(target->image);
    fclose(fp);
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	if (image != NULL) {
        for (uint32_t i = 0; i < image->rows; i++) {
            free(image->image[i]);
        }
        free(image->image);
        free(image);
    }
}