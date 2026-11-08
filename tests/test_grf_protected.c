#include <stdlib.h>
#include <string.h>

#include "unity.h"
#include "malloc.h"
#include "grf_protected.h"

static const char test_name[] = "data\\test_protected.gat";

static unsigned char test_key[GRF_PROTECTED_KEY_SIZE];

static void init_key(void)
{
	int i;

	for (i = 0; i < GRF_PROTECTED_KEY_SIZE; i++)
		test_key[i] = (unsigned char)(i * 37 + 11);
}

static unsigned char *make_plain(unsigned int len, int compressible)
{
	unsigned char *p = (unsigned char *)malloc(len + 1);
	unsigned int i, seed = 0x12345678u;

	TEST_ASSERT_NOT_NULL(p);
	for (i = 0; i < len; i++) {
		if (compressible) {
			p[i] = (unsigned char)("protected grf "[i % 14]);
		} else {
			seed = seed * 1103515245u + 12345u;
			p[i] = (unsigned char)(seed >> 16);
		}
	}
	return p;
}

static unsigned char *encode(const unsigned char *plain, unsigned int len,
	unsigned int body_cipher, unsigned int compression, unsigned int *payload_len)
{
	unsigned char *payload;

	init_key();
	payload = grf_protected_encode_for_test(plain, len, test_name, (unsigned int)strlen(test_name),
		body_cipher, compression, 0, test_key, payload_len);
	TEST_ASSERT_NOT_NULL(payload);
	TEST_ASSERT_TRUE(*payload_len >= GRF_PROTECTED_HEADER_SIZE);
	return payload;
}

static void roundtrip(unsigned int len, unsigned int body_cipher, unsigned int compression, int compressible)
{
	unsigned char *plain = make_plain(len, compressible);
	unsigned int payload_len = 0, out_size = 0;
	unsigned char *payload = encode(plain, len, body_cipher, compression, &payload_len);
	unsigned char *out;

	out = (unsigned char *)grf_protected_decode(payload, payload_len,
		test_name, (unsigned int)strlen(test_name), len, &out_size);
	TEST_ASSERT_NOT_NULL(out);
	TEST_ASSERT_EQUAL_UINT(len, out_size);
	TEST_ASSERT_EQUAL_MEMORY(plain, out, len);

	aFree(out);
	aFree(payload);
	free(plain);
}

static void *decode_payload(const unsigned char *payload, unsigned int payload_len, unsigned int expected)
{
	return grf_protected_decode(payload, payload_len, test_name, (unsigned int)strlen(test_name), expected, NULL);
}

static void build_header(unsigned char *hdr, unsigned int compression,
	unsigned int padded, unsigned int compressed, unsigned int size)
{
	init_key();
	memset(hdr, 0, GRF_PROTECTED_HEADER_SIZE);
	hdr[8]  = 269 & 0xff;
	hdr[9]  = 269 >> 8;
	hdr[10] = (unsigned char)compression;
	hdr[12] = (unsigned char)padded;
	hdr[13] = (unsigned char)(padded >> 8);
	hdr[14] = (unsigned char)(padded >> 16);
	hdr[15] = (unsigned char)(padded >> 24);
	hdr[16] = (unsigned char)compressed;
	hdr[17] = (unsigned char)(compressed >> 8);
	hdr[18] = (unsigned char)(compressed >> 16);
	hdr[19] = (unsigned char)(compressed >> 24);
	hdr[20] = (unsigned char)size;
	hdr[21] = (unsigned char)(size >> 8);
	hdr[22] = (unsigned char)(size >> 16);
	hdr[23] = (unsigned char)(size >> 24);
	memcpy(hdr + 44, test_key, GRF_PROTECTED_KEY_SIZE);
	grf_protected_seal_header_for_test(hdr);
}

void test_grf_protected_roundtrip_stored_269(void)
{
	roundtrip(64, 269, 0, 0);
	roundtrip(128, 269, 0, 0);
	roundtrip(129, 269, 0, 0);
	roundtrip(2176, 269, 0, 0);
	roundtrip(2177, 269, 0, 0);
	roundtrip(2200, 269, 0, 0);
	roundtrip(2184, 269, 0, 0);	/* rc5 part is a multiple of 8 (full pad block) */
	roundtrip(4000, 269, 0, 0);	/* tail after rc5 window */
}

void test_grf_protected_roundtrip_stored_259_260(void)
{
	roundtrip(100, 259, 0, 0);
	roundtrip(100, 260, 0, 0);
	roundtrip(1000, 259, 0, 0);
	roundtrip(1000, 260, 0, 0);
	roundtrip(3500, 259, 0, 0);
	roundtrip(3500, 260, 0, 0);
}

void test_grf_protected_roundtrip_lz4_269(void)
{
	roundtrip(100, 269, 2, 0);
	roundtrip(1000, 269, 2, 0);
	roundtrip(20000, 269, 2, 1);
	roundtrip(3000, 269, 2, 0);
}

void test_grf_protected_archive_key(void)
{
	unsigned char *plain = make_plain(3000, 0);
	unsigned int payload_len = 0;
	unsigned char *payload, *out;

	init_key();
	TEST_ASSERT_TRUE(grf_protected_set_archive_key(200, test_key));
	payload = grf_protected_encode_for_test(plain, 3000, test_name, (unsigned int)strlen(test_name),
		269, 0, 200, test_key, &payload_len);
	TEST_ASSERT_NOT_NULL(payload);

	out = (unsigned char *)decode_payload(payload, payload_len, 3000);
	TEST_ASSERT_NOT_NULL(out);
	TEST_ASSERT_EQUAL_MEMORY(plain, out, 3000);

	aFree(out);
	aFree(payload);
	free(plain);
}

