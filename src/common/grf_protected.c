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

/*********************************************************************
 *
 *		grf_protected.c -- protected GRF entry (type & 0x80) decoder
 *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grfio.h"
#include "malloc.h"
#include "grf_protected.h"

#define XXH_INLINE_ALL
#define XXH_STATIC_LINKING_ONLY
#include "xxhash.h"

#include "lz4.h"

#define GRFP_HEADER_SIZE   GRF_PROTECTED_HEADER_SIZE
#define GRFP_MAX_SIZE      GRF_PROTECTED_MAX_PLAINTEXT
#define GRFP_MAX_KEYS      256
#define GRFP_PLAIN_HEAD    128
#define GRFP_RC5_OFFSET    2176
#define GRFP_RC5_MAX       1024
#define GRFP_RC5_ROUNDS    20
#define GRFP_TEA_ROUNDS    16
#define GRFP_TEA_DELTA     0x9E3779B9u

static const unsigned char master_key[16] = {
	0x56, 0xfd, 0x7e, 0x71, 0x2f, 0x6d, 0x36, 0xf5, 0x5c, 0xa5, 0x99, 0xe6, 0x7b, 0x18, 0x10, 0x7a
};
static const unsigned char aes_iv_type1[16] = {
	0x4c, 0xe8, 0xa1, 0xae, 0x45, 0xb3, 0x21, 0x60, 0x7e, 0x4f, 0x26, 0xa4, 0xbb, 0x14, 0x0c, 0x96
};
static const unsigned char threeway_key[12] = {
	0xad, 0x61, 0xae, 0xda, 0xbf, 0x20, 0x3e, 0x1d, 0xfe, 0x1d, 0xb7, 0x2b
};
static const unsigned char threeway_iv[12] = {
	0xa0, 0x95, 0xdf, 0xcf, 0xd0, 0x4b, 0x74, 0xdb, 0x02, 0x7e, 0xde, 0x09
};

static const unsigned char grf_default_key1[GRF_PROTECTED_KEY_SIZE] = {
	251, 4, 60, 99, 44, 96, 169, 51, 228, 0, 13, 249, 77, 215, 114, 244,
	198, 231, 137, 224, 179, 32, 119, 176, 1, 94, 56, 18, 61, 25, 233, 99,
	177, 211, 5, 120, 116, 153, 13, 98, 106, 88, 75, 224, 169, 144, 203, 143,
	28, 67, 111, 83, 195, 193, 200, 143, 185, 7, 59, 209
};
static const unsigned char grf_default_key2[GRF_PROTECTED_KEY_SIZE] = {
	79, 122, 239, 181, 187, 174, 97, 103, 82, 150, 170, 70, 109, 47, 93, 124,
	251, 106, 121, 207, 238, 70, 4, 129, 174, 178, 48, 103, 135, 74, 148, 139,
	111, 54, 183, 204, 118, 32, 226, 15, 195, 150, 14, 253, 41, 139, 62, 202,
	186, 11, 143, 231, 98, 109, 210, 178, 147, 220, 238, 23
};
static const unsigned char grf_default_key3[GRF_PROTECTED_KEY_SIZE] = {
	228, 230, 159, 227, 155, 140, 208, 121, 170, 224, 46, 124, 143, 252, 242, 244,
	168, 204, 250, 177, 169, 75, 210, 202, 174, 95, 116, 124, 148, 95, 143, 128,
	171, 225, 226, 248, 254, 180, 62, 34, 223, 232, 150, 88, 3, 137, 80, 50,
	212, 118, 154, 53, 81, 116, 25, 237, 255, 11, 250, 151
};

static const unsigned char grf_key_block[192] = {
	0x03, 0x00, 0x01, 0x00, 0xe4, 0xe6, 0x9f, 0xe3, 0x9b, 0x8c, 0xd0, 0x79, 0xaa, 0xe0, 0x2e, 0x7c,
	0x8f, 0xfc, 0xf2, 0xf4, 0xa8, 0xcc, 0xfa, 0xb1, 0xa9, 0x4b, 0xd2, 0xca, 0xae, 0x5f, 0x74, 0x7c,
	0x94, 0x5f, 0x8f, 0x80, 0xab, 0xe1, 0xe2, 0xf8, 0xfe, 0xb4, 0x3e, 0x22, 0xdf, 0xe8, 0x96, 0x58,
	0x03, 0x89, 0x50, 0x32, 0xd4, 0x76, 0x9a, 0x35, 0x51, 0x74, 0x19, 0xed, 0xff, 0x0b, 0xfa, 0x97,
	0x01, 0x00, 0x00, 0x00, 0xfb, 0x04, 0x3c, 0x63, 0x2c, 0x60, 0xa9, 0x33, 0xe4, 0x00, 0x0d, 0xf9,
	0x4d, 0xd7, 0x72, 0xf4, 0xc6, 0xe7, 0x89, 0xe0, 0xb3, 0x20, 0x77, 0xb0, 0x01, 0x5e, 0x38, 0x12,
	0x3d, 0x19, 0xe9, 0x63, 0xb1, 0xd3, 0x05, 0x78, 0x74, 0x99, 0x0d, 0x62, 0x6a, 0x58, 0x4b, 0xe0,
	0xa9, 0x90, 0xcb, 0x8f, 0x1c, 0x43, 0x6f, 0x53, 0xc3, 0xc1, 0xc8, 0x8f, 0xb9, 0x07, 0x3b, 0xd1,
	0x02, 0x00, 0x00, 0x00, 0x4f, 0x7a, 0xef, 0xb5, 0xbb, 0xae, 0x61, 0x67, 0x52, 0x96, 0xaa, 0x46,
	0x6d, 0x2f, 0x5d, 0x7c, 0xfb, 0x6a, 0x79, 0xcf, 0xee, 0x46, 0x04, 0x81, 0xae, 0xb2, 0x30, 0x67,
	0x87, 0x4a, 0x94, 0x8b, 0x6f, 0x36, 0xb7, 0xcc, 0x76, 0x20, 0xe2, 0x0f, 0xc3, 0x96, 0x0e, 0xfd,
	0x29, 0x8b, 0x3e, 0xca, 0xba, 0x0b, 0x8f, 0xe7, 0x62, 0x6d, 0xd2, 0xb2, 0x93, 0xdc, 0xee, 0x17
};

static unsigned char archive_keys[GRFP_MAX_KEYS][GRF_PROTECTED_KEY_SIZE];
static unsigned char archive_key_present[GRFP_MAX_KEYS];

static const unsigned char *grf_default_key(unsigned int key_id)
{
	if(key_id == 1)
		return grf_default_key1;
	if(key_id == 2)
		return grf_default_key2;
	if(key_id == 3)
		return grf_default_key3;
	return NULL;
}

/*==========================================
 *	byte order helpers
 *------------------------------------------
 */
