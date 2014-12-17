#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileops.h"
#include "bmptypes.h"

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
	uint8_t headerBytes[BMP_EOH];
	
	for(i = 0; i < BMP_EOH; i++)
	{
		headerBytes[i] = fgetc(file);
	}
	
	header = (struct bmpHeader*) memcpy(header, &headerBytes[0], sizeof(struct bmpHeader));
	
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


