#ifndef _FILEOPS_H
#define _FILEOPS_H

#include <stdint.h>
#include "bmptypes.h"

uint32_t** loadBMPFile(char* filename, struct bmpInfoHeader* infoHeader);
void freeBMP(uint32_t** bitmap, int w, int h);

#endif /* _FILEOPS_H */
