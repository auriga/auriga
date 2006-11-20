/*********************************************************************
 *
 *		Ragnarok Online Emulator : grfio.c -- grf file I/O Module
 *--------------------------------------------------------------------
 *		special need library : zlib
 *********************************************************************
 *	$Id: grfio.c,v 1.4 2003/11/10 23:32:44 jmb Exp $
 *
 *	2002/12/18 ... 原版
 *	2003/01/23 ... コード修正
 *	2003/02/01 ... LocalFile及び複数GRFチェック処理を追加,暗号解読処理を改良
 *	2003/02/02 ... grfが無くても止まらないように修正
 *	2003/02/02 ... grf読み込み指定を後から追加できるように修正(grfio_add関数追加)
 *	2003/02/03 ... grfio_resourcecheck処理時、エントリ追加処理方法を修正
 *	2003/02/05 ... grfio_init内処理の変更
 *	2003/02/23 ... ローカルファイルチェックをGRFIO_LOCALでスイッチ(デフォを機能Offに)
 *      2003/10/21 ・・・ αクライアントのデータを読むようにした。
 *	2003/11/10 ... Ready new grf format.
 *	2003/11/11 ... version check fix & bug fix
 *	2006/05/27 ... Reading of customed GRF (by Yor)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include "mmo.h"
#include "grfio.h"
#include "malloc.h"

#define GRF_HEADER "Master of Magic"

#if defined(_WIN32) && !defined(LOCALZLIB)
	#include <windows.h>
	#include "zlib\zlib.h"
	HINSTANCE zlib_dll;
	#define zlib_inflateInit(strm) zlib_inflateInit_((strm),ZLIB_VERSION, sizeof(z_stream))
	#define zlib_deflateInit(strm, level) zlib_deflateInit_((strm),(level),ZLIB_VERSION,sizeof(z_stream))

	int (WINAPI* zlib_inflateInit_)      (z_streamp strm, const char *version, int stream_size);
	int (WINAPI* zlib_inflate)           (z_streamp strm, int flush);
	int (WINAPI* zlib_inflateEnd)        (z_streamp strm);
	int (WINAPI* zlib_deflateInit_)      (z_streamp strm, int level, const char *version, int stream_size);
	int (WINAPI* zlib_deflate)           (z_streamp strm, int flush);
	int (WINAPI* zlib_deflateEnd)        (z_streamp strm);
	unsigned long (WINAPI* zlib_crc32)   (unsigned long crc, const char *buf, unsigned int len);
#else
	#ifdef LOCALZLIB
		#include "zlib/zlib.h"
	#else
		#include <zlib.h>
	#endif

	#define zlib_inflateInit inflateInit
	#define zlib_inflate     inflate
	#define zlib_inflateEnd  inflateEnd
	#define zlib_deflateInit deflateInit
	#define zlib_deflate     deflate
	#define zlib_deflateEnd  deflateEnd
	#define zlib_crc32       crc32
#endif

#ifdef MEMWATCH
#include "memwatch.h"
#endif

#ifndef BYTE
	typedef unsigned char BYTE;
#endif

#ifndef WORD
	typedef unsigned short WORD;
#endif

#ifndef DWORD
	typedef unsigned long DWORD;
#endif

static char data_file[1024] = ""; // data.grf
static char adata_file[1024] = ""; // adata.grf
static char sdata_file[1024] = ""; // sdata.grf

// accessor to data_file,adata_file,sdata_file
char *grfio_setdatafile(const char *str){ strncpy(data_file, str, sizeof(data_file)); data_file[sizeof(data_file)-1] = '\0'; return data_file; }
char *grfio_setadatafile(const char *str){ strncpy(adata_file, str, sizeof(adata_file)); adata_file[sizeof(adata_file)-1] = '\0'; return adata_file; }
char *grfio_setsdatafile(const char *str){ strncpy(sdata_file, str, sizeof(sdata_file)); sdata_file[sizeof(sdata_file)-1] = '\0'; return sdata_file; }

//----------------------------
//	file entry table struct
//----------------------------
typedef struct {
	int  srclen; // compressed size
	int  srclen_aligned;
	int  declen; // original size
	int  srcpos;
	int  next; // -1: no next, 0+: pointer to index of next value
	char cycle;
	char type;
	char fn[128-4*5]; // file name
	char gentry; // read grf file select
} FILELIST;
// gentry ... 0  :ローカルファイルより取得
//            1>=:gentry_table[gentry-1]のリソースファイルより取得
//            1<=:ローカルファイルをチェック
//                   有れば0に再セットして以降ローカルファイルより取得
//                   無ければ符号反転して再セットし、1>=と同じくリソースファイルより取得

// ※FILELIST.gentryをcharで定義しているのでgrfio_addで追加できる上限は127コまでになります
#define GENTRY_LIMIT 127
//#define FILELIST_LIMIT 65535 // 仮上限,理論上上限は2G

static FILELIST *filelist = NULL;
static int filelist_entrys = 0;
static int filelist_maxentry = 0;

static char **gentry_table = NULL;
static int gentry_entrys = 0;
static int gentry_maxentry = 0;

//----------------------------
//	file list hash table
//----------------------------
static int filelist_hash[256]; // hash table

//----------------------------
//	grf decode data table
//----------------------------
static unsigned char BitMaskTable[8] = {
	0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
};

static char	BitSwapTable1[64] = {
	58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
	57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7
};
static char	BitSwapTable2[64] = {
	40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
	38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
	36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
	34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25
};
static char	BitSwapTable3[32] = {
	16,  7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
	 2,  8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
};

static unsigned char NibbleData[4][64]={
	{
		0xef, 0x03, 0x41, 0xfd, 0xd8, 0x74, 0x1e, 0x47,  0x26, 0xef, 0xfb, 0x22, 0xb3, 0xd8, 0x84, 0x1e,
		0x39, 0xac, 0xa7, 0x60, 0x62, 0xc1, 0xcd, 0xba,  0x5c, 0x96, 0x90, 0x59, 0x05, 0x3b, 0x7a, 0x85,
		0x40, 0xfd, 0x1e, 0xc8, 0xe7, 0x8a, 0x8b, 0x21,  0xda, 0x43, 0x64, 0x9f, 0x2d, 0x14, 0xb1, 0x72,
		0xf5, 0x5b, 0xc8, 0xb6, 0x9c, 0x37, 0x76, 0xec,  0x39, 0xa0, 0xa3, 0x05, 0x52, 0x6e, 0x0f, 0xd9,
	}, {
		0xa7, 0xdd, 0x0d, 0x78, 0x9e, 0x0b, 0xe3, 0x95,  0x60, 0x36, 0x36, 0x4f, 0xf9, 0x60, 0x5a, 0xa3,
		0x11, 0x24, 0xd2, 0x87, 0xc8, 0x52, 0x75, 0xec,  0xbb, 0xc1, 0x4c, 0xba, 0x24, 0xfe, 0x8f, 0x19,
		0xda, 0x13, 0x66, 0xaf, 0x49, 0xd0, 0x90, 0x06,  0x8c, 0x6a, 0xfb, 0x91, 0x37, 0x8d, 0x0d, 0x78,
		0xbf, 0x49, 0x11, 0xf4, 0x23, 0xe5, 0xce, 0x3b,  0x55, 0xbc, 0xa2, 0x57, 0xe8, 0x22, 0x74, 0xce,
	}, {
		0x2c, 0xea, 0xc1, 0xbf, 0x4a, 0x24, 0x1f, 0xc2,  0x79, 0x47, 0xa2, 0x7c, 0xb6, 0xd9, 0x68, 0x15,
		0x80, 0x56, 0x5d, 0x01, 0x33, 0xfd, 0xf4, 0xae,  0xde, 0x30, 0x07, 0x9b, 0xe5, 0x83, 0x9b, 0x68,
		0x49, 0xb4, 0x2e, 0x83, 0x1f, 0xc2, 0xb5, 0x7c,  0xa2, 0x19, 0xd8, 0xe5, 0x7c, 0x2f, 0x83, 0xda,
		0xf7, 0x6b, 0x90, 0xfe, 0xc4, 0x01, 0x5a, 0x97,  0x61, 0xa6, 0x3d, 0x40, 0x0b, 0x58, 0xe6, 0x3d,
	}, {
		0x4d, 0xd1, 0xb2, 0x0f, 0x28, 0xbd, 0xe4, 0x78,  0xf6, 0x4a, 0x0f, 0x93, 0x8b, 0x17, 0xd1, 0xa4,
		0x3a, 0xec, 0xc9, 0x35, 0x93, 0x56, 0x7e, 0xcb,  0x55, 0x20, 0xa0, 0xfe, 0x6c, 0x89, 0x17, 0x62,
		0x17, 0x62, 0x4b, 0xb1, 0xb4, 0xde, 0xd1, 0x87,  0xc9, 0x14, 0x3c, 0x4a, 0x7e, 0xa8, 0xe2, 0x7d,
		0xa0, 0x9f, 0xf6, 0x5c, 0x6a, 0x09, 0x8d, 0xf0,  0x0f, 0xe3, 0x53, 0x25, 0x95, 0x36, 0x28, 0xcb,
	}
};
/*-----------------
 *	long data get
 */
