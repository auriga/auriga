#ifndef _MD5CALC_H_
#define _MD5CALC_H_

void MD5_Binary(const char *string, int len, char *output);

void MD5_String(const char *string, char *output);
void MD5_String2binary(const char *string, char *output);

void HMAC_MD5_Binary( const char *key, int keylen, const char *str, int len, char *output );

#endif
