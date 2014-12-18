#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileops.h"
#include "bmptypes.h"
#include "jpgtypes.h"

long getFilesize(FILE* file)
{
    long filesize;
    
    fseek(file, 0L, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return filesize;
}

struct bmpHeader* loadBMPFileHeader(FILE* file, struct bmpHeader* header)
{
	int i = 0;
	int j = 0;
	uint8_t headerBytes[BMP_EOH];
	uint8_t filesizeBuf[4];
	
	for(i = 0; i < BMP_EOH; i++)
	{
		headerBytes[i] = fgetc(file);
	}
	
	printf("Size of header type: %d\n", sizeof(header->header_type));

	for(i = 0; i < sizeof(header->header_type); i++)
	{
		header->header_type[i] = headerBytes[i];
	}

	printf("Offset now: %d\n", i);

	/* Need to reverse filesize bytes from 0 -> 4 to 4 -> 0 - it's backwards for some reason... */
	for(j = 0; j < sizeof(header->filesize); i++, j++)
	{
		filesizeBuf[i] = headerBytes[sizeof(header->filesize) - i];
		printf("Byte %d: 0x%02x\n", i, filesizeBuf[i]);
	}

	header->filesize = (int) &filesizeBuf[0];

	return header;
}

struct bmpHeader* loadBMPFile(char* filepath)
{
	struct bmpHeader* file_header;
    FILE* bmpfile;
    long filesize;

    bmpfile = fopen(filepath, "rb");
    
    filesize = getFilesize(bmpfile);
	
	printf("Filesize: %ld\n", filesize);

	file_header = (struct bmpHeader*) malloc(sizeof(struct bmpHeader));
	
	file_header = loadBMPFileHeader(bmpfile, file_header);

    fclose(bmpfile);

    return file_header;
}


