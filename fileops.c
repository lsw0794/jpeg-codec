#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>
#include "fileops.h"
#include "bmptypes.h"
#include "jpgtypes.h"


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
	/*int i = 0;
	uint8_t* byte;

	byte = (uint8_t*) infoHdr;

	printf("Size of info header: %lu (0x%lx)\n", sizeof(struct bmpInfoHeader), sizeof(struct bmpInfoHeader));

	printf("Bytewise: \n");
	for(i = 0; i < sizeof(struct bmpInfoHeader); i++)
	{
		printf("%d: 0x%02x\n", i, *(byte++));
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
	
}

uint8_t* loadBMPFile(char *filename, struct bmpInfoHeader* infoHeader)
{
	FILE *fp;
	struct bmpHeader* bitmapFileHeader;
	uint8_t* bmpImg;
	int imageIdx = 0;
	uint8_t tempRGB;	// Swap variable

	// Open file in rb mode
	fp = fopen(filename, "rb");
	if(fp == NULL)
		return NULL;

	bitmapFileHeader = (struct bmpHeader*) malloc(sizeof(struct bmpHeader));

	// read the file header
	fread(bitmapFileHeader, sizeof(struct bmpHeader), 1, fp);

	printBMPHeader(bitmapFileHeader);

	// Verify that this is a BMP file
	if(*((int16_t*)bitmapFileHeader->filetype) != 0x4D42)
	{
		fclose(fp);
		return NULL;
	}

	// read the bitmap info header
	fread(infoHeader, sizeof(struct bmpInfoHeader), 1, fp);

	printBMPInfoHeader(infoHeader);

	// move file point to beginning of bitmap data
	fseek(fp, *((int32_t*)bitmapFileHeader->pxl_off), SEEK_SET);

	printf("Pixel offset: 0x%02x\n", *((int32_t*)bitmapFileHeader->pxl_off));

	// Allocate enough memory for the bmp image data
	bmpImg = (uint8_t*)malloc(*((int32_t*)infoHeader->imgSize));

	if(!bmpImg)
	{
		free(bmpImg);
		fclose(fp);
		return NULL;
	}

	// read in bitmap image data
	fread(bmpImg, *((int32_t*)infoHeader->imgSize), 1, fp);

	// Make sure bitmap image data was read
	if(bmpImg == NULL)
	{
		fclose(fp);
		return NULL;
	}

	// Swap r and b values to get RGB, because bitmap is BGR
	for(imageIdx = 0; imageIdx < *((int32_t*)infoHeader->imgSize); imageIdx += 3)
	{
		tempRGB = bmpImg[imageIdx];
		bmpImg[imageIdx] = bmpImg[imageIdx + 2];
		bmpImg[imageIdx + 2] = tempRGB;
	}

	// close file and return bitmap image data
	fclose(fp);

	return bmpImg;
}