#ifndef	_GRFIO_H_
#define	_GRFIO_H_

void grfio_init(char*);			// GRFIO Initialize
int grfio_add(char*,char*);		// GRFIO Resource file add
void* grfio_read(char*);		// GRFIO data file read
void* grfio_reads(char*,int*);	// GRFIO data file read & size get
int grfio_size(char*);			// GRFIO data file size get

int  decode_zip(char *dest, unsigned long* destLen, const char* source, unsigned long sourceLen);
int  encode_zip(char *dest, unsigned long* destLen, const char* source, unsigned long sourceLen);

void grfio_load_zlib(void);
unsigned long grfio_crc32(const char *buf, unsigned int len);

// Accessor to GRF filenames
int grfio_setdatafile(const char *w1, const char *w2);

#endif	// _GRFIO_H_
