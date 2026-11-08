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

#define GRF_PROTECTED_HEADER_SIZE   104u
#define GRF_PROTECTED_MAX_PLAINTEXT (256u * 1024u * 1024u)
#define GRF_PROTECTED_MAX_PAYLOAD   (GRF_PROTECTED_MAX_PLAINTEXT + 104u + 8u)

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

/* Allocate protected payload for tests; caller aFree's. Returns NULL on failure.
 * Header cipher is 1 (AES-128-CBC fixed IV) and flags are 0.
 * body_cipher: 259/260/269, compression: 0=stored, 2=LZ4 (zlib is not supported)
 * key_id: 0 = inline material from key60, otherwise key60 must match the key
 *         the decoder resolves for key_id (archive key or built-in default key)
 */
unsigned char *grf_protected_encode_for_test(
	const unsigned char *plain, unsigned int plain_len,
	const char *raw_name, unsigned int name_len,
	unsigned int body_cipher,
	unsigned int compression,
	unsigned int key_id,
	const unsigned char key60[GRF_PROTECTED_KEY_SIZE],
	unsigned int *out_payload_len);

/* Fill checksum (hdr+4) and encrypt hdr+8..103 with header cipher 1, in place.
 * hdr holds the plaintext header; hdr[0]/hdr[1] are set to 1. For tests.
 */
void grf_protected_seal_header_for_test(unsigned char hdr[GRF_PROTECTED_HEADER_SIZE]);

#endif /* _GRF_PROTECTED_H_ */
