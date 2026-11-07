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

#ifndef _GRF_PROTECTED_H_
#define _GRF_PROTECTED_H_

#include <stddef.h>

#define GRF_PROTECTED_KEY_SIZE 60

/* Decode protected payload (GRF entry with type & 0x80).
 * On success returns plaintext allocated with aCalloc (size + 1024 bytes, zero filled,
 * same convention as grfio_reads); caller frees with aFree.
 * raw_name: exact GRF table filename bytes (no slash normalize)
 * name_len: byte length hashed as-is (no terminating NUL is added)
 * payload/payload_len: exact compressed length from table (NOT aligned)
 * expected_size: table uncompressed length (must match header.size)
 * out_size: optional
 * Returns NULL on failure.
 */
void *grf_protected_decode(const unsigned char *payload, unsigned int payload_len,
	const char *raw_name, unsigned int name_len,
	unsigned int expected_size, unsigned int *out_size);

/* Set/replace archive key slot (1-based id, 1..255). key must be 60 bytes.
 * Returns 1 on success, 0 on failure.
 */
int grf_protected_set_archive_key(unsigned int key_id, const unsigned char key[GRF_PROTECTED_KEY_SIZE]);

/* Parse "<id>,<120 hex chars>" (separator may be ',', ' ', ':' or tab) and set the key.
 * Returns 1 on success, 0 on failure.
 */
int grf_protected_parse_key(const char *str);

/* Check whether blob looks like a known key envelope (spec section 9).
 * Known key records are not embedded, so this never loads keys and always returns 0.
 */
int grf_protected_try_load_envelope(const void *blob, size_t len);

#endif /* _GRF_PROTECTED_H_ */
