all: char-server

COMMON_OBJ = ../common/core.o ../common/socket.o ../common/timer.o ../common/db.o ../common/lock.o ../common/nullpo.o ../common/malloc.o ../common/grfio.o ../common/httpd.o ../common/graph.o ../common/md5calc.o ../common/journal.o

ifeq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
COMMON_OBJ += ../common/zlib/inflate.o ../common/zlib/deflate.o ../common/zlib/crc32.o ../common/zlib/trees.o ../common/zlib/zutil.o ../common/zlib/inftrees.o ../common/zlib/adler32.o ../common/zlib/inffast.o ../common/zlib/compress.o
endif

ifeq ($(findstring MINGW32,$(shell uname)), MINGW32)
LIBS = -lm -lwsock32 -limagehlp
else
LIBS = -lm
endif

ifdef SQLFLAG
	LIBS += -L$(MYSQL_LIBS) -lmysqlclient
endif

ifneq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
	LIBS += -lz
endif

char-server: char.o inter.o int_party.o int_guild.o int_storage.o int_pet.o int_mail.o int_homun.o int_status.o $(COMMON_OBJ)
	$(CC) -o ../../bin/$@ $> $(LIBS)

clean:
	rm -f *.o
	rm -f GNUmakefile

ifeq ($(findstring CYGWIN,$(shell uname)), CYGWIN)
		rm -f ../../bin/char-server.exe
else
		rm -f ../../bin/char-server
endif
