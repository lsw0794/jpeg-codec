#ifndef _JPG_TYPES_H
#define _JPG_TYPES_H

struct jpgYCbrPixel
{
	float y;
	float cb;
	float cr;
};

struct jpgHeader
{
	int16_t magicnum;
	int16_t imgWidth;
	int16_t imgHeight;
	int8_t components;
	int8_t samplingFactor1;
	int8_t samplingFactor2;
	int8_t samplingFactor3;
};

#endif /* _JPG_TYPES_H */