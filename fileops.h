#ifndef _FILEOPS_H
#define _FILEOPS_H

#include <stdint.h>

uint8_t* loadBMPFile(char* filepath);
/* uint8_t* loadJPGFile(char* filepath); */
long getFilesize(FILE* file);

#endif /* _FILEOPS_H */