static unsigned int getlong(unsigned char *p)
{
	//return *p+p[1]*256+(p[2]+p[3]*256)*65536;
	return p[0] +
	      (p[1] << 0x08) +
	      (p[2] << 0x10) +
	      (p[3] << 0x18); // speeder
}

/*==========================================
 *	Grf data decode : Subs
 *------------------------------------------
 */
static void NibbleSwap(BYTE *Src, int len)
{
	for(;0<len;len--,Src++) {
		*Src = (*Src>>4) | (*Src<<4);
	}

	return;
}

static void BitConvert(BYTE *Src,char *BitSwapTable)
{
	int lop,prm;
	BYTE tmp[8];
	*(DWORD*)tmp=*(DWORD*)(tmp+4)=0;
	for(lop=0;lop!=64;lop++) {
		prm = BitSwapTable[lop]-1;
		if (Src[(prm >> 3) & 7] & BitMaskTable[prm & 7]) {
			tmp[(lop >> 3) & 7] |= BitMaskTable[lop & 7];
		}
	}
	*(DWORD*)Src     = *(DWORD*)tmp;
	*(DWORD*)(Src+4) = *(DWORD*)(tmp+4);

	return;
}

static void BitConvert4(BYTE *Src)
{
	int lop,prm;
	BYTE tmp[8];
	tmp[0] = ((Src[7]<<5) | (Src[4]>>3)) & 0x3f;	// ..0 vutsr
	tmp[1] = ((Src[4]<<1) | (Src[5]>>7)) & 0x3f;	// ..srqpo n
	tmp[2] = ((Src[4]<<5) | (Src[5]>>3)) & 0x3f;	// ..o nmlkj
	tmp[3] = ((Src[5]<<1) | (Src[6]>>7)) & 0x3f;	// ..kjihg f
	tmp[4] = ((Src[5]<<5) | (Src[6]>>3)) & 0x3f;	// ..g fedcb
	tmp[5] = ((Src[6]<<1) | (Src[7]>>7)) & 0x3f;	// ..cba98 7
	tmp[6] = ((Src[6]<<5) | (Src[7]>>3)) & 0x3f;	// ..8 76543
	tmp[7] = ((Src[7]<<1) | (Src[4]>>7)) & 0x3f;	// ..43210 v

	for(lop=0;lop!=4;lop++) {
		tmp[lop] = (NibbleData[lop][tmp[lop*2]] & 0xf0)
		         | (NibbleData[lop][tmp[lop*2+1]] & 0x0f);
	}

	*(DWORD*)(tmp+4)=0;
	for(lop=0;lop!=32;lop++) {
		prm = BitSwapTable3[lop]-1;
		if (tmp[prm >> 3] & BitMaskTable[prm & 7]) {
			tmp[(lop >> 3) + 4] |= BitMaskTable[lop & 7];
		}
	}
	*(DWORD*)Src ^= *(DWORD*)(tmp+4);

	return;
}