static unsigned int rd_le16(const unsigned char *p)
{
	return (unsigned int)p[0] | ((unsigned int)p[1] << 8);
}

static unsigned int rd_le32(const unsigned char *p)
{
	return (unsigned int)p[0] | ((unsigned int)p[1] << 8) | ((unsigned int)p[2] << 16) | ((unsigned int)p[3] << 24);
}

static unsigned int rd_be32(const unsigned char *p)
{
	return ((unsigned int)p[0] << 24) | ((unsigned int)p[1] << 16) | ((unsigned int)p[2] << 8) | (unsigned int)p[3];
}

static void wr_le32(unsigned char *p, unsigned int v)
{
	p[0] = (unsigned char)v;
	p[1] = (unsigned char)(v >> 8);
	p[2] = (unsigned char)(v >> 16);
	p[3] = (unsigned char)(v >> 24);
}

static void wr_be32(unsigned char *p, unsigned int v)
{
	p[0] = (unsigned char)(v >> 24);
	p[1] = (unsigned char)(v >> 16);
	p[2] = (unsigned char)(v >> 8);
	p[3] = (unsigned char)v;
}

static void wr_le64(unsigned char *p, unsigned long long v)
{
	int i;

	for(i = 0; i < 8; i++)
		p[i] = (unsigned char)(v >> (i * 8));
}

/*==========================================
 *	NativeHash : XXH3-128 (low64 LE + high64 LE)
 *------------------------------------------
 */
static void native_hash(const void *data, size_t len, unsigned long long seed, unsigned char out[16])
{
	XXH128_hash_t h = XXH3_128bits_withSeed(data, len, (XXH64_hash_t)seed);

	wr_le64(out, (unsigned long long)h.low64);
	wr_le64(out + 8, (unsigned long long)h.high64);
}

/*==========================================
 *	AES-128
 *------------------------------------------
 */
static unsigned char aes_sbox[256];
static unsigned char aes_inv_sbox[256];
static int aes_ready = 0;

static unsigned char aes_xtime(unsigned char x)
{
	return (unsigned char)((x << 1) ^ ((x & 0x80) ? 0x1b : 0x00));
}

static unsigned char aes_gmul(unsigned char a, unsigned char b)
{
	unsigned char r = 0;

	while(b) {
		if(b & 1)
			r ^= a;
		a = aes_xtime(a);
		b >>= 1;
	}
	return r;
}

static unsigned char rotl8(unsigned char x, int n)
{
	return (unsigned char)((x << n) | (x >> (8 - n)));
}

static void aes_init_tables(void)
{
	unsigned char p = 1, q = 1;
	int i;

	if(aes_ready)
		return;

	do {
		/* p *= 3, q /= 3 in GF(2^8) */
		p = (unsigned char)(p ^ (unsigned char)(p << 1) ^ ((p & 0x80) ? 0x1b : 0x00));
		q ^= (unsigned char)(q << 1);
		q ^= (unsigned char)(q << 2);
		q ^= (unsigned char)(q << 4);
		if(q & 0x80)
			q ^= 0x09;
		aes_sbox[p] = (unsigned char)(q ^ rotl8(q, 1) ^ rotl8(q, 2) ^ rotl8(q, 3) ^ rotl8(q, 4) ^ 0x63);
	} while(p != 1);
	aes_sbox[0] = 0x63;

	for(i = 0; i < 256; i++)
		aes_inv_sbox[aes_sbox[i]] = (unsigned char)i;

	aes_ready = 1;
}

static void aes128_expand_key(const unsigned char key[16], unsigned char rk[176])
{
	unsigned char rcon = 1, t[4], u;
	int i, k;

	aes_init_tables();
	memcpy(rk, key, 16);
	for(i = 16; i < 176; i += 4) {
		memcpy(t, rk + i - 4, 4);
		if((i & 15) == 0) {
			u    = t[0];
			t[0] = (unsigned char)(aes_sbox[t[1]] ^ rcon);
			t[1] = aes_sbox[t[2]];
			t[2] = aes_sbox[t[3]];
			t[3] = aes_sbox[u];
			rcon = aes_xtime(rcon);
		}
		for(k = 0; k < 4; k++)
			rk[i + k] = (unsigned char)(rk[i - 16 + k] ^ t[k]);
	}
}

static void aes128_decrypt_block(const unsigned char rk[176], const unsigned char in[16], unsigned char out[16])
{
	unsigned char s[16], t[16];
	int round, c, r, i;

	for(i = 0; i < 16; i++)
		s[i] = (unsigned char)(in[i] ^ rk[160 + i]);

	for(round = 9; round >= 0; round--) {
		/* InvShiftRows + InvSubBytes */
		for(c = 0; c < 4; c++) {
			for(r = 0; r < 4; r++)
				t[((c + r) & 3) * 4 + r] = aes_inv_sbox[s[c * 4 + r]];
		}
		for(i = 0; i < 16; i++)
			s[i] = (unsigned char)(t[i] ^ rk[round * 16 + i]);
		if(round == 0)
			break;
		/* InvMixColumns */
		for(c = 0; c < 4; c++) {
			unsigned char a0 = s[c * 4], a1 = s[c * 4 + 1], a2 = s[c * 4 + 2], a3 = s[c * 4 + 3];
			s[c * 4]     = (unsigned char)(aes_gmul(a0, 14) ^ aes_gmul(a1, 11) ^ aes_gmul(a2, 13) ^ aes_gmul(a3, 9));
			s[c * 4 + 1] = (unsigned char)(aes_gmul(a0, 9) ^ aes_gmul(a1, 14) ^ aes_gmul(a2, 11) ^ aes_gmul(a3, 13));
			s[c * 4 + 2] = (unsigned char)(aes_gmul(a0, 13) ^ aes_gmul(a1, 9) ^ aes_gmul(a2, 14) ^ aes_gmul(a3, 11));
			s[c * 4 + 3] = (unsigned char)(aes_gmul(a0, 11) ^ aes_gmul(a1, 13) ^ aes_gmul(a2, 9) ^ aes_gmul(a3, 14));
		}
	}
	memcpy(out, s, 16);
}

