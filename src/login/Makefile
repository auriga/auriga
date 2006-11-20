all: login-server

COMMON_OBJ = ../common/core.o ../common/socket.o ../common/timer.o ../common/db.o ../common/lock.o ../common/malloc.o ../common/grfio.o ../common/httpd.o ../common/graph.o ../common/md5calc.o ../common/journal.o

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

login-server: login.o $(COMMON_OBJ)
	$(CC) -o ../../bin/$@ login.o $(COMMON_OBJ) $(LIBS)

clean:
	rm -f *.o
	rm -f GNUmakefile

ifeq ($(findstring CYGWIN,$(shell uname)), CYGWIN)
		rm -f ../../bin/login-server.exe
else
		rm -f ../../bin/login-server
endif