void test_grf_protected_reject_short_payload(void)
{
	unsigned char *plain = make_plain(64, 0);
	unsigned int payload_len = 0;
	unsigned char *payload = encode(plain, 64, 269, 0, &payload_len);

	TEST_ASSERT_NULL(decode_payload(payload, GRF_PROTECTED_HEADER_SIZE - 1, 64));
	TEST_ASSERT_NULL(decode_payload(payload, payload_len - 1, 64));
	TEST_ASSERT_NULL(decode_payload(NULL, payload_len, 64));

	aFree(payload);
	free(plain);
}

void test_grf_protected_reject_size_mismatch(void)
{
	unsigned char *plain = make_plain(500, 0);
	unsigned int payload_len = 0;
	unsigned char *payload = encode(plain, 500, 269, 0, &payload_len);

	TEST_ASSERT_NULL(decode_payload(payload, payload_len, 499));
	TEST_ASSERT_NULL(decode_payload(payload, payload_len, 501));

	aFree(payload);
	free(plain);
}

void test_grf_protected_reject_name_mismatch(void)
{
	unsigned char *plain = make_plain(500, 0);
	unsigned int payload_len = 0;
	unsigned char *payload = encode(plain, 500, 269, 0, &payload_len);
	const char *other = "data\\other.gat";

	TEST_ASSERT_NULL(grf_protected_decode(payload, payload_len, other, (unsigned int)strlen(other), 500, NULL));

	aFree(payload);
	free(plain);
}

void test_grf_protected_reject_rc5_padding(void)
{
	unsigned char *plain = make_plain(2177, 0);
	unsigned int payload_len = 0;
	unsigned char *payload = encode(plain, 2177, 269, 0, &payload_len);

	/* rc5 window = 1 byte + 7 pad bytes; OFB flips the decrypted pad byte */
	TEST_ASSERT_EQUAL_UINT(GRF_PROTECTED_HEADER_SIZE + 2177 + 7, payload_len);
	payload[payload_len - 1] ^= 0x01;
	TEST_ASSERT_NULL(decode_payload(payload, payload_len, 2177));

	aFree(payload);
	free(plain);
}

void test_grf_protected_reject_corrupt_body(void)
{
	unsigned char *plain = make_plain(1000, 0);
	unsigned int payload_len = 0;
	unsigned char *payload = encode(plain, 1000, 269, 0, &payload_len);

	payload[GRF_PROTECTED_HEADER_SIZE + 500] ^= 0x80;
	TEST_ASSERT_NULL(decode_payload(payload, payload_len, 1000));

	aFree(payload);
	free(plain);
}

void test_grf_protected_reject_corrupt_header(void)
{
	unsigned char *plain = make_plain(64, 0);
	unsigned int payload_len = 0;
	unsigned char *payload = encode(plain, 64, 269, 0, &payload_len);

	payload[20] ^= 0x01;
	TEST_ASSERT_NULL(decode_payload(payload, payload_len, 64));

	aFree(payload);
	free(plain);
}

void test_grf_protected_reject_bad_header_fields(void)
{
	unsigned char payload[GRF_PROTECTED_HEADER_SIZE + 16];
	unsigned int big = GRF_PROTECTED_MAX_PLAINTEXT + 1u;

	memset(payload, 0, sizeof(payload));

	/* compressed > padded */
	build_header(payload, 0, 16, 32, 32);
	TEST_ASSERT_NULL(decode_payload(payload, sizeof(payload), 32));

	/* size above limit (matches table size) */
	build_header(payload, 2, 16, 16, big);
	TEST_ASSERT_NULL(decode_payload(payload, sizeof(payload), big));

	/* unsupported compression */
	build_header(payload, 3, 16, 16, 16);
	TEST_ASSERT_NULL(decode_payload(payload, sizeof(payload), 16));

	/* stored length != size */
	build_header(payload, 0, 16, 8, 16);
	TEST_ASSERT_NULL(decode_payload(payload, sizeof(payload), 16));

	/* zlib body: unit tests link no zlib, inflate stub fails */
	build_header(payload, 1, 16, 16, 16);
	TEST_ASSERT_NULL(decode_payload(payload, sizeof(payload), 16));
}

void test_grf_protected_encode_rejects_unsupported(void)
{
	unsigned char plain[16];
	unsigned int payload_len = 1;

	memset(plain, 0, sizeof(plain));
	init_key();
	TEST_ASSERT_NULL(grf_protected_encode_for_test(plain, sizeof(plain), test_name, (unsigned int)strlen(test_name),
		269, 1, 0, test_key, &payload_len));
	TEST_ASSERT_EQUAL_UINT(0, payload_len);
	TEST_ASSERT_NULL(grf_protected_encode_for_test(plain, sizeof(plain), test_name, (unsigned int)strlen(test_name),
		258, 0, 0, test_key, &payload_len));
	TEST_ASSERT_NULL(grf_protected_encode_for_test(plain, GRF_PROTECTED_MAX_PLAINTEXT + 1u, test_name,
		(unsigned int)strlen(test_name), 269, 0, 0, test_key, &payload_len));
}
