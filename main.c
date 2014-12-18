#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileops.h"
#include "bmptypes.h"

int main(int argc, char* argv[])
{
	struct bmpHeader* header;
	
	if(argc != 2)
	{
		printf("Error: Expecting 1 argument (bmp filename)\n");
		return -1;
	}

	header = loadBMPFile(argv[1]);
	
	printf("Header type: %.*s\n", sizeof(header->header_type), header->header_type);
	printf("Filesize: %lld Bytes\n", header->filesize);
	
	free(header);	
	
    return 0;
}