static void aes128_cbc_decrypt(const unsigned char key[16], const unsigned char iv[16], unsigned char *buf, size_t len)
{
	unsigned char rk[176], prev[16], cur[16];
	size_t ofs;
	int i;

	aes128_expand_key(key, rk);
	memcpy(prev, iv, 16);
	for(ofs = 0; ofs + 16 <= len; ofs += 16) {
		memcpy(cur, buf + ofs, 16);
		aes128_decrypt_block(rk, cur, buf + ofs);
		for(i = 0; i < 16; i++)
			buf[ofs + i] ^= prev[i];
		memcpy(prev, cur, 16);
	}
}

static void aes128_encrypt_block(const unsigned char rk[176], const unsigned char in[16], unsigned char out[16])
{
	unsigned char s[16], t[16];
	int round, c, r, i;

	for(i = 0; i < 16; i++)
		s[i] = (unsigned char)(in[i] ^ rk[i]);

	for(round = 1; round <= 10; round++) {
		/* SubBytes + ShiftRows */
		for(c = 0; c < 4; c++) {
			for(r = 0; r < 4; r++)
				t[c * 4 + r] = aes_sbox[s[((c + r) & 3) * 4 + r]];
		}
		/* MixColumns */
		if(round < 10) {
			for(c = 0; c < 4; c++) {
				unsigned char a0 = t[c * 4], a1 = t[c * 4 + 1], a2 = t[c * 4 + 2], a3 = t[c * 4 + 3];
				t[c * 4]     = (unsigned char)(aes_gmul(a0, 2) ^ aes_gmul(a1, 3) ^ a2 ^ a3);
				t[c * 4 + 1] = (unsigned char)(a0 ^ aes_gmul(a1, 2) ^ aes_gmul(a2, 3) ^ a3);
				t[c * 4 + 2] = (unsigned char)(a0 ^ a1 ^ aes_gmul(a2, 2) ^ aes_gmul(a3, 3));
				t[c * 4 + 3] = (unsigned char)(aes_gmul(a0, 3) ^ a1 ^ a2 ^ aes_gmul(a3, 2));
			}
		}
		for(i = 0; i < 16; i++)
			s[i] = (unsigned char)(t[i] ^ rk[round * 16 + i]);
	}
	memcpy(out, s, 16);
}

static void aes128_cbc_encrypt(const unsigned char key[16], const unsigned char iv[16], unsigned char *buf, size_t len)
{
	unsigned char rk[176];
	const unsigned char *prev = iv;
	size_t ofs;
	int i;

	aes128_expand_key(key, rk);
	for(ofs = 0; ofs + 16 <= len; ofs += 16) {
		for(i = 0; i < 16; i++)
			buf[ofs + i] ^= prev[i];
		aes128_encrypt_block(rk, buf + ofs, buf + ofs);
		prev = buf + ofs;
	}
}

/*==========================================
 *	IDEA (BouncyCastle compatible)
 *------------------------------------------
 */
#define IDEA_MASK 0xffffu
#define IDEA_BASE 0x10001u

static unsigned int idea_mul(unsigned int x, unsigned int y)
{
	if(x == 0) {
		x = IDEA_BASE - y;
	} else if(y == 0) {
		x = IDEA_BASE - x;
	} else {
		unsigned int p = x * y;
		y = p & IDEA_MASK;
		x = p >> 16;
		x = y - x + ((y < x) ? 1 : 0);
	}
	return x & IDEA_MASK;
}

static unsigned int idea_mulinv(unsigned int x)
{
	unsigned int t0, t1, q, y;

	if(x < 2)
		return x;

	t0 = 1;
	t1 = IDEA_BASE / x;
	y  = IDEA_BASE % x;
	while(y != 1) {
		q  = x / y;
		x  = x % y;
		t0 = (t0 + (t1 * q)) & IDEA_MASK;
		if(x == 1)
			return t0;
		q  = y / x;
		y  = y % x;
		t1 = (t1 + (t0 * q)) & IDEA_MASK;
	}
	return (1 - t1) & IDEA_MASK;
}

static unsigned int idea_addinv(unsigned int x)
{
	return (0 - x) & IDEA_MASK;
}

static void idea_expand_key(const unsigned char key[16], unsigned int ek[52])
{
	int i;

	for(i = 0; i < 8; i++)
		ek[i] = ((unsigned int)key[i * 2] << 8) | key[i * 2 + 1];
	for(i = 8; i < 52; i++) {
		if((i & 7) < 6)
			ek[i] = (((ek[i - 7] & 127) << 9) | (ek[i - 6] >> 7)) & IDEA_MASK;
		else if((i & 7) == 6)
			ek[i] = (((ek[i - 7] & 127) << 9) | (ek[i - 14] >> 7)) & IDEA_MASK;
		else
			ek[i] = (((ek[i - 15] & 127) << 9) | (ek[i - 14] >> 7)) & IDEA_MASK;
	}
}

static void idea_invert_key(const unsigned int ek[52], unsigned int dk[52])
{
	unsigned int t1, t2, t3, t4;
	int p = 52, in = 0, round;

	t1 = idea_mulinv(ek[in++]);
	t2 = idea_addinv(ek[in++]);
	t3 = idea_addinv(ek[in++]);
	t4 = idea_mulinv(ek[in++]);
	dk[--p] = t4;
	dk[--p] = t3;
	dk[--p] = t2;
	dk[--p] = t1;

	for(round = 1; round < 8; round++) {
		t1 = ek[in++];
		t2 = ek[in++];
		dk[--p] = t2;
		dk[--p] = t1;

		t1 = idea_mulinv(ek[in++]);
		t2 = idea_addinv(ek[in++]);
		t3 = idea_addinv(ek[in++]);
		t4 = idea_mulinv(ek[in++]);
		dk[--p] = t4;
		dk[--p] = t2;	/* middle rounds swap the add keys */
		dk[--p] = t3;
		dk[--p] = t1;
	}

	t1 = ek[in++];
	t2 = ek[in++];
	dk[--p] = t2;
	dk[--p] = t1;

	t1 = idea_mulinv(ek[in++]);
	t2 = idea_addinv(ek[in++]);
	t3 = idea_addinv(ek[in++]);
	t4 = idea_mulinv(ek[in++]);
	dk[--p] = t4;
	dk[--p] = t3;
	dk[--p] = t2;
	dk[--p] = t1;
}

