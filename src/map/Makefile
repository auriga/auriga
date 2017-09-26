all: map-server

COMMON_SRC = $(shell ls ../common/*.c)

ifeq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
COMMON_SRC += $(shell ls ../common/zlib/*.c)
endif

MAP_SRC = $(shell ls *.c)
ifdef SQLFLAG
	MAP_SRC += $(shell ls sql/*.c)
else
	MAP_SRC += $(shell ls txt/*.c)
endif

map-server: $(MAP_SRC:.c=.o) $(COMMON_SRC:.c=.o)
	$(CC) -o ../../$@ $> $(LIBS) ../common/lua/liblua.a

clean:
	rm -f *.o
ifdef SQLFLAG
	rm -f sql/*.o
else
	rm -f txt/*.o
endif
	rm -f GNUmakefile

ifeq ($(findstring CYGWIN,$(shell uname)), CYGWIN)
	rm -f ../../map-server.exe
else
	rm -f ../../map-server
endif
