all: map-server

COMMON_SRC = $(shell ls ../common/*.c)

ifeq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
COMMON_SRC += $(shell ls ../common/zlib/*.c)
endif

ifdef SQLFLAG
	MAP_SRC = $(shell ls *.c | grep -v '_txt\.c')
else
	MAP_SRC = $(shell ls *.c | grep -v '_sql\.c')
endif

map-server: $(MAP_SRC:.c=.o) $(COMMON_SRC:.c=.o)
	$(CC) -o ../../$@ $> $(LIBS)

clean:
	rm -f *.o
	rm -f GNUmakefile

ifeq ($(findstring CYGWIN,$(shell uname)), CYGWIN)
	rm -f ../../map-server.exe
else
	rm -f ../../map-server
endif
