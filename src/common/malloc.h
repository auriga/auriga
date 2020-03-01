/*
 * Copyright (C) 2002-2020  Auriga
 *
 * This file is part of Auriga.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

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

#if _MSC_VER >= 1400
	#undef  strdup
	#define strdup _strdup
#endif

int do_init_memmgr(const char* file);
double memmgr_usage(void);

#endif /* _MALLOC_H_ */
