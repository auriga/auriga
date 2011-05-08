all: char-server

COMMON_OBJ = ../common/core.o ../common/socket.o ../common/timer.o ../common/db.o ../common/lock.o ../common/nullpo.o ../common/malloc.o ../common/grfio.o ../common/httpd.o ../common/graph.o ../common/md5calc.o ../common/journal.o ../common/utils.o ../common/version.o ../common/sqldbs.o

ifeq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
COMMON_OBJ += ../common/zlib/inflate.o ../common/zlib/deflate.o ../common/zlib/crc32.o ../common/zlib/trees.o ../common/zlib/zutil.o ../common/zlib/inftrees.o ../common/zlib/adler32.o ../common/zlib/inffast.o ../common/zlib/compress.o
endif

char-server: char.o charlog_sql.o charlog_txt.o inter.o interlog_sql.o interlog_txt.o int_party.o int_guild.o int_storage.o int_pet.o int_mail.o int_merc.o int_homun.o int_status.o int_quest.o accregdb_sql.o accregdb_txt.o chardb_sql.o chardb_txt.o guilddb_sql.o guilddb_txt.o homundb_sql.o homundb_txt.o maildb_sql.o maildb_txt.o mercdb_sql.o mercdb_txt.o partydb_sql.o partydb_txt.o petdb_sql.o petdb_txt.o questdb_sql.o questdb_txt.o statusdb_sql.o statusdb_txt.o storagedb_sql.o storagedb_txt.o $(COMMON_OBJ)
	$(CC) -o ../../$@ $> $(LIBS)

clean:
	rm -f *.o
	rm -f GNUmakefile

ifeq ($(findstring CYGWIN,$(shell uname)), CYGWIN)
	rm -f ../../char-server.exe
else
	rm -f ../../char-server
endif
