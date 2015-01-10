#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileops.h"
#include "bmptypes.h"

int main(int argc, char* argv[])
{
	struct bmpInfoHeader* infoHeader;
	uint8_t* imgData;
	int i = 0;

	infoHeader = (struct bmpInfoHeader*) malloc(sizeof(struct bmpInfoHeader));

	if(argc != 2)
	{
		printf("Error: Expecting 1 argument (bmp filename)\n");
		return -1;
	}

	imgData = loadBMPFile(argv[1], infoHeader);
	
	for(i = 0; i < 100; ++i)
	{
		printf("0x%02x ", *(imgData + i));
	}

	free(imgData);
    return 0;
}