static void idea_block(const unsigned int wk[52], const unsigned char in[8], unsigned char out[8])
{
	unsigned int x0, x1, x2, x3, t0, t1;
	int round, k = 0;

	x0 = ((unsigned int)in[0] << 8) | in[1];
	x1 = ((unsigned int)in[2] << 8) | in[3];
	x2 = ((unsigned int)in[4] << 8) | in[5];
	x3 = ((unsigned int)in[6] << 8) | in[7];

	for(round = 0; round < 8; round++) {
		x0 = idea_mul(x0, wk[k++]);
		x1 = (x1 + wk[k++]) & IDEA_MASK;
		x2 = (x2 + wk[k++]) & IDEA_MASK;
		x3 = idea_mul(x3, wk[k++]);

		t0 = x1;
		t1 = x2;
		x2 ^= x0;
		x1 ^= x3;

		x2 = idea_mul(x2, wk[k++]);
		x1 = (x1 + x2) & IDEA_MASK;
		x1 = idea_mul(x1, wk[k++]);
		x2 = (x2 + x1) & IDEA_MASK;

		x0 ^= x1;
		x3 ^= x2;
		x1 ^= t1;
		x2 ^= t0;
	}

	t0 = idea_mul(x0, wk[k++]);
	t1 = (x2 + wk[k++]) & IDEA_MASK;	/* final add keys use swapped words */
	x1 = (x1 + wk[k++]) & IDEA_MASK;
	x3 = idea_mul(x3, wk[k]);

	out[0] = (unsigned char)(t0 >> 8); out[1] = (unsigned char)t0;
	out[2] = (unsigned char)(t1 >> 8); out[3] = (unsigned char)t1;
	out[4] = (unsigned char)(x1 >> 8); out[5] = (unsigned char)x1;
	out[6] = (unsigned char)(x3 >> 8); out[7] = (unsigned char)x3;
}

static void idea_cbc_decrypt(const unsigned char key[16], const unsigned char iv[8], unsigned char *buf, size_t len)
{
	unsigned int ek[52], dk[52];
	unsigned char prev[8], cur[8];
	size_t ofs;
	int i;

	idea_expand_key(key, ek);
	idea_invert_key(ek, dk);
	memcpy(prev, iv, 8);
	for(ofs = 0; ofs + 8 <= len; ofs += 8) {
		memcpy(cur, buf + ofs, 8);
		idea_block(dk, cur, buf + ofs);
		for(i = 0; i < 8; i++)
			buf[ofs + i] ^= prev[i];
		memcpy(prev, cur, 8);
	}
}

/* spec 5.3 */
static void idea_make_mask(const unsigned char key[16], const unsigned char src[16], const unsigned char iv[8], unsigned char mask[16])
{
	unsigned int ek[52];
	unsigned char blk[8];
	int i;

	idea_expand_key(key, ek);
	for(i = 0; i < 8; i++)
		blk[i] = (unsigned char)(src[i] ^ iv[i]);
	idea_block(ek, blk, mask);
	for(i = 0; i < 8; i++)
		blk[i] = (unsigned char)(src[8 + i] ^ mask[i]);
	idea_block(ek, blk, mask + 8);
}

static void apply_mask(unsigned char *buf, size_t from, size_t to, const unsigned char mask[16])
{
	size_t i;

	for(i = from; i < to; i++)
		buf[i] ^= mask[i & 15];
}

/*==========================================
 *	3-Way (encrypt only, big endian words)
 *------------------------------------------
 */
static void threeway_theta(unsigned int *a)
{
	unsigned int b0, b1, b2;

	b0 = a[0] ^ (a[0] >> 16) ^ (a[1] << 16) ^ (a[1] >> 16) ^ (a[2] << 16) ^
	     (a[1] >> 24) ^ (a[2] << 8) ^ (a[2] >> 8) ^ (a[0] << 24) ^
	     (a[2] >> 16) ^ (a[0] << 16) ^ (a[2] >> 24) ^ (a[0] << 8);
	b1 = a[1] ^ (a[1] >> 16) ^ (a[2] << 16) ^ (a[2] >> 16) ^ (a[0] << 16) ^
	     (a[2] >> 24) ^ (a[0] << 8) ^ (a[0] >> 8) ^ (a[1] << 24) ^
	     (a[0] >> 16) ^ (a[1] << 16) ^ (a[0] >> 24) ^ (a[1] << 8);
	b2 = a[2] ^ (a[2] >> 16) ^ (a[0] << 16) ^ (a[0] >> 16) ^ (a[1] << 16) ^
	     (a[0] >> 24) ^ (a[1] << 8) ^ (a[1] >> 8) ^ (a[2] << 24) ^
	     (a[1] >> 16) ^ (a[2] << 16) ^ (a[1] >> 24) ^ (a[2] << 8);
	a[0] = b0;
	a[1] = b1;
	a[2] = b2;
}

static void threeway_rho(unsigned int *a)
{
	unsigned int b0, b1, b2;

	threeway_theta(a);
	/* pi_1 */
	a[0] = (a[0] >> 10) ^ (a[0] << 22);
	a[2] = (a[2] << 1) ^ (a[2] >> 31);
	/* gamma */
	b0 = a[0] ^ (a[1] | (~a[2]));
	b1 = a[1] ^ (a[2] | (~a[0]));
	b2 = a[2] ^ (a[0] | (~a[1]));
	/* pi_2 */
	a[0] = (b0 << 1) ^ (b0 >> 31);
	a[1] = b1;
	a[2] = (b2 >> 10) ^ (b2 << 22);
}

static void threeway_encrypt_block(const unsigned int k[3], const unsigned char in[12], unsigned char out[12])
{
	unsigned int a[3], rc = 0x0b0b;
	int i;

	a[0] = rd_be32(in);
	a[1] = rd_be32(in + 4);
	a[2] = rd_be32(in + 8);
	for(i = 0; i < 11; i++) {
		a[0] ^= k[0] ^ (rc << 16);
		a[1] ^= k[1];
		a[2] ^= k[2] ^ rc;
		threeway_rho(a);
		rc <<= 1;
		if(rc & 0x10000)
			rc ^= 0x11011;
	}
	a[0] ^= k[0] ^ (rc << 16);
	a[1] ^= k[1];
	a[2] ^= k[2] ^ rc;
	threeway_theta(a);
	wr_be32(out, a[0]);
	wr_be32(out + 4, a[1]);
	wr_be32(out + 8, a[2]);
}

