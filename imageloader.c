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

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("file doesn't exist");
		return NULL;
	};
    char format[3];
    if (fscanf(fp, "%2s", format) != 1 || format[0] != 'P' || format[1] != '3') {
        fprintf(stderr, "Invalid file format. Expected P3.\n");
        fclose(fp);
        return NULL;
    }
	Image *target = (Image *) malloc(sizeof(Image));
	if (target == NULL) {
        perror("Failed to allocate memory for Image");
        fclose(fp);
        return NULL;
    }
	if (fscanf(fp, "%u %u", &target->cols, &target->rows) != 2) {
        fprintf(stderr, "Failed to read cols and rows.\n");
        free(target);
        fclose(fp);
        return NULL;
    }
    unsigned int max_color;
    if (fscanf(fp, "%u", &max_color) != 1 || max_color != 255) {
        fprintf(stderr, "Invalid max color value. Expected 255.\n");
        free(target);
        fclose(fp);
        return NULL;
    }
	target->image = (Color **)malloc(target->rows * sizeof(Color *));
	if (target->image == NULL) {
		perror("Failed to allocate memory");
		free(target);
        fclose(fp);
		return NULL;
	}

	for (uint32_t i = 0; i < target->rows; i++) {
		target->image[i] = (Color *)malloc(target->cols * sizeof(Color));
		if (target->image[i] == NULL) {
			perror("Failed to allocate memory for image cols");
			freeImage(target);
            fclose(fp);
			return NULL; 
		}
	}

	for (uint32_t i = 0; i < target->rows; i++) {
        for (uint32_t j = 0; j < target->cols; j++) {
            if (fscanf(fp, "%hhu %hhu %hhu", &target->image[i][j].R, &target->image[i][j].G, &target->image[i][j].B) != 3) {
                fprintf(stderr, "Failed to read pixel data at (%d, %d).\n", i, j);
				freeImage(target);
                fclose(fp);
                return NULL;
            }
        }
    }
    fclose(fp);
	return target;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
    // Print the PPM header
    printf("P3\n");
    printf("%u %u\n", image->cols, image->rows);
    printf("255\n");

    // Print the pixel data
    for (uint32_t i = 0; i < image->rows; i++) {
        for (uint32_t j = 0; j < image->cols; j++) {
			printf("%3u %3u %3u", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
			if (j < image->cols - 1) {
				printf("   ");
			}
        }
        printf("\n"); // Newline after each row for better readability
    }
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