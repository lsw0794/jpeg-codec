#include <stdio.h>
#include <stdint.h>
#include "bmptypes.h"

int main(void)
{
	printf("Int32: %lu\n", sizeof(int32_t));
	printf("Int16: %lu\n", sizeof(int16_t));
	printf("Uint8: %lu\n", sizeof(uint8_t));
	printf("bmpheader: %lu\n", sizeof(struct bmpHeader));

	return 0;
}