static void threeway_cfb_decrypt(const unsigned char key[12], const unsigned char iv[12], unsigned char *buf, size_t len)
{
	unsigned int k[3];
	unsigned char reg[12], ks[12];
	size_t ofs;
	int i;

	k[0] = rd_be32(key);
	k[1] = rd_be32(key + 4);
	k[2] = rd_be32(key + 8);
	memcpy(reg, iv, 12);
	for(ofs = 0; ofs + 12 <= len; ofs += 12) {
		threeway_encrypt_block(k, reg, ks);
		memcpy(reg, buf + ofs, 12);
		for(i = 0; i < 12; i++)
			buf[ofs + i] ^= ks[i];
	}
}

/*==========================================
 *	TEA / XTEA CFB (big endian words, spec 6.1)
 *------------------------------------------
 */
static void tea_encrypt_block(const unsigned int k[4], unsigned char blk[8], int rounds)
{
	unsigned int v0 = rd_be32(blk), v1 = rd_be32(blk + 4), sum = 0;
	int i;

	for(i = 0; i < rounds; i++) {
		sum += GRFP_TEA_DELTA;
		v0 += ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
		v1 += ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
	}
	wr_be32(blk, v0);
	wr_be32(blk + 4, v1);
}

static void xtea_encrypt_block(const unsigned int k[4], unsigned char blk[8], int rounds)
{
	unsigned int v0 = rd_be32(blk), v1 = rd_be32(blk + 4), sum = 0;
	int i;

	for(i = 0; i < rounds; i++) {
		v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
		sum += GRFP_TEA_DELTA;
		v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum >> 11) & 3]);
	}
	wr_be32(blk, v0);
	wr_be32(blk + 4, v1);
}

static void tea_cfb_decrypt(int xtea, const unsigned char key[16], const unsigned char iv[8], unsigned char *buf, size_t len)
{
	unsigned int k[4];
	unsigned char reg[8], ks[8];
	size_t ofs;
	int i;

	for(i = 0; i < 4; i++)
		k[i] = rd_be32(key + i * 4);
	memcpy(reg, iv, 8);
	for(ofs = 0; ofs + 8 <= len; ofs += 8) {
		memcpy(ks, reg, 8);
		if(xtea)
			xtea_encrypt_block(k, ks, GRFP_TEA_ROUNDS);
		else
			tea_encrypt_block(k, ks, GRFP_TEA_ROUNDS);
		memcpy(reg, buf + ofs, 8);
		for(i = 0; i < 8; i++)
			buf[ofs + i] ^= ks[i];
	}
}

static void tea_cfb_encrypt(int xtea, const unsigned char key[16], const unsigned char iv[8], unsigned char *buf, size_t len)
{
	unsigned int k[4];
	unsigned char reg[8];
	size_t ofs;
	int i;

	for(i = 0; i < 4; i++)
		k[i] = rd_be32(key + i * 4);
	memcpy(reg, iv, 8);
	for(ofs = 0; ofs + 8 <= len; ofs += 8) {
		if(xtea)
			xtea_encrypt_block(k, reg, GRFP_TEA_ROUNDS);
		else
			tea_encrypt_block(k, reg, GRFP_TEA_ROUNDS);
		for(i = 0; i < 8; i++)
			buf[ofs + i] ^= reg[i];
		memcpy(reg, buf + ofs, 8);
	}
}

/*==========================================
 *	RC5-32 OFB (spec 6.4)
 *------------------------------------------
 */
#define RC5_ROTL(x, n) (((x) << ((n) & 31)) | ((x) >> ((32 - ((n) & 31)) & 31)))

static void rc5_setup(const unsigned char key[16], unsigned int *S, int rounds)
{
	unsigned int L[4], A = 0, B = 0;
	int t = 2 * (rounds + 1), i = 0, j = 0, n, k;

	for(k = 0; k < 4; k++)
		L[k] = rd_le32(key + k * 4);
	S[0] = 0xB7E15163u;
	for(k = 1; k < t; k++)
		S[k] = S[k - 1] + 0x9E3779B9u;
	n = 3 * (t > 4 ? t : 4);
	for(k = 0; k < n; k++) {
		A = S[i] = RC5_ROTL(S[i] + A + B, 3);
		B = L[j] = RC5_ROTL(L[j] + A + B, A + B);
		i = (i + 1) % t;
		j = (j + 1) % 4;
	}
}

static void rc5_encrypt_block(const unsigned int *S, int rounds, unsigned char blk[8])
{
	unsigned int A = rd_le32(blk) + S[0], B = rd_le32(blk + 4) + S[1];
	int i;

	for(i = 1; i <= rounds; i++) {
		A = RC5_ROTL(A ^ B, B) + S[2 * i];
		B = RC5_ROTL(B ^ A, A) + S[2 * i + 1];
	}
	wr_le32(blk, A);
	wr_le32(blk + 4, B);
}

static void rc5_ofb_crypt(const unsigned char key[16], const unsigned char iv[8], const unsigned char *in, unsigned char *out, size_t len)
{
	unsigned int S[2 * (GRFP_RC5_ROUNDS + 1)];
	unsigned char reg[8];
	size_t ofs;

	rc5_setup(key, S, GRFP_RC5_ROUNDS);
	memcpy(reg, iv, 8);
	for(ofs = 0; ofs < len; ofs++) {
		if((ofs & 7) == 0)
			rc5_encrypt_block(S, GRFP_RC5_ROUNDS, reg);
		out[ofs] = (unsigned char)(in[ofs] ^ reg[ofs & 7]);
	}
}

/*==========================================
 *	Archive keys
 *------------------------------------------
 */
int grf_protected_set_archive_key(unsigned int key_id, const unsigned char key[GRF_PROTECTED_KEY_SIZE])
{
	if(key_id == 0 || key_id >= GRFP_MAX_KEYS || key == NULL) {
		printf("grf_protected: invalid archive key id %u (1-%d).\n", key_id, GRFP_MAX_KEYS - 1);
		return 0;
	}
	memcpy(archive_keys[key_id], key, GRF_PROTECTED_KEY_SIZE);
	archive_key_present[key_id] = 1;

	return 1;
}

static int hexval(int c)
{
	if(c >= '0' && c <= '9') return c - '0';
	if(c >= 'a' && c <= 'f') return c - 'a' + 10;
	if(c >= 'A' && c <= 'F') return c - 'A' + 10;
	return -1;
}

