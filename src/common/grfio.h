#ifndef	_GRFIO_H_
#define	_GRFIO_H_

void grfio_init(const char*);		// GRFIO Initialize
int grfio_add(const char*);	// GRFIO Resource file add
void* grfio_read(const char*);	// GRFIO data file read
void* grfio_reads(const char*,int*);	// GRFIO data file read & size get
int grfio_size(const char*);		// GRFIO data file size get

int decode_zip(char *dest, unsigned long* destLen, const char* source, unsigned long sourceLen);
int encode_zip(char *dest, unsigned long* destLen, const char* source, unsigned long sourceLen);

void grfio_load_zlib(void);
unsigned long grfio_crc32(const char *buf, unsigned int len);

#endif	// _GRFIO_H_