static void decode_des_etc(BYTE *buf,int len,int type,int cycle)
{
	int lop,cnt=0;
	if(cycle<3) cycle=3;
	else if(cycle<5) cycle++;
	else if(cycle<7) cycle+=9;
	else cycle+=15;

	for(lop=0;lop*8<len;lop++,buf+=8) {
		if(lop<20 || (type==0 && lop%cycle==0)){ // des
			BitConvert(buf,BitSwapTable1);
			BitConvert4(buf);
			BitConvert(buf,BitSwapTable2);
		} else {
			if(cnt==7 && type==0){
				int a;
				BYTE tmp[8];
				*(DWORD*)tmp     = *(DWORD*)buf;
				*(DWORD*)(tmp+4) = *(DWORD*)(buf+4);
				cnt=0;
				buf[0]=tmp[3];
				buf[1]=tmp[4];
				buf[2]=tmp[6];
				buf[3]=tmp[0];
				buf[4]=tmp[1];
				buf[5]=tmp[2];
				buf[6]=tmp[5];
				a=tmp[7];
				if(a==0x00) a=0x2b;
				else if(a==0x2b) a=0x00;
				else if(a==0x01) a=0x68;
				else if(a==0x68) a=0x01;
				else if(a==0x48) a=0x77;
				else if(a==0x77) a=0x48;
				else if(a==0x60) a=0xff;
				else if(a==0xff) a=0x60;
				else if(a==0x6c) a=0x80;
				else if(a==0x80) a=0x6c;
				else if(a==0xb9) a=0xc0;
				else if(a==0xc0) a=0xb9;
				else if(a==0xeb) a=0xfe;
				else if(a==0xfe) a=0xeb;
				buf[7]=a;
			}
			cnt++;
		}
	}

	return;
}

/*==========================================
 *	Grf data decode sub : zip
 *------------------------------------------
 */
int decode_zip(char *dest, unsigned long* destLen, const char* source, unsigned long sourceLen)
{
	z_stream stream;
	int err;

	stream.next_in = (Bytef*)source;
	stream.avail_in = (uInt)sourceLen;
	/* Check for source > 64K on 16-bit machine: */
	if ((uLong)stream.avail_in != sourceLen) return Z_BUF_ERROR;

	stream.next_out = (Bytef*)dest;
	stream.avail_out = (uInt)*destLen;
	if ((uLong)stream.avail_out != *destLen) return Z_BUF_ERROR;

	stream.zalloc = (alloc_func)0;
	stream.zfree = (free_func)0;

	err = zlib_inflateInit(&stream);
	if (err != Z_OK) return err;

	err = zlib_inflate(&stream, Z_FINISH);
	if (err != Z_STREAM_END) {
		zlib_inflateEnd(&stream);
		return err == Z_OK ? Z_BUF_ERROR : err;
	}
	*destLen = stream.total_out;

	err = zlib_inflateEnd(&stream);

	return err;
}

