all: map-server

COMMON_OBJ = ../common/core.o ../common/socket.o ../common/timer.o ../common/grfio.o ../common/db.o ../common/lock.o ../common/nullpo.o ../common/malloc.o ../common/httpd.o ../common/graph.o ../common/md5calc.o ../common/journal.o ../common/utils.o

ifeq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
COMMON_OBJ += ../common/zlib/inflate.o ../common/zlib/deflate.o ../common/zlib/crc32.o ../common/zlib/trees.o ../common/zlib/zutil.o ../common/zlib/inftrees.o ../common/zlib/adler32.o ../common/zlib/inffast.o ../common/zlib/compress.o
endif

ifdef SQLFLAG
	LIBS_S = -L$(MYSQL_LIBS) -lmysqlclient
endif

map-server: map.o chrif.o clif.o pc.o npc.o chat.o path.o itemdb.o mob.o script.o storage.o skill.o atcommand.o battle.o intif.o trade.o party.o vending.o guild.o pet.o status.o friend.o date.o ranking.o unit.o mail.o homun.o $(COMMON_OBJ)
	$(CC) -o ../../$@ $> $(LIBS) $(LIBS_S)

clean:
	rm -f *.o
	rm -f GNUmakefile

ifeq ($(findstring CYGWIN,$(shell uname)), CYGWIN)
		rm -f ../../map-server.exe
else
		rm -f ../../map-server
endif
