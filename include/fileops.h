#ifndef _FILEOPS_H
#define _FILEOPS_H

#include <stdint.h>
#include "bmptypes.h"

uint8_t* loadBMPFile(char* filepath, struct bmpInfoHeader* infoHeader);

#endif /* _FILEOPS_H */
