#ifndef _BMP_TYPES_H
#define _BMP_TYPES_H
#include <stdint.h>

#define BMP_EOH 0x0D

struct bmpRgbPixel 
{
	uint8_t b;
	uint8_t g;
	uint8_t r;
};

struct bmpHeader
{
	uint8_t header_type[2];
	long long filesize;
	uint8_t rsrvd1[2];
	uint8_t rsrvd2[2];
	uint8_t pxl_off[4];
};

#endif /* _BMP_TYPES_H */