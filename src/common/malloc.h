#ifndef _MALLOC_H_
#define _MALLOC_H_

#include "utils.h"

#define ALC_MARK __FILE__, __LINE__, __func__

void* aMalloc_( size_t size, const char *file, int line, const char *func );
void* aCalloc_( size_t num, size_t size, const char *file, int line, const char *func );
void* aRealloc_( void *p, size_t size, const char *file, int line, const char *func );
void* aStrdup_( const void *p, const char *file, int line, const char *func );
void  aFree_( void *p, const char *file, int line, const char *func );

#define aMalloc(n)    aMalloc_(n,ALC_MARK)
#define aCalloc(m,n)  aCalloc_(m,n,ALC_MARK)
#define aRealloc(p,n) aRealloc_(p,n,ALC_MARK)
#define aStrdup(p)    aStrdup_(p,ALC_MARK)
#define aFree(p)      do { aFree_(p,ALC_MARK); p = NULL; } while(0)

// ついでに置き換え
#if !defined(_MALLOC_C_) && !defined(MEMWATCH)
#undef  strdup
#define malloc(n)    aMalloc_(n,ALC_MARK)
#define calloc(m,n)  aCalloc_(m,n,ALC_MARK)
#define realloc(p,n) aRealloc_(p,n,ALC_MARK)
#define strdup(p)    aStrdup_(p,ALC_MARK)
#define free(p)      do { aFree_(p,ALC_MARK); p = NULL; } while(0)
#endif

int do_init_memmgr(const char* file);
double memmgr_usage(void);

#endif /* _MALLOC_H_ */
