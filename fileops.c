#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>
#include "fileops.h"
#include "bmptypes.h"


void printBMPHeader(struct bmpHeader* hdr)
{
	/*int i = 0;
	uint8_t* byte;

	byte = (uint8_t*) hdr;

	printf("Bytewise: \n");
	for(i = 0; i < sizeof(struct bmpHeader); ++i)
	{
		printf("0x%02x ", *(byte++));
	}

	printf("\nElement wise: \n");*/
	printf("Filetype: %hu (0x%x)\n", *((int16_t*)hdr->filetype), *((int16_t*)hdr->filetype));
	printf("Filesize: %u (0x%x)\n",  *((int32_t*)hdr->filesize), *((int32_t*)hdr->filesize));
	printf("Reserved: %u (0x%x)\n",  *((int32_t*)hdr->rsrvd1),  *((int32_t*)hdr->rsrvd1));
	printf("Pixel offset: %u (0x%x)\n",  *((int32_t*)hdr->pxl_off),  *((int32_t*)hdr->pxl_off));

}

void printBMPInfoHeader(struct bmpInfoHeader* infoHdr)
{
/*	int i = 0;
	uint8_t* byte;

	byte = (uint8_t*) infoHdr;

	printf("Size of info header: %lu (0x%lx)\n", sizeof(struct bmpInfoHeader), sizeof(struct bmpInfoHeader));

	printf("Bytewise: \n");
	for(i = 0; i < sizeof(struct bmpInfoHeader); i++)
	{
		printf("%d: 0x%02x (%c)\n", i, *(byte), *(byte));
		byte++;
	}

	printf("\nElement wise: \n");*/
	printf("Info header size: %hu (0x%x)\n", *((int32_t*)infoHdr->ihSize), *((int32_t*)infoHdr->ihSize));
	printf("Width: %hu (0x%x)\n", *((int32_t*)infoHdr->bmpWidth), *((int32_t*)infoHdr->bmpWidth));
	printf("Height: %hu (0x%x)\n", *((int32_t*)infoHdr->bmpHeight), *((int32_t*)infoHdr->bmpHeight));
	printf("Planes: %hu (0x%x)\n", *((int16_t*)infoHdr->planes), *((int16_t*)infoHdr->planes));
	printf("Bit Count: %hu (0x%x)\n", *((int16_t*)infoHdr->bitCount), *((int16_t*)infoHdr->bitCount));
	printf("Compression: %hu (0x%x)\n", *((int32_t*)infoHdr->compression), *((int32_t*)infoHdr->compression));
	printf("Image Size: %hu (0x%x)\n", *((int32_t*)infoHdr->imgSize), *((int32_t*)infoHdr->imgSize));
	printf("X Pixels per m: %hu (0x%x)\n", *((int32_t*)infoHdr->xPxm), *((int32_t*)infoHdr->xPxm));
	printf("Y Pixels per m: %hu (0x%x)\n", *((int32_t*)infoHdr->yPxm), *((int32_t*)infoHdr->yPxm));
	printf("Colours Used: %hu (0x%x)\n", *((int32_t*)infoHdr->coloursUsed), *((int32_t*)infoHdr->coloursUsed));
	printf("Colours Important: %hu (0x%x)\n", *((int32_t*)infoHdr->coloursImportant), *((int32_t*)infoHdr->coloursImportant));
	printf("Colour space: %.4s (0x%x)\n", infoHdr->colourSpace, *((int32_t*)infoHdr->colourSpace));
	
}

uint32_t** loadBMPFile(char *filename, struct bmpInfoHeader* infoHeader)
{
	FILE *fp;
	struct bmpHeader* bitmapFileHeader;
	uint8_t* bmpImg;
	int imageIdx = 0;
	int i, j;
	//uint8_t tempRGB;	// Swap variable
	int bmpWidth, bmpHeight;
	uint32_t** bitmap;

	// Open file in rb mode
	fp = fopen(filename, "rb");
	if(fp == NULL)
	{
		printf("Error opening file '%s'. File does not exist.\n", filename);
		return NULL;
	}

	bitmapFileHeader = (struct bmpHeader*) malloc(sizeof(struct bmpHeader));

	// read the file header
	fread(bitmapFileHeader, sizeof(struct bmpHeader), 1, fp);

	printBMPHeader(bitmapFileHeader);

	// Verify that this is a BMP file
	if(*((int16_t*)bitmapFileHeader->filetype) != 0x4D42)
	{
		printf("Invalid magic number for BMP format - should be 0x4D42, is %hd.\n", *((int16_t*)bitmapFileHeader->filetype));
		fclose(fp);
		return NULL;
	}

	// read the bitmap info header
	fread(infoHeader, sizeof(struct bmpInfoHeader), 1, fp);

	printBMPInfoHeader(infoHeader);

	bmpWidth = *((int32_t*)infoHeader->bmpWidth);
	bmpHeight = *((int32_t*)infoHeader->bmpHeight);

	// move file point to beginning of bitmap data
	fseek(fp, *((int32_t*)bitmapFileHeader->pxl_off), SEEK_SET);

	printf("Pixel offset: 0x%02x\n", *((int32_t*)bitmapFileHeader->pxl_off));

	// Allocate enough memory for the bmp image data
	bmpImg = (uint8_t*)malloc(*((int32_t*)infoHeader->imgSize));

	if(!bmpImg)
	{
		free(bmpImg);
		printf("Error allocating memory for bitmap image.\n");
		fclose(fp);
		return NULL;
	}

	// read in bitmap image data
	fread(bmpImg, *((int32_t*)infoHeader->imgSize), 1, fp);

	// Make sure bitmap image data was read
	if(bmpImg == NULL)
	{
		fclose(fp);
		printf("Error reading bitmap image.\n");
		return NULL;
	}

	bitmap = (uint32_t**)malloc(bmpHeight * sizeof(uint32_t*));

	for(i = 0; i < bmpHeight; i++)
	{
		bitmap[i] = (uint32_t*)malloc(bmpWidth * sizeof(uint32_t));
	}
	
	imageIdx = 0;
	for(i = 0; i < bmpHeight; i++)
	{
		for(j = 0; j < bmpWidth; j++)
		{
			bitmap[i][j] = (bmpImg[imageIdx] << 16) | 
			 			   (bmpImg[imageIdx+1] << 8) |
			 				bmpImg[imageIdx+2];
			imageIdx += 3;
		}
	}

	// Swap r and b values to get RGB, because bitmap is BGR
	/*for(imageIdx = 0; imageIdx < *((int32_t*)infoHeader->imgSize); imageIdx += 3)
	{
		tempRGB = bmpImg[imageIdx];
		bmpImg[imageIdx] = bmpImg[imageIdx + 2];
		bmpImg[imageIdx + 2] = tempRGB;
	}*/

	// close file and return bitmap image data
	fclose(fp);

	free(bmpImg);

	return bitmap;
}

void freeBMP(uint32_t** bitmap, int w, int h)
{
	int i = 0;
	for(i = 0; i < h; i++)
		free(bitmap[i]);
	free(bitmap);
}