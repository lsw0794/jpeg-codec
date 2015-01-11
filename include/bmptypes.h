#ifndef _BMP_TYPES_H
#define _BMP_TYPES_H
#include <stdint.h>

struct bmpRgbPixel 
{
	uint8_t b;
	uint8_t g;
	uint8_t r;
};

struct bmpHeader
{
	uint8_t filetype[2];
	uint8_t filesize[4];
	uint8_t rsrvd1[4];
	uint8_t pxl_off[4];
};

struct bmpInfoHeader
{
	uint8_t ihSize[4];
	uint8_t bmpWidth[4];
	uint8_t bmpHeight[4];
	uint8_t planes[2];
	uint8_t bitCount[2];
	uint8_t compression[4];
	uint8_t imgSize[4];
	uint8_t xPxm[4];
	uint8_t yPxm[4];
	uint8_t coloursUsed[4];
	uint8_t coloursImportant[4];
	uint8_t colourSpace[4];
	uint8_t unused2[64];
};


struct colourTable
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t rsrvd;
};

#endif /* _BMP_TYPES_H */