#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#ifdef MEMWATCH
#include "memwatch.h"
#endif

#define _MALLOC_C_
#include "malloc.h"

// 独自メモリマネージャを使用しない場合、次をコメントアウトしてください
#define USE_MEMMGR

// デバッグモード（エラーチェックの強化用、通常運営ではお勧めできない）
//#define DEBUG_MEMMGR

#if defined(MEMWATCH) || !defined(USE_MEMMGR)

void* aMalloc_( size_t size, const char *file, int line, const char *func )
{
	void *ret;

	// printf("%s:%d: in func %s: malloc %d\n",file,line,func,size);
#ifdef MEMWATCH
	ret=mwMalloc(size,file,line);
#else
	ret=malloc(size);
#endif

#ifdef _WIN64
	if( ((__int64)ret + size) >> 32 ) {
		printf("memmgr: current version does not compatible with this machine\n");
		exit(1);
	}
#endif

	if(ret==NULL){
		printf("%s:%d: in func %s: malloc error out of memory!\n",file,line,func);
		exit(1);

	}
	return ret;
}

void* aCalloc_( size_t num, size_t size, const char *file, int line, const char *func )
{
	void *ret;

	// printf("%s:%d: in func %s: calloc %d %d\n",file,line,func,num,size);
#ifdef MEMWATCH
	ret=mwCalloc(num,size,file,line);
#else
	ret=calloc(num,size);
#endif

#ifdef _WIN64
	if( ((__int64)ret + size) >> 32 ) {
		printf("memmgr: 64bit version does not compatible with this machine\n");
		exit(1);
	}
#endif

	if(ret==NULL){
		printf("%s:%d: in func %s: calloc error out of memory!\n",file,line,func);
		exit(1);

	}
	return ret;
}

void* aRealloc_( void *p, size_t size, const char *file, int line, const char *func )
{
	void *ret;

	// printf("%s:%d: in func %s: realloc %p %d\n",file,line,func,p,size);
#ifdef MEMWATCH
	ret=mwRealloc(p,size,file,line);
#else
	ret=realloc(p,size);
#endif

#ifdef _WIN64
	if( ((__int64)ret + size) >> 32 ) {
		printf("memmgr: 64bit version does not compatible with this machine\n");
		exit(1);
	}
#endif

	if(ret==NULL){
		printf("%s:%d: in func %s: realloc error out of memory!\n",file,line,func);
		exit(1);

	}
	return ret;
}

void* aStrdup_( const void *p, const char *file, int line, const char *func )
{
	void *ret;

	// printf("%s:%d: in func %s: strdup %p\n",file,line,func,p);
#ifdef MEMWATCH
	ret=mwStrdup(p,file,line);
#else
	ret=strdup(p);
#endif

#ifdef _WIN64
	if( ((__int64)ret + strlen(ret) + 1) >> 32 ) {
		printf("memmgr: 64bit version does not compatible with this machine\n");
		exit(1);
	}
#endif

	if(ret==NULL){
		printf("%s:%d: in func %s: strdup error out of memory!\n",file,line,func);
		exit(1);

	}
	return ret;
}

void aFree_( void *p, const char *file, int line, const char *func )
{
	// printf("%s:%d: in func %s: free %p\n",file,line,func,p);
#ifdef MEMWATCH
	mwFree(p,file,line);
#else
	free(p);
#endif
}

int do_init_memmgr(const char* file)
{
#ifdef MEMWATCH
	mwInit();
	atexit(mwAbort);
#endif
	return 0;
}

double memmgr_usage(void)
{
	return 0;
}

#else /* USE_MEMMGR */

/*
 * メモリマネージャ
 *     malloc , free の処理を効率的に出来るようにしたもの。
 *     複雑な処理を行っているので、若干重くなるかもしれません。
 *
 * データ構造など（説明下手ですいません^^; ）
 *     ・メモリを複数の「ブロック」に分けて、さらにブロックを複数の「ユニット」
 *       に分けています。ユニットのサイズは、１ブロックの容量を複数個に均等配分
 *       したものです。たとえば、１ユニット32KBの場合、ブロック１つは32Byteのユ
 *       ニットが、1024個集まって出来ていたり、64Byteのユニットが 512個集まって
 *       出来ていたりします。（padding,unit_head を除く）
 *
 *     ・ブロック同士はリンクリスト(block_prev,block_next) でつながり、同じサイ
 *       ズを持つブロック同士もリンクリスト(hash_prev,hash_nect) でつな
 *       がっています。それにより、不要となったメモリの再利用が効率的に行えます。
 */