int encode_zip(char *dest, unsigned long* destLen, const char* source, unsigned long sourceLen) {
	z_stream stream;
	int err;

	stream.next_in = (Bytef*)source;
	stream.avail_in = (uInt)sourceLen;
	/* Check for source > 64K on 16-bit machine: */
	if ((uLong)stream.avail_in != sourceLen) return Z_BUF_ERROR;

	stream.next_out = (Bytef*)dest;
	stream.avail_out = (uInt)*destLen;
	if ((uLong)stream.avail_out != *destLen) return Z_BUF_ERROR;

	stream.zalloc = (alloc_func)0;
	stream.zfree = (free_func)0;

	err = zlib_deflateInit(&stream,Z_DEFAULT_COMPRESSION);
	if (err != Z_OK) return err;

	err = zlib_deflate(&stream, Z_FINISH);
	if (err != Z_STREAM_END) {
		zlib_inflateEnd(&stream);
		return err == Z_OK ? Z_BUF_ERROR : err;
	}
	*destLen = stream.total_out;

	err = zlib_deflateEnd(&stream);

	return err;
}

/***********************************************************
 ***                File List Sobroutines                ***
 ***********************************************************/

/*==========================================
 *	File List : Hash make
 *------------------------------------------
 */
static int filehash(unsigned char *fname)
{
	unsigned int hash=0;

	while(*fname) {
		hash = ((hash<<1)+(hash>>7)*9+(unsigned int)tolower(*fname));
		fname++;
	}

	return hash & 255;
}

/*==========================================
 *	File List : Hash initalize
 *------------------------------------------
 */
static void hashinit(void)
{
	int lop;

	for(lop=0;lop<256;lop++)
		filelist_hash[lop] = -1;

	return;
}

/*==========================================
 *	File List : File find
 *------------------------------------------
 */
FILELIST *filelist_find(char *fname)
{
	int idx;

	for(idx = filelist_hash[filehash(fname)]; idx != -1; idx = filelist[idx].next) {
		if (strcasecmp(filelist[idx].fn, fname) == 0)
			return &filelist[idx];
	}

	return NULL;
}

/*==========================================
 *	File List : Filelist add
 *------------------------------------------
 */
#define FILELIST_ADDS 1024 // ファイルリスト数増分

static FILELIST* filelist_add(FILELIST *entry)
{
	int hash;

/*	if (filelist_entrys>=FILELIST_LIMIT) { // is that necessary?
		printf("filelist limit : filelist_add\n");
		exit(1);
	}*/

	if (filelist_entrys >= filelist_maxentry) {
		FILELIST *new_filelist = (FILELIST*)aRealloc((void*)filelist, (filelist_maxentry + FILELIST_ADDS) * sizeof(FILELIST));
		filelist = new_filelist;
		memset(filelist + filelist_maxentry, 0, FILELIST_ADDS * sizeof(FILELIST));
		filelist_maxentry += FILELIST_ADDS;
	}

	memcpy(&filelist[filelist_entrys], entry, sizeof(FILELIST));

	hash = filehash(entry->fn);
	filelist[filelist_entrys].next = filelist_hash[hash];
	filelist_hash[hash] = filelist_entrys;

	filelist_entrys++;

	return &filelist[filelist_entrys-1];
}

static FILELIST* filelist_modify(FILELIST *entry)
{
	FILELIST *fentry;

	if ((fentry=filelist_find(entry->fn))!=NULL) {
		int tmp = fentry->next;
		memcpy( fentry, entry, sizeof(FILELIST) );
		fentry->next = tmp;
	} else {
		fentry = filelist_add(entry);
	}

	return fentry;
}

/*==========================================
 *	File List : filelist size adjust
 *------------------------------------------
 */
static void filelist_adjust(void)
{
	if (filelist!=NULL) {
		if (filelist_maxentry>filelist_entrys) {
			FILELIST *new_filelist = (FILELIST*)aRealloc(
				(void*)filelist,filelist_entrys*sizeof(FILELIST) );
			filelist = new_filelist;
			filelist_maxentry = filelist_entrys;
		}
	}

	return;
}

/***********************************************************
 ***                  Grfio Sobroutines                  ***
 ***********************************************************/

/*==========================================
 *	Grfio : Resource file size get
 *------------------------------------------
 */
