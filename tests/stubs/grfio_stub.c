/*
 * grfio stubs for unit tests.
 * grf_protected.c calls decode_zip for zlib bodies; tests do not link zlib,
 * so inflate always fails here.
 */

#include <stddef.h>

#include "grfio.h"

int decode_zip(char *dest, unsigned long *destLen, const char *source, unsigned int sourceLen)
{
	(void)dest;
	(void)source;
	(void)sourceLen;
	if (destLen != NULL)
		*destLen = 0;
	return -1;
}