/* ブロックのアライメント */
#define BLOCK_ALIGNMENT1	16
#define BLOCK_ALIGNMENT2	64

/* ブロックに入るデータ量 */
#define BLOCK_DATA_COUNT1	128
#define BLOCK_DATA_COUNT2	608

/* ブロックの大きさ: 16*128 + 64*576 = 40KB */
#define BLOCK_DATA_SIZE1	( BLOCK_ALIGNMENT1 * BLOCK_DATA_COUNT1 )
#define BLOCK_DATA_SIZE2	( BLOCK_ALIGNMENT2 * BLOCK_DATA_COUNT2 )
#define BLOCK_DATA_SIZE		( BLOCK_DATA_SIZE1 + BLOCK_DATA_SIZE2 )

/* 一度に確保するブロックの数。 */
#define BLOCK_ALLOC		104

/* ブロック */
struct block {
	struct block* block_next;		/* 次に確保した領域 */
	struct block* unfill_prev;		/* 次の埋まっていない領域 */
	struct block* unfill_next;		/* 次の埋まっていない領域 */
	unsigned short unit_size;		/* ユニットの大きさ */
	unsigned short unit_hash;		/* ユニットのハッシュ */
	unsigned short unit_count;		/* ユニットの個数 */
	unsigned short unit_used;		/* 使用ユニット数 */
	unsigned short unit_unfill;		/* 未使用ユニットの場所 */
	unsigned short unit_maxused;	/* 使用ユニットの最大値 */
	char   data[ BLOCK_DATA_SIZE ];
};

struct unit_head {
	struct block   *block;
	const  char*   file;
	unsigned short line;
	unsigned short size;
#ifdef DEBUG_MEMMGR
	time_t time_stamp;
#endif
	long           checksum;
};

static struct block* hash_unfill[BLOCK_DATA_COUNT1 + BLOCK_DATA_COUNT2 + 1];
static struct block* block_first, *block_last, block_head;

/* メモリを使い回せない領域用のデータ */
struct unit_head_large {
	size_t                  size;
	struct unit_head_large* prev;
	struct unit_head_large* next;
	struct unit_head        unit_head;
};

static struct unit_head_large *unit_head_large_first = NULL;

static struct block* block_malloc(unsigned short hash);
static void          block_free(struct block* p);
static void          memmgr_warning(const char* format,...);
static size_t        memmgr_usage_bytes;

#define block2unit(p, n) ((struct unit_head*)(&(p)->data[ p->unit_size * (n) ]))

#ifdef DEBUG_MEMMGR
#define memmgr_assert(v) do { if(!(v)) { memmgr_warning("memmgr_assert: " #v "\n"); } } while(0)
#else
#define memmgr_assert(v)
#endif

static unsigned short size2hash( size_t size )
{
	if( size <= BLOCK_DATA_SIZE1 ) {
		return (unsigned short)(size + BLOCK_ALIGNMENT1 - 1) / BLOCK_ALIGNMENT1;
	} else if( size <= BLOCK_DATA_SIZE ){
		return (unsigned short)(size - BLOCK_DATA_SIZE1 + BLOCK_ALIGNMENT2 - 1) / BLOCK_ALIGNMENT2
				+ BLOCK_DATA_COUNT1;
	} else {
		return 0xffff;	// ブロック長を超える場合は hash にしない
	}
}

static size_t hash2size( unsigned short hash )
{
	if( hash <= BLOCK_DATA_COUNT1) {
		return hash * BLOCK_ALIGNMENT1;
	} else {
		return (hash - BLOCK_DATA_COUNT1) * BLOCK_ALIGNMENT2 + BLOCK_DATA_SIZE1;
	}
}