int grfio_size(char *fname)
{
	FILELIST *entry;

	entry = filelist_find(fname);

	if (entry==NULL || entry->gentry<0) {	// LocalFileCheck
		char lfname[256],*p;
		FILELIST lentry;
		struct stat st;

		strncpy(lfname,fname,255);
		for(p=&lfname[0];*p!=0;p++) if (*p=='\\') *p = '/';	// ※Unix時のみ

		if (stat(lfname,&st)==0) {
			strncpy(lentry.fn, fname, sizeof(lentry.fn)-1 );
			lentry.declen = st.st_size;
			lentry.gentry = 0;	// 0:LocalFile
			entry = filelist_modify(&lentry);
		} else if (entry==NULL) {
			printf("%s not found (grfio_size).\n", fname);
			// exit(1);
			return 0;
		}
	}

	return entry->declen;
}

/*==========================================
 *	Grfio : Resource file read & size get
 *------------------------------------------
 */
void* grfio_reads(char *fname, int *size)
{
	FILE *in = NULL;
	unsigned char *buf=NULL,*buf2=NULL;
	char *gfname;
	FILELIST *entry;

	entry = filelist_find(fname);

	if (entry==NULL || entry->gentry<=0) {	// LocalFileCheck
		char lfname[256],*p;
		FILELIST lentry;

		strncpy(lfname,fname,255);
		for(p=&lfname[0];*p!=0;p++)	// ※Unix時のみ
			if (*p=='\\')
				*p = '/';

		in = fopen(lfname,"rb");
		if(in!=NULL) {
			if (entry!=NULL && entry->gentry==0) {
				lentry.declen=entry->declen;
			} else {
				fseek(in,0,2);	// SEEK_END
				lentry.declen = ftell(in);
			}
			fseek(in,0,0);	// SEEK_SET
			buf2 = (char *)aCalloc(1,lentry.declen+1024);
			fread(buf2,1,lentry.declen,in);
			fclose(in);
			in = NULL;
			strncpy( lentry.fn, fname, sizeof(lentry.fn)-1 );
			lentry.gentry = 0;	// 0:LocalFile
			entry = filelist_modify(&lentry);
		} else {
			if (entry!=NULL && entry->gentry<0) {
				entry->gentry = -entry->gentry;	// local file checked
			} else {
				printf("%s not found. %24s\n", fname, "");
				goto errret;
			}
		}
	}
	if (entry!=NULL && entry->gentry>0) {	// Archive[GRF] File Read
		buf = (char *)aCalloc(1,entry->srclen_aligned+1024);
		gfname = gentry_table[entry->gentry-1];
		in = fopen(gfname,"rb");
		if(in==NULL) {
			printf("%s not found. %24s\n", gfname, "");
			goto errret;
		}
		fseek(in,entry->srcpos,0);
		fread(buf,1,entry->srclen_aligned,in);
		fclose(in);
		buf2=(char *)aCalloc(1,entry->declen+1024);
		if(entry->type==1 || entry->type==3 || entry->type==5) {
			uLongf len;
			if (entry->cycle>=0) {
				decode_des_etc((BYTE *)buf, entry->srclen_aligned, entry->cycle == 0, entry->cycle);
			}
			len=entry->declen;
			decode_zip(buf2,&len,buf,entry->srclen);
			if((int)len!=entry->declen) {
				printf("decode_zip size miss match err: %d != %d\n",(int)len,entry->declen);
				goto errret;
			}
		} else {
			memcpy(buf2,buf,entry->declen);
		}
		free(buf);
	}
	if (size!=NULL && entry!=NULL)
		*size = entry->declen;

	return buf2;

errret:
	if (buf!=NULL) free(buf);
	if (buf2!=NULL) free(buf2);
	if (in!=NULL) fclose(in);

	// exit(1);
	return NULL;
}

/*==========================================
 *	Grfio : Resource file read
 *------------------------------------------
 */
void* grfio_read(char *fname)
{
	return grfio_reads(fname, NULL);
}

/*==========================================
 *	Resource filename decode
 *------------------------------------------
 */
static unsigned char * decode_filename(unsigned char *buf,int len)
{
	int lop;

	for(lop=0;lop<len;lop+=8) {
		NibbleSwap(&buf[lop],8);
		BitConvert(&buf[lop],BitSwapTable1);
		BitConvert4(&buf[lop]);
		BitConvert(&buf[lop],BitSwapTable2);
	}

	return buf;
}

/*==========================================
 * Grfio : Entry table read
 *------------------------------------------
 */
