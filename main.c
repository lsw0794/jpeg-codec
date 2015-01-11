#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileops.h"
#include "bmptypes.h"

int main(int argc, char* argv[])
{
	struct bmpInfoHeader* infoHeader;
	uint32_t** imgData;
	int i, j;
	int32_t w, h;

	infoHeader = (struct bmpInfoHeader*) malloc(sizeof(struct bmpInfoHeader));

	if(argc != 2)
	{
		printf("Error: Expecting 1 argument (bmp filename)\n");
		return -1;
	}

	imgData = loadBMPFile(argv[1], infoHeader);

	if(imgData == NULL)
	{
		printf("Image is not valid!\n");
		return -1;
	}

	w = *((int32_t*)infoHeader->bmpWidth);
	h = *((int32_t*)infoHeader->bmpHeight);

	printf("Bitmap %d x %d\n", w, h);

	convertToJPG(imgData);


	freeBMP(imgData, w, h);
    return 0;
}