void* aMalloc_(size_t size, const char *file, int line, const char *func)
{
	struct block *block;
	short size_hash = size2hash( size );
	struct unit_head *head;

	if(size == 0) {
		return NULL;
	}
	memmgr_usage_bytes += size;

	/* ブロック長を超える領域の確保には、malloc() を用いる */
	/* その際、unit_head.block に NULL を代入して区別する */
	if(hash2size(size_hash) > BLOCK_DATA_SIZE - sizeof(struct unit_head)) {
		struct unit_head_large* p = (struct unit_head_large*)malloc(sizeof(struct unit_head_large) + size);

		if(p != NULL) {
#ifdef DEBUG_MEMMGR
			// タイムスタンプの記録
			p->unit_head.time_stamp = time(NULL);
#endif
			p->size            = size;
			p->unit_head.block = NULL;
			p->unit_head.size  = 0;
			p->unit_head.file  = file;
			p->unit_head.line  = line;
			if(unit_head_large_first == NULL) {
				unit_head_large_first = p;
				p->next = NULL;
				p->prev = NULL;
			} else {
				unit_head_large_first->prev = p;
				p->prev = NULL;
				p->next = unit_head_large_first;
				unit_head_large_first = p;
			}
			*(long*)((char*)p + sizeof(struct unit_head_large) - sizeof(long) + size) = 0xdeadbeaf;
			return (char *)p + sizeof(struct unit_head_large) - sizeof(long);
		} else {
			printf("MEMMGR::memmgr_alloc failed.\n");
			exit(1);
		}
	}

	/* 同一サイズのブロックが確保されていない時、新たに確保する */
	if(hash_unfill[size_hash]) {
		block = hash_unfill[size_hash];
	} else {
		block = block_malloc(size_hash);
	}

	if( block->unit_unfill == 0xFFFF ) {
		// free済み領域が残っていない
		memmgr_assert(block->unit_used <  block->unit_count);
		memmgr_assert(block->unit_used == block->unit_maxused);
		head = block2unit(block, block->unit_maxused);
		block->unit_used++;
		block->unit_maxused++;
	} else {
		head = block2unit(block, block->unit_unfill);
		block->unit_unfill = head->size;
		block->unit_used++;
	}

	if( block->unit_unfill == 0xFFFF && block->unit_maxused >= block->unit_count) {
		// ユニットを使い果たしたので、unfillリストから削除
		if( block->unfill_prev == &block_head) {
			hash_unfill[ size_hash ] = block->unfill_next;
		} else {
			block->unfill_prev->unfill_next = block->unfill_next;
		}
		if( block->unfill_next ) {
			block->unfill_next->unfill_prev = block->unfill_prev;
		}
		block->unfill_prev = NULL;
	}

#ifdef DEBUG_MEMMGR
	{
		size_t i, sz = hash2size( size_hash );
		for( i=0; i<sz; i++ )
		{
			if( ((unsigned char*)head)[ sizeof(struct unit_head) - sizeof(long) + i] != 0xfd )
			{
				if( head->line != 0xfdfd )
				{
					memmgr_warning("memmgr: freed-data is changed. (freed in %s line %d)\n", head->file,head->line);
				}
				else
				{
					memmgr_warning("memmgr: not-allocated-data is changed.\n");
				}
				break;
			}
		}
		memset( (char *)head + sizeof(struct unit_head) - sizeof(long), 0xcd, sz );
		// タイムスタンプの記録
		head->time_stamp = time(NULL);
	}
#endif

	head->block = block;
	head->file  = file;
	head->line  = line;
	head->size  = (unsigned short)size;
	*(long*)((char*)head + sizeof(struct unit_head) - sizeof(long) + size) = 0xdeadbeaf;

	return (char *)head + sizeof(struct unit_head) - sizeof(long);
};

void* aCalloc_(size_t num, size_t size, const char *file, int line, const char *func )
{
	void *p = aMalloc_(num * size,file,line,func);

	memset(p,0,num * size);
	return p;
}

void* aRealloc_(void *memblock, size_t size, const char *file, int line, const char *func )
{
	size_t old_size;

	if(memblock == NULL) {
		return aMalloc_(size,file,line,func);
	}

	old_size = ((struct unit_head *)((char *)memblock - sizeof(struct unit_head) + sizeof(long)))->size;
	if( old_size == 0 ) {
		old_size = ((struct unit_head_large *)((char *)memblock - sizeof(struct unit_head_large) + sizeof(long)))->size;
	}
	if(old_size > size) {
		// サイズ縮小 -> そのまま返す（手抜き）
		return memblock;
	}  else {
		// サイズ拡大
		void *p = aMalloc_(size,file,line,func);
		if(p != NULL) {
			memcpy(p,memblock,old_size);
		}
		aFree_(memblock,file,line,func);
		return p;
	}
}