static int grfio_entryread(char *gfname,int gentry)
{
	/* GRF header (size: 46 bytes (0x2e), version 0x0100 and 0x0200)
	struct GRF_Header {                    // Offset
	    unsigned char signature[16];       // 0  (0x00) always Master of Magic\0
	    unsigned char allowEncryption[14]; // 16 (0x10)
	    uint32 fileTableOffset;            // 30 (0x1e)
	    uint32 number1;                    // 34 (0x22)
	    uint32 number2;                    // 38 (0x26)
	    uint32 version;                    // 42 (0x2a)
	};*/
	FILE *fp;
	int grf_size,list_size;
	unsigned char grf_header[0x2e];
	int lop,entry,entrys,ofs,grf_version;
	unsigned char *fname;
	unsigned char *grf_filelist;

	fp = fopen(gfname,"rb");
	if(fp==NULL) {
		printf("GRF Data File not found: '%s'.\n",gfname);
		return 1;	// 1:not found error
	}

	fseek(fp,0,2);	// SEEK_END
	grf_size = ftell(fp);
	fseek(fp,0,0);	// SEEK_SET
	fread(grf_header, 1, 0x2e, fp);
	if (strcmp((char*)grf_header, GRF_HEADER) || fseek(fp, getlong(grf_header + 0x1e), 1)) { // SEEK_CUR
		fclose(fp);
		printf("%s read error\n",gfname);
		return 2;	// 2:file format error
	}

	/* Read the version */
	grf_version = getlong(grf_header + 0x2a);
	/* Read the number of files */
	entrys = getlong(grf_header + 0x26) - getlong(grf_header + 0x22) - 7;

	printf("GRF version: 0x%04X. Number of files: %d.\n", grf_version, entrys);

	switch (grf_version & 0xFF00) {
	case 0x0100: //****** Grf version 01xx ******
		list_size = grf_size-ftell(fp);
		grf_filelist = (char *)aCalloc(1,list_size);
		fread(grf_filelist,1,list_size,fp);
		fclose(fp);

		// Get an entry
		for(entry=0,ofs=0;entry<entrys;entry++){
			int ofs2,srclen,srccount;
			char type;
			char *period_ptr;
			FILELIST aentry;

			ofs2 = ofs+getlong(grf_filelist+ofs)+4;
			type = grf_filelist[ofs2+12];
			if( type!=0 ){	// Directory Index ... skip
				fname = decode_filename(grf_filelist+ofs+6,grf_filelist[ofs]-6);
				if(strlen(fname)>sizeof(aentry.fn)-1){
					printf("File name too long : %s.\n",fname);
					free(grf_filelist);
					exit(1);
				}
				srclen=0;
				if((period_ptr=strrchr(fname,'.'))!=NULL){
					for(lop=0;lop<4;lop++) {
						if(strcasecmp(period_ptr,".gnd\0.gat\0.act\0.str"+lop*5)==0)
							break;
					}
					srclen=getlong(grf_filelist+ofs2)-getlong(grf_filelist+ofs2+8)-715;
					if(lop==4) {
						for(lop=10,srccount=1;srclen>=lop;lop=lop*10,srccount++)
							;
					} else {
						srccount=0;
					}
				} else {
					srccount=0;
				}

				aentry.srclen         = srclen;
				aentry.srclen_aligned = getlong(grf_filelist+ofs2+4)-37579;
				aentry.declen         = getlong(grf_filelist+ofs2+8);
				aentry.srcpos         = getlong(grf_filelist+ofs2+13)+0x2e;
				aentry.cycle          = srccount;
				aentry.type           = type;
				strncpy(aentry.fn,fname,sizeof(aentry.fn)-1);
				aentry.fn[sizeof(aentry.fn)-1] = '\0';
#ifdef	GRFIO_LOCAL
				aentry.gentry         = -(gentry+1);	// 負数にするのは初回LocalFileCheckをさせるためのFlagとして
#else
				aentry.gentry         = gentry+1;		// 初回LocalFileCheck無し
#endif
				filelist_modify(&aentry);
			}
			ofs = ofs2 + 17;
		}
		free(grf_filelist);
		break;

	case 0x0200: //****** Grf version 02xx ******
	  {
		unsigned char eheader[8];
		unsigned char *rBuf;
		uLongf rSize,eSize;

		/* Size: 8 + compressedLength
		struct GRF2_FileTableHeader {              // Offset
		    uint32 compressedLength;               // 0
		    uint32 uncompressedLength;             // 4
		    unsigned char body[compressedLength];  // 8
		};*/
		fread(eheader,1,8,fp);
		rSize = getlong(eheader);	// Read Size
		eSize = getlong(eheader+4);	// Extend Size

		if ((int)rSize > grf_size-ftell(fp)) {
			fclose(fp);
			printf("Illegal data format : grf compress entry size.\n");
			return 4;
		}

		rBuf = (char *)aCalloc(1,rSize);	// Get a Read Size
		grf_filelist = (char *)aCalloc(1,eSize);	// Get a Extend Size
		fread(rBuf,1,rSize,fp);
		fclose(fp);
		decode_zip(grf_filelist,&eSize,rBuf,rSize);	// Decode function
		list_size = eSize;
		free(rBuf);

		// Get an entry
		for(entry=0,ofs=0;entry<entrys;entry++){
			/* Size: sizeof(filename) + 17
			Note: The notation sizeof(filename) is the size of the filename, including terminating NULL.
			struct GRF2_FileTableItem {          // Offset
			    char filename[];                 // 0                      EUC-KR encoding
			    uint32 compressedLength;         // sizeof(filename) + 0
			    uint32 compressedLength_aligned; // sizeof(filename) + 4
			    uint32 uncompressedLength;       // sizeof(filename) + 8
			    uint8  flags;                    // sizeof(filename) + 12
			    uint32 offset;                   // sizeof(filename) + 13
			};
			Flags (bitmask):
			    0x01 (FILE) - Whether this flag is a file. If this flag is not set, then this item is a directory.
			    0x02 (MIXCRYPT) - Indicates that the file uses mixed crypto.
			    0x04 (DES) - Indicates that only the first 0x14 blocks are encrypted.
			*/
			int ofs2,srclen,srccount;
			char type;
			FILELIST aentry;

			fname = grf_filelist+ofs;
			if (strlen(fname)>sizeof(aentry.fn)-1) {
				printf("grf : file name too long : %s\n",fname);
				free(grf_filelist);
				exit(1);
			}
			ofs2 = ofs+strlen(grf_filelist+ofs)+1;
			type = grf_filelist[ofs2+12];
			if ((type & 0x01) == 0x01) { // type 1, 2 or 3
				srclen=getlong(grf_filelist+ofs2);
				switch (type) {
				case 3:
					for(lop=10,srccount=1;srclen>=lop;lop=lop*10,srccount++)
						;
					break;
				case 5:
					srccount = 0;
					break;
				default: // 1
					srccount = -1;
					break;
				}
				aentry.srclen         = srclen;
				aentry.srclen_aligned = getlong(grf_filelist+ofs2+4);
				aentry.declen         = getlong(grf_filelist+ofs2+8);
				aentry.srcpos         = getlong(grf_filelist+ofs2+13)+0x2e;
				aentry.cycle          = srccount;
				aentry.type           = type;
				strncpy(aentry.fn,fname,sizeof(aentry.fn)-1);
				aentry.fn[sizeof(aentry.fn)-1] = '\0';
#ifdef	GRFIO_LOCAL
				aentry.gentry         = -(gentry+1);	// 負数にするのは初回LocalFileCheckをさせるためのFlagとして
#else
				aentry.gentry         = gentry+1;		// 初回LocalFileCheck無し
#endif
				filelist_modify(&aentry);
			}
			ofs = ofs2 + 17;
		}
		free(grf_filelist);
	  }
		break;

	default: //****** Grf Other version ******
		fclose(fp);
		printf("Not support grf version: 0x%04x.\n", grf_version);
		return 4;
	}

	filelist_adjust();	// filelistの不要エリア解放

	return 0;	// 0:no error
}

