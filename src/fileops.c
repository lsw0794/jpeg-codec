#include <stdio.h>
#include <stdlib.h>
#include "fileops.h"

#define uint8 unsigned char

long getFilesize(FILE* file)
{
    long filesize;
    
    fseek(file, 0L, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return filesize;
}


uint8_t* loadBMPFile(char* filepath)
{
    uint8_t* contents;
    FILE* bmpfile;
    long filesize;

    bmpfile = fopen(filepath, "rb");
    
    filesize = getFilesize(bmpfile);

    contents = (uint8_t*)malloc(filesize);

    fclose(bmpfile);

    return contents;
}