void* aStrdup_(const void* string, const char *file, int line, const char *func )
{
	if(string == NULL) {
		return NULL;
	} else {
		size_t  len = strlen((const char *)string);
		char    *p  = (char *)aMalloc_(len + 1,file,line,func);
		memcpy(p,string,len+1);
		return p;
	}
}

void aFree_(void *ptr, const char *file, int line, const char *func )
{
	struct unit_head *head;

	if(ptr == NULL) return;
	head = (struct unit_head *)((char *)ptr - sizeof(struct unit_head) + sizeof(long));
	if(head->size == 0) {
		/* malloc() で直に確保された領域 */
		struct unit_head_large *head_large = (struct unit_head_large *)((char *)ptr - sizeof(struct unit_head_large) + sizeof(long));

		if(*(long*)((char*)head_large + sizeof(struct unit_head_large) - sizeof(long) + head_large->size) != 0xdeadbeaf)
		{
			memmgr_warning("memmgr: args of aFree is overflowed pointer %s line %d\n",file,line);
		} else {
			head->size = -1;
			if(head_large->prev) {
				head_large->prev->next = head_large->next;
			} else {
				unit_head_large_first  = head_large->next;
			}
			if(head_large->next) {
				head_large->next->prev = head_large->prev;
			}
			memmgr_usage_bytes -= head_large->size;
			free(head_large);
		}
	} else {
		/* ユニット解放 */
		struct block *block = head->block;

		if( (char*)head - (char*)block > sizeof(struct block) ) {
			memmgr_warning("memmgr: args of aFree is invalid pointer %s line %d\n",file,line);
		} else if(head->block == NULL) {
			memmgr_warning("memmgr: args of aFree is freed pointer %s line %d\n",file,line);
		} else if(*(long*)((char*)head + sizeof(struct unit_head) - sizeof(long) + head->size) != 0xdeadbeaf) {
			memmgr_warning("memmgr: args of aFree is overflowed pointer %s line %d\n",file,line);
		} else {
			memmgr_usage_bytes -= head->size;
			head->block         = NULL;
#ifdef DEBUG_MEMMGR
			memset(ptr, 0xfd, block->unit_size - sizeof(struct unit_head) + sizeof(long) );
			head->file = file;
			head->line = line;
#endif
			memmgr_assert( block->unit_used > 0 );
			if(--block->unit_used == 0) {
				/* ブロックの解放 */
				block_free(block);
			} else {
				if( block->unfill_prev == NULL) {
					// unfill リストに追加
					if( hash_unfill[ block->unit_hash ] ) {
						hash_unfill[ block->unit_hash ]->unfill_prev = block;
					}
					block->unfill_prev = &block_head;
					block->unfill_next = hash_unfill[ block->unit_hash ];
					hash_unfill[ block->unit_hash ] = block;
				}
				head->size     = block->unit_unfill;
				block->unit_unfill = (unsigned short)(((unsigned long)head - (unsigned long)block->data) / block->unit_size);
			}
		}
	}
}

/* ブロックを確保する */
static struct block* block_malloc(unsigned short hash)
{
	int i;
	struct block *p;

	if(hash_unfill[0] != NULL) {
		/* ブロック用の領域は確保済み */
		p = hash_unfill[0];
		hash_unfill[0] = hash_unfill[0]->unfill_next;
	} else {
		/* ブロック用の領域を新たに確保する */
		p = (struct block*)malloc(sizeof(struct block) * (BLOCK_ALLOC) );
		if(p == NULL) {
			printf("MEMMGR::block_alloc failed.\n");
			exit(1);
		}
#ifdef _WIN64
		if( ((__int64)p + sizeof(struct block) * (BLOCK_ALLOC)) >> 32 ) {
			printf("memmgr: 64bit version does not compatible with this machine\n");
			exit(1);
		}
#endif
		if(block_first == NULL) {
			/* 初回確保 */
			block_first   = p;
		} else {
			block_last->block_next = p;
		}
		block_last = &p[BLOCK_ALLOC - 1];
		block_last->block_next = NULL;
		/* ブロックを連結させる */
		for(i=0;i<BLOCK_ALLOC;i++) {
			if(i != 0) {
				// p[0] はこれから使うのでリンクには加えない
				p[i].unfill_next = hash_unfill[0];
				hash_unfill[0]   = &p[i];
				p[i].unfill_prev = NULL;
			}
			if(i != BLOCK_ALLOC -1) {
				p[i].block_next = &p[i+1];
			}
		}
	}

