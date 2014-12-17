#ifndef _FILEOPS_H
#define _FILEOPS_H

#include <stdint.h>
#include "bmptypes.h"

struct bmpHeader* loadBMPFile(char* filepath);
/* uint8_t* loadJPGFile(char* filepath); */
long getFilesize(FILE* file);

#endif /* _FILEOPS_H */
