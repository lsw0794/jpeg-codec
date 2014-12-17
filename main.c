#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileops.h"
#include "bmptypes.h"

int main(int argc, char* argv[])
{
	struct bmpHeader* header;
	int i = 0;
	
	if(argc != 2)
	{
		printf("Error: Expecting 1 argument (bmp filename)\n");
		return -1;
	}

	header = loadBMPFile(argv[1]);
	
	printf("Header type: %.*s\n", sizeof(header->header), header->header);
	printf("Filesize: %.*s\tBytes:", sizeof(header->filesize), header->filesize);
	while(i < sizeof(header->filesize))
	{
		printf("0x%02x\t", header->filesize[i]);
		i++;
	}
	
	printf("\nDecimal equivalent: %ld Bytes\n", (long)&header->filesize[0]);
	
	free(header);	
	
    return 0;
}