/*==========================================
 * Grfio : Resource file check
 *------------------------------------------
 */
static void grfio_resourcecheck(void)
{
	int size;
	unsigned char *buf,*ptr;
	char w1[256],w2[256],src[256],dst[256];
	FILELIST *entry;

	buf=grfio_reads("data\\resnametable.txt",&size);
	if (buf == NULL) {
		printf("WARNING: Could not read data\\resnametable.txt !\n");
		return;
	}
	buf[size] = 0;

	for(ptr=buf;ptr-buf<size;) {
		if(sscanf(ptr,"%[^#]#%[^#]#",w1,w2)==2){
			if(strstr(w2,"bmp")){
				sprintf(src,"data\\texture\\%s",w1);
				sprintf(dst,"data\\texture\\%s",w2);
			} else {
				sprintf(src,"data\\%s",w1);
				sprintf(dst,"data\\%s",w2);
			}
			entry = filelist_find(dst);
			if (entry!=NULL) {
				FILELIST fentry;
				memcpy( &fentry, entry, sizeof(FILELIST) );
				strncpy( fentry.fn ,src, sizeof(fentry.fn)-1 );
				filelist_modify(&fentry);
			} else {
				//printf("File not found in data.grf : %s < %s\n", dst, src);
			}
		}
		ptr = strchr(ptr,'\n');	// Next line
		if (!ptr) break;
		ptr++;
	}
	free(buf);
	filelist_adjust();	// filelistの不要エリア解放

	return;
}

/*==========================================
 * Grfio : Resource add
 *------------------------------------------
 */
#define GENTRY_ADDS 16 // gentry_tableエントリ数増分

int grfio_add(char *fname)
{
	int len,result;
	char *buf;

	if (gentry_entrys>=GENTRY_LIMIT) {
		printf("gentrys limit : grfio_add\n");
		exit(1);
	}

	printf("'%s' file reading...\n",fname);

	if (gentry_entrys>=gentry_maxentry) {
		char **new_gentry = (char**)aRealloc((void*)gentry_table, (gentry_maxentry+GENTRY_ADDS) * sizeof(char*));
		int lop;
		gentry_table = new_gentry;
		gentry_maxentry += GENTRY_ADDS;
		for(lop=gentry_entrys;lop<gentry_maxentry;lop++)
			gentry_table[lop] = NULL;
	}
	len = strlen( fname );
	buf = (char *)aCalloc(1,len+1);
	strncpy( buf, fname, len+1 );
	gentry_table[gentry_entrys++] = buf;

	result = grfio_entryread(fname,gentry_entrys-1);

	if (result==0) {
		// リソースチェック
		grfio_resourcecheck();
	}

	return result;
}