int grf_protected_parse_key(const char *str)
{
	unsigned char key[GRF_PROTECTED_KEY_SIZE];
	unsigned long id;
	char *p;
	int i;

	if(str == NULL)
		return 0;

	id = strtoul(str, &p, 10);
	if(p == str)
		goto err;
	while(*p == ',' || *p == ' ' || *p == ':' || *p == '\t')
		p++;
	for(i = 0; i < GRF_PROTECTED_KEY_SIZE; i++) {
		int hi = hexval((unsigned char)p[i * 2]);
		int lo = (hi < 0) ? -1 : hexval((unsigned char)p[i * 2 + 1]);
		if(hi < 0 || lo < 0)
			goto err;
		key[i] = (unsigned char)((hi << 4) | lo);
	}
	p += GRF_PROTECTED_KEY_SIZE * 2;
	while(*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')
		p++;
	if(*p != '\0')
		goto err;

	return grf_protected_set_archive_key((unsigned int)id, key);

err:
	printf("grf_protected: bad archive key format (expected \"<id>,<%d hex chars>\").\n", GRF_PROTECTED_KEY_SIZE * 2);
	return 0;
}

int grf_protected_try_load_envelope(const void *blob, size_t len)
{
	const unsigned char *p = (const unsigned char *)blob;
	unsigned char slice[192];
	unsigned int magic, rec_size;
	int slice_len = -1;
	int off, n;

	if(p == NULL || (len != 84 && len != 148 && len != 212))
		return 0;

	magic = rd_le32(p);
	if(magic != 1 && magic != 257)
		return 0;
	rec_size = rd_le32(p + 12);
	if(rec_size != (unsigned int)(len - 20))
		return 0;

	switch(rec_size) {
	case 64:
		memcpy(slice, grf_key_block + 64, 64);
		slice_len = 64;
		break;
	case 128:
		memcpy(slice, grf_key_block + 128, 64);
		memcpy(slice + 64, grf_key_block + 64, 64);
		slice_len = 128;
		break;
	case 192:
		memcpy(slice, grf_key_block, 192);
		slice_len = 192;
		break;
	default:
		return 0;
	}

	if(XXH32(slice, (size_t)slice_len, 0) != rd_le32(p + 16)) {
		printf("grf_protected: key envelope XXH32 mismatch (len=%u, magic=%u).\n",
			(unsigned int)len, magic);
		return 0;
	}

	n = 0;
	for(off = 0; off < slice_len; off += 64) {
		unsigned int id = rd_le16(slice + off);

		if(id == 0 || id >= GRFP_MAX_KEYS)
			return 0;
		memcpy(archive_keys[id], slice + off + 4, GRF_PROTECTED_KEY_SIZE);
		archive_key_present[id] = 1;
		n++;
	}
	printf("grf_protected: loaded %d archive key%s from envelope.\n", n, (n > 1) ? "s" : "");
	return 1;
}

/*==========================================
 *	Header decrypt (spec 4)
 *------------------------------------------
 */
static int decrypt_header(unsigned char *hdr, const unsigned char name_hash[16])
{
	unsigned char iv[16];

	switch(hdr[1]) {
	case 1:
		aes128_cbc_decrypt(master_key, aes_iv_type1, hdr + 8, 96);
		break;
	case 2:
		aes128_cbc_decrypt(master_key, name_hash, hdr + 8, 96);
		break;
	case 15:
		native_hash(hdr + 4, 4, 0, iv);
		aes128_cbc_decrypt(master_key, iv, hdr + 8, 96);
		break;
	case 0x71:
		threeway_cfb_decrypt(threeway_key, threeway_iv, hdr + 8, 96);
		break;
	case 241:
		idea_cbc_decrypt(master_key, aes_iv_type1, hdr + 8, 96);
		break;
	default:
		printf("grf_protected: unknown header cipher %u.\n", (unsigned int)hdr[1]);
		return 0;
	}

	return 1;
}

/*==========================================
 *	Body transforms (spec 6)
 *------------------------------------------
 */
static void body_259(unsigned char *body, size_t len, const unsigned char *mat,
	const unsigned char name_hash[16], const unsigned char output_hash[16])
{
	unsigned char mask[16];
	size_t count = len - GRFP_PLAIN_HEAD;

	if(count > 1024)
		count = 1024;
	count &= ~(size_t)7;
	tea_cfb_decrypt(1, mat, mat + 32, body + GRFP_PLAIN_HEAD, count);

	idea_make_mask(output_hash, name_hash, mat + 50, mask);
	apply_mask(body, GRFP_PLAIN_HEAD, len, mask);
}

static void body_260(unsigned char *body, size_t len, const unsigned char *mat,
	const unsigned char name_hash[16], const unsigned char output_hash[16])
{
	unsigned char mask[16];
	size_t tail = len - GRFP_PLAIN_HEAD, ofs, count;

	if(tail >= 3072) {
		ofs   = 2176;
		count = 1024;
	} else {
		ofs   = GRFP_PLAIN_HEAD;
		count = tail & ~(size_t)7;
	}
	tea_cfb_decrypt(0, mat + 32, mat, body + ofs, count);

	idea_make_mask(name_hash, output_hash, mat + 48, mask);
	apply_mask(body, GRFP_PLAIN_HEAD, len, mask);
}

static int body_269(const unsigned char *in, size_t len, unsigned char *out, size_t compressed,
	const unsigned char *mat, const unsigned char name_hash[16], const unsigned char output_hash[16])
{
	unsigned char mask[16], tmp[GRFP_RC5_MAX + 8];
	size_t rc5_plain, rc5_len, pad, rest, i;

	idea_make_mask(name_hash, output_hash, mat + 50, mask);

	if(compressed <= GRFP_RC5_OFFSET) {
		if(len != compressed) {
			printf("grf_protected: cipher 269 body length mismatch (%u != %u).\n", (unsigned int)len, (unsigned int)compressed);
			return 0;
		}
		memcpy(out, in, compressed);
		apply_mask(out, GRFP_PLAIN_HEAD, compressed, mask);
		return 1;
	}

	rc5_plain = compressed - GRFP_RC5_OFFSET;
	if(rc5_plain > GRFP_RC5_MAX)
		rc5_plain = GRFP_RC5_MAX;
	pad     = 8 - (rc5_plain & 7);
	rc5_len = rc5_plain + pad;
	if(len != compressed + pad || len < GRFP_RC5_OFFSET + rc5_len) {
		printf("grf_protected: cipher 269 body length mismatch (%u, compressed %u, pad %u).\n",
			(unsigned int)len, (unsigned int)compressed, (unsigned int)pad);
		return 0;
	}

	memcpy(out, in, GRFP_RC5_OFFSET);
	apply_mask(out, GRFP_PLAIN_HEAD, GRFP_RC5_OFFSET, mask);

	rc5_ofb_crypt(mat + 16, mat, in + GRFP_RC5_OFFSET, tmp, rc5_len);
	for(i = rc5_len - pad; i < rc5_len; i++) {
		if(tmp[i] != pad) {
			printf("grf_protected: cipher 269 RC5 padding error.\n");
			return 0;
		}
	}
	memcpy(out + GRFP_RC5_OFFSET, tmp, rc5_plain);

	rest = compressed - (GRFP_RC5_OFFSET + rc5_plain);
	if(rest > 0) {
		memcpy(out + GRFP_RC5_OFFSET + rc5_plain, in + GRFP_RC5_OFFSET + rc5_len, rest);
		apply_mask(out, GRFP_RC5_OFFSET + rc5_plain, compressed, mask);
	}

	return 1;
}

/*==========================================
 *	Protected entry decode (spec 10)
 *------------------------------------------
 */
void *grf_protected_decode(const unsigned char *payload, unsigned int payload_len,
	const char *raw_name, unsigned int name_len,
	unsigned int expected_size, unsigned int *out_size)
{
	unsigned char hdr[GRFP_HEADER_SIZE];
	unsigned char name_hash[16], output_hash[16], check_hash[16], material[GRF_PROTECTED_KEY_SIZE];
	unsigned char *body = NULL, *plain = NULL, *out = NULL;
	unsigned int body_cipher, compression, flags, padded, compressed, size, key_id;
	int i;

	if(out_size != NULL)
		*out_size = 0;

	if(payload == NULL || raw_name == NULL || payload_len < GRFP_HEADER_SIZE) {
		printf("grf_protected: payload too short (%u bytes).\n", payload_len);
		return NULL;
	}
	memcpy(hdr, payload, GRFP_HEADER_SIZE);

	if(hdr[0] != 1) {
		printf("grf_protected: unsupported header version %u.\n", (unsigned int)hdr[0]);
		return NULL;
	}

	native_hash(raw_name, name_len, 0, name_hash);

	if(!decrypt_header(hdr, name_hash))
		return NULL;
	if(XXH32(hdr + 8, 96, 0) != rd_le32(hdr + 4)) {
		printf("grf_protected: header checksum mismatch (cipher %u).\n", (unsigned int)hdr[1]);
		return NULL;
	}

	body_cipher = rd_le16(hdr + 8);
	compression = hdr[10];
	flags       = hdr[11];
	padded      = rd_le32(hdr + 12);
	compressed  = rd_le32(hdr + 16);
	size        = rd_le32(hdr + 20);
	memcpy(output_hash, hdr + 24, 16);
	key_id      = rd_le16(hdr + 40);

	if(padded != payload_len - GRFP_HEADER_SIZE) {
		printf("grf_protected: payload length mismatch (%u != 104 + %u).\n", payload_len, padded);
		return NULL;
	}
	if(compressed > padded) {
		printf("grf_protected: compressed length %u exceeds body length %u.\n", compressed, padded);
		return NULL;
	}
	if(size != expected_size) {
		printf("grf_protected: size mismatch (header %u, table %u).\n", size, expected_size);
		return NULL;
	}
	if(size > GRFP_MAX_SIZE) {
		printf("grf_protected: size %u exceeds limit.\n", size);
		return NULL;
	}
	if(flags & ~1u) {
		printf("grf_protected: unsupported flags 0x%02x.\n", flags);
		return NULL;
	}
	if(compression > 2) {
		printf("grf_protected: unsupported compression %u.\n", compression);
		return NULL;
	}
	if(compression == 0 && compressed != size) {
		printf("grf_protected: stored length mismatch (%u != %u).\n", compressed, size);
		return NULL;
	}
	if(body_cipher != 259 && body_cipher != 260 && body_cipher != 269) {
		printf("grf_protected: unsupported body cipher %u.\n", body_cipher);
		return NULL;
	}

	if(key_id == 0) {
		memcpy(material, hdr + 44, GRF_PROTECTED_KEY_SIZE);
	} else if(key_id < GRFP_MAX_KEYS && archive_key_present[key_id]) {
		memcpy(material, archive_keys[key_id], GRF_PROTECTED_KEY_SIZE);
	} else {
		const unsigned char *defkey = NULL;

		/* body 259/260/269 → 既定鍵 */
		if(body_cipher == 259 || body_cipher == 260 || body_cipher == 269)
			defkey = grf_default_key(key_id);
		if(defkey == NULL) {
			printf("grf_protected: archive key %u is not set.\n", key_id);
			return NULL;
		}
		memcpy(material, defkey, GRF_PROTECTED_KEY_SIZE);
	}
	if(flags & 1) {
		for(i = 0; i < GRF_PROTECTED_KEY_SIZE; i++)
			material[i] ^= output_hash[i & 15];
	}

	body = (unsigned char *)aMalloc(padded + 1);
	memcpy(body, payload + GRFP_HEADER_SIZE, padded);

	if(compressed <= GRFP_PLAIN_HEAD) {
		plain = body;
	} else if(body_cipher == 269) {
		plain = (unsigned char *)aMalloc(compressed);
		if(!body_269(body, padded, plain, compressed, material, name_hash, output_hash))
			goto err;
	} else {
		if(body_cipher == 259)
			body_259(body, padded, material, name_hash, output_hash);
		else
			body_260(body, padded, material, name_hash, output_hash);
		plain = body;
	}

	out = (unsigned char *)aCalloc(size + 1024, sizeof(unsigned char));
	switch(compression) {
	case 0:
		memcpy(out, plain, size);
		break;
	case 1:
		{
			unsigned long dlen = (unsigned long)size;
			int ret = decode_zip((char *)out, &dlen, (const char *)plain, compressed);
			if(ret != 0 || dlen != (unsigned long)size) {
				printf("grf_protected: zlib inflate failed (ret %d, %lu != %u).\n", ret, dlen, size);
				goto err;
			}
		}
		break;
	case 2:
		{
			int ret = LZ4_decompress_safe((const char *)plain, (char *)out, (int)compressed, (int)size);
			if(ret < 0 || (unsigned int)ret != size) {
				printf("grf_protected: LZ4 decompress failed (ret %d, size %u).\n", ret, size);
				goto err;
			}
		}
		break;
	}

	native_hash(out, size, 0, check_hash);
	if(memcmp(check_hash, output_hash, 16) != 0) {
		printf("grf_protected: output hash mismatch (body cipher %u, key %u).\n", body_cipher, key_id);
		goto err;
	}

	if(plain != body)
		aFree(plain);
	aFree(body);
	if(out_size != NULL)
		*out_size = size;

	return out;

err:
	if(plain != NULL && plain != body)
		aFree(plain);
	if(body != NULL)
		aFree(body);
	if(out != NULL)
		aFree(out);

	return NULL;
}

/*==========================================
 *	Protected entry encode (for unit tests)
 *------------------------------------------
 */
void grf_protected_seal_header_for_test(unsigned char hdr[GRF_PROTECTED_HEADER_SIZE])
{
	hdr[0] = 1;
	hdr[1] = 1;
	wr_le32(hdr + 4, XXH32(hdr + 8, 96, 0));
	aes128_cbc_encrypt(master_key, aes_iv_type1, hdr + 8, 96);
}

unsigned char *grf_protected_encode_for_test(
	const unsigned char *plain, unsigned int plain_len,
	const char *raw_name, unsigned int name_len,
	unsigned int body_cipher,
	unsigned int compression,
	unsigned int key_id,
	const unsigned char key60[GRF_PROTECTED_KEY_SIZE],
	unsigned int *out_payload_len)
{
	unsigned char hdr[GRFP_HEADER_SIZE];
	unsigned char name_hash[16], output_hash[16], mask[16];
	unsigned char *comp = NULL, *payload, *body;
	unsigned int compressed, padded;
	size_t rc5_plain = 0, pad = 0;

	if(out_payload_len != NULL)
		*out_payload_len = 0;

	if(plain == NULL || raw_name == NULL || key60 == NULL || plain_len > GRFP_MAX_SIZE)
		return NULL;
	if(body_cipher != 259 && body_cipher != 260 && body_cipher != 269)
		return NULL;
	if(key_id >= GRFP_MAX_KEYS)
		return NULL;

	switch(compression) {
	case 0:
		comp = (unsigned char *)aMalloc(plain_len + 1);
		memcpy(comp, plain, plain_len);
		compressed = plain_len;
		break;
	case 2:
		{
			int bound = LZ4_compressBound((int)plain_len);
			int ret;

			if(bound <= 0)
				return NULL;
			comp = (unsigned char *)aMalloc((size_t)bound);
			ret = LZ4_compress_default((const char *)plain, (char *)comp, (int)plain_len, bound);
			if(ret <= 0) {
				aFree(comp);
				return NULL;
			}
			compressed = (unsigned int)ret;
		}
		break;
	default:
		return NULL;
	}

	padded = compressed;
	if(body_cipher == 269 && compressed > GRFP_RC5_OFFSET) {
		rc5_plain = compressed - GRFP_RC5_OFFSET;
		if(rc5_plain > GRFP_RC5_MAX)
			rc5_plain = GRFP_RC5_MAX;
		pad     = 8 - (rc5_plain & 7);
		padded += (unsigned int)pad;
	}

	payload = (unsigned char *)aCalloc(GRFP_HEADER_SIZE + padded + 1, sizeof(unsigned char));
	body    = payload + GRFP_HEADER_SIZE;
	memcpy(body, comp, compressed);

	native_hash(raw_name, name_len, 0, name_hash);
	native_hash(plain, plain_len, 0, output_hash);

	if(compressed <= GRFP_PLAIN_HEAD) {
		/* stored as-is (decoder skips body transform) */
	} else if(body_cipher == 269) {
		idea_make_mask(name_hash, output_hash, key60 + 50, mask);
		if(compressed <= GRFP_RC5_OFFSET) {
			apply_mask(body, GRFP_PLAIN_HEAD, compressed, mask);
		} else {
			unsigned char tmp[GRFP_RC5_MAX + 8];
			size_t rest = compressed - (GRFP_RC5_OFFSET + rc5_plain), i;

			apply_mask(body, GRFP_PLAIN_HEAD, GRFP_RC5_OFFSET, mask);
			memcpy(tmp, comp + GRFP_RC5_OFFSET, rc5_plain);
			memset(tmp + rc5_plain, (int)pad, pad);
			rc5_ofb_crypt(key60 + 16, key60, tmp, body + GRFP_RC5_OFFSET, rc5_plain + pad);
			for(i = 0; i < rest; i++) {
				size_t pos = GRFP_RC5_OFFSET + rc5_plain + i;
				body[pos + pad] = (unsigned char)(comp[pos] ^ mask[pos & 15]);
			}
		}
	} else if(body_cipher == 259) {
		size_t count = padded - GRFP_PLAIN_HEAD;

		if(count > 1024)
			count = 1024;
		count &= ~(size_t)7;
		idea_make_mask(output_hash, name_hash, key60 + 50, mask);
		apply_mask(body, GRFP_PLAIN_HEAD, padded, mask);
		tea_cfb_encrypt(1, key60, key60 + 32, body + GRFP_PLAIN_HEAD, count);
	} else {
		size_t tail = padded - GRFP_PLAIN_HEAD, ofs, count;

		if(tail >= 3072) {
			ofs   = 2176;
			count = 1024;
		} else {
			ofs   = GRFP_PLAIN_HEAD;
			count = tail & ~(size_t)7;
		}
		idea_make_mask(name_hash, output_hash, key60 + 48, mask);
		apply_mask(body, GRFP_PLAIN_HEAD, padded, mask);
		tea_cfb_encrypt(0, key60 + 32, key60, body + ofs, count);
	}
	aFree(comp);

	memset(hdr, 0, sizeof(hdr));
	hdr[8]  = (unsigned char)body_cipher;
	hdr[9]  = (unsigned char)(body_cipher >> 8);
	hdr[10] = (unsigned char)compression;
	hdr[11] = 0;
	wr_le32(hdr + 12, padded);
	wr_le32(hdr + 16, compressed);
	wr_le32(hdr + 20, plain_len);
	memcpy(hdr + 24, output_hash, 16);
	hdr[40] = (unsigned char)key_id;
	hdr[41] = (unsigned char)(key_id >> 8);
	if(key_id == 0)
		memcpy(hdr + 44, key60, GRF_PROTECTED_KEY_SIZE);
	grf_protected_seal_header_for_test(hdr);
	memcpy(payload, hdr, GRFP_HEADER_SIZE);

	if(out_payload_len != NULL)
		*out_payload_len = GRFP_HEADER_SIZE + padded;

	return payload;
}
