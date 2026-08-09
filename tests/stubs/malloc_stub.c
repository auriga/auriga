/*
 * Minimal allocator stubs for unit tests.
 * Maps Auriga aMalloc_ family to standard malloc/free so common modules
 * can be linked without core/memmgr.
 */

#include <stdlib.h>
#include <string.h>

#include "malloc.h"

void *aMalloc_(size_t size, const char *file, int line, const char *func)
{
	(void)file;
	(void)line;
	(void)func;
	return malloc(size);
}

void *aCalloc_(size_t num, size_t size, const char *file, int line, const char *func)
{
	(void)file;
	(void)line;
	(void)func;
	return calloc(num, size);
}

void *aRealloc_(void *p, size_t size, const char *file, int line, const char *func)
{
	(void)file;
	(void)line;
	(void)func;
	return realloc(p, size);
}

void *aStrdup_(const void *p, const char *file, int line, const char *func)
{
	size_t len;
	char *dup;

	(void)file;
	(void)line;
	(void)func;
	if (p == NULL)
		return NULL;
	len = strlen((const char *)p) + 1;
	dup = (char *)malloc(len);
	if (dup == NULL)
		return NULL;
	memcpy(dup, p, len);
	return dup;
}

void aFree_(void *p, const char *file, int line, const char *func)
{
	(void)file;
	(void)line;
	(void)func;
	free(p);
}

int do_init_memmgr(const char *file)
{
	(void)file;
	return 0;
}

double memmgr_usage(void)
{
	return 0.0;
}