/*==========================================
 * Grfio : Finalize
 *------------------------------------------
 */
void grfio_final(void)
{
	int lop;

	if (filelist != NULL) {
		free(filelist);
		filelist = NULL;
	}
	filelist_entrys = 0;
	filelist_maxentry = 0;

	if (gentry_table != NULL) {
		for(lop=0;lop<gentry_entrys;lop++) {
			if (gentry_table[lop]!=NULL) {
				free(gentry_table[lop]);
			}
		}
		free(gentry_table);
		gentry_table = NULL;
	}
	gentry_entrys = 0;
	gentry_maxentry = 0;

#ifdef _WIN32
	#ifndef LOCALZLIB
	FreeLibrary(zlib_dll);
	zlib_inflateInit_ = NULL;
	zlib_inflate      = NULL;
	zlib_inflateEnd   = NULL;
	#endif
#endif

	return;
}

/*==========================================
 * Grfio : Initialize
 *------------------------------------------
 */

void grfio_load_zlib(void) {
#if defined(_WIN32) && !defined(LOCALZLIB)
	if(!zlib_dll) {
		zlib_dll = LoadLibrary("zlib.dll");
		(FARPROC)zlib_inflateInit_ = GetProcAddress(zlib_dll,"inflateInit_");
		(FARPROC)zlib_inflate      = GetProcAddress(zlib_dll,"inflate");
		(FARPROC)zlib_inflateEnd   = GetProcAddress(zlib_dll,"inflateEnd");
		(FARPROC)zlib_deflateInit_ = GetProcAddress(zlib_dll,"deflateInit_");
		(FARPROC)zlib_deflate      = GetProcAddress(zlib_dll,"deflate");
		(FARPROC)zlib_deflateEnd   = GetProcAddress(zlib_dll,"deflateEnd");
		(FARPROC)zlib_crc32        = GetProcAddress(zlib_dll,"crc32");
		if(zlib_dll == NULL) {
			MessageBox(NULL,"Can't load zlib.dll","grfio.c",MB_OK);
			exit(1);
		}
	}
#endif

	return;
}

unsigned long grfio_crc32(const char *buf, unsigned int len) {
	return zlib_crc32(zlib_crc32(0L, Z_NULL, 0), buf, len);
}

void grfio_init(char *fname)
{
	FILE *data_conf;
	char line[1024],w1[1024],w2[1024];
	int result = 0, result2 = 0, result3 = 0;

	grfio_load_zlib();

	if( fname )
	{
		data_conf = fopen(fname, "r");

		// grf-files.txt があるなら読み込む
		if( data_conf!=NULL ) {
			while(fgets(line,sizeof(line)-1,data_conf)) {
				if(sscanf(line,"%[^:]: %[^\r\n]", w1, w2) == 2) {
					if(strcmp(w1,"data") == 0) {
						strncpy(data_file, w2, sizeof(data_file));
						data_file[sizeof(data_file)-1] = '\0';
					} else if(strcmp(w1,"sdata") == 0) {
						strncpy(sdata_file, w2, sizeof(sdata_file));
						sdata_file[sizeof(sdata_file)-1] = '\0';
					} else if(strcmp(w1,"adata") == 0) {
						strncpy(adata_file, w2, sizeof(adata_file));
						adata_file[sizeof(adata_file)-1] = '\0';
					}
				}
			}
			fclose(data_conf);
			printf("read %s done\n",fname);
		} // end of reading grf-files.txt
	}

	hashinit();	// hashテーブル初期化

	filelist = NULL;
	filelist_entrys = 0;
	filelist_maxentry = 0;
	gentry_table = NULL;
	gentry_entrys = 0;
	gentry_maxentry = 0;
	atexit(grfio_final);	// 終了処理定義

	// エントリーテーブル読込
	if (strcmp(data_file, "") != 0) {	// If data directive exists in grf-files.txt
		result  = grfio_add(data_file);	// Standard data file
	} else {
		printf("No file name in grf-files.txt for data directive.\n");
	}
	if (strcmp(sdata_file, "") != 0) {	// If sdata directive exists in grf-files.txt
		result2 = grfio_add(sdata_file);	// Sakray addon data file
	} else {
		printf("No file name in grf-files.txt for sdata directive.\n");
	}
	if (strcmp(adata_file, "") != 0) {	// If adata directive exists in grf-files.txt
		result3 = grfio_add(adata_file);	// alpha data file
	} else {
		printf("No file name in grf-files.txt for adata directive.\n");
	}
/*
	if (result!=0 && result2!=0 && result3!=0) {
		printf("not grf file readed exit!!\n");
		exit(1);			// リソースが一つも読めなければ終了
	}
*/
}