	// unfill に追加
	memmgr_assert(hash_unfill[ hash ] == NULL);
	hash_unfill[ hash ] = p;
	p->unfill_prev  = &block_head;
	p->unfill_next  = NULL;
	p->unit_size    = (unsigned short)(hash2size( hash ) + sizeof(struct unit_head));
	p->unit_hash    = hash;
	p->unit_count   = BLOCK_DATA_SIZE / p->unit_size;
	p->unit_used    = 0;
	p->unit_unfill  = 0xFFFF;
	p->unit_maxused = 0;
#ifdef DEBUG_MEMMGR
	memset( p->data, 0xfd, sizeof(p->data) );
#endif
	return p;
}

static void block_free(struct block* p)
{
	if( p->unfill_prev ) {
		if( p->unfill_prev == &block_head) {
			hash_unfill[ p->unit_hash ] = p->unfill_next;
		} else {
			p->unfill_prev->unfill_next = p->unfill_next;
		}
		if( p->unfill_next ) {
			p->unfill_next->unfill_prev = p->unfill_prev;
		}
		p->unfill_prev = NULL;
	}

	p->unfill_next = hash_unfill[0];
	hash_unfill[0] = p;
}

static char memmer_logfile[128];

static void memmgr_warning(const char* format,...)
{
	FILE *fp = fopen(memmer_logfile,"a");
	va_list ap;
	va_start(ap,format);

	if(fp) {
		vfprintf(fp,format,ap);
		fclose(fp);
	}
	vprintf(format,ap);
	va_end(ap);
}

static FILE* memmgr_log(void)
{
	FILE *fp = fopen(memmer_logfile,"a");

	if(!fp) {
		fp = stdout;
	}
	fprintf(fp,"memmgr: memory leaks found\n");
	return fp;
}

static void memmer_exit(void)
{
	FILE *fp = NULL;
	int count = 0;
	struct block *block = block_first;
	struct unit_head_large *large = unit_head_large_first;

	while(block) {
		if(block->unfill_prev) {
			int i;
			if(!fp) {
				fp = memmgr_log();
			}
			for(i=0;i< block->unit_maxused;i++) {
				struct unit_head *head = block2unit(block, i);
				if(head->block != NULL) {
#ifdef DEBUG_MEMMGR
					{
						char buf[24];
						strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", localtime(&head->time_stamp));
						fprintf(
							fp,"%04d [%s] : %s line %d size %d\n",++count,buf,
							head->file,head->line,head->size
						);
					}
#else
					fprintf(
						fp,"%04d : %s line %d size %d\n",++count,
						head->file,head->line,head->size
					);
#endif
				}
			}
		}
		block = block->block_next;
	}
	while(large) {
		if(!fp) {
			fp = memmgr_log();
		}

#ifdef DEBUG_MEMMGR
		{
			char buf[24];
			strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", localtime(&large->unit_head.time_stamp));
			fprintf(
				fp,"%04d [%s] : %s line %d size %d\n",++count,buf,
				large->unit_head.file,
				large->unit_head.line,large->unit_head.size
			);
		}
#else
		fprintf(
			fp,"%04d : %s line %d size %d\n",++count,
			large->unit_head.file,
			large->unit_head.line,large->unit_head.size
		);
#endif
		large = large->next;
	}
	if(!fp) {
		printf("memmgr: no memory leaks found.\n");
	} else {
		printf("memmgr: memory leaks found.\n");
	}
}

int do_init_memmgr(const char* file)
{
	sprintf(memmer_logfile,"%s.log",file);
	atexit(memmer_exit);
	printf("memmgr: initialised: %s\n",memmer_logfile);
	return 0;
}

double memmgr_usage(void)
{
	return memmgr_usage_bytes / 1024.0;
}

#endif
