#include "jpgenc.h"
#include <stdint.h>
#include <stdlib.h>
#include "jpgtypes.h"
#include "bmptypes.h"

struct jpgYCbrPixel* encodeBMPtoJPEG(struct bmpRgbPixel rgbImg[], size_t sz)
{
	struct jpgYCbrPixel* ycbrImg = (struct jpgYCbrPixel*)malloc(sz);
	int i = 0;
	float y, cr, cb;
	
	for(i = 0; i < sz; i++)
	{
		y 	= (float)	(0.299 	 * rgbImg[i].r) + (0.587   * rgbImg[i].g) + (0.114   * rgbImg[i].b);
		cb 	= (float)	(-0.1687 * rgbImg[i].r) + (-0.3313 * rgbImg[i].g) + (0.5     * rgbImg[i].b) + 128;
		cr 	= (float)	(0.5     * rgbImg[i].r) + (-0.4187 * rgbImg[i].g) + (-0.0813 * rgbImg[i].b) + 128;
		
		(ycbrImg + i)->y = y;
		(ycbrImg + i)->cb = cb;
		(ycbrImg + i)->cr = cr;
	}
	
	return ycbrImg;
}