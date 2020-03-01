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

#ifndef	_GRFIO_H_
#define	_GRFIO_H_

void grfio_init(const char*);		// GRFIO Initialize
int grfio_add(const char*);	// GRFIO Resource file add
void* grfio_read(const char*);	// GRFIO data file read
void* grfio_reads(const char*,int*);	// GRFIO data file read & size get
int grfio_size(const char*);		// GRFIO data file size get

int decode_zip(char *dest, unsigned long* destLen, const char* source, unsigned int sourceLen);
int encode_zip(char *dest, unsigned long* destLen, const char* source, unsigned int sourceLen);

void grfio_load_zlib(void);
unsigned long grfio_crc32(const unsigned char *buf, unsigned int len);

#endif	// _GRFIO_H_
