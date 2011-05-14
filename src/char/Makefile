all: char-server

COMMON_SRC = $(shell ls ../common/*.c)

ifeq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
COMMON_SRC += $(shell ls ../common/zlib/*.c)
endif

ifdef SQLFLAG
	CHAR_SRC = $(shell ls *.c | grep -v '_txt\.c')
else
	CHAR_SRC = $(shell ls *.c | grep -v '_sql\.c')
endif

char-server: $(CHAR_SRC:.c=.o) $(COMMON_SRC:.c=.o)
	$(CC) -o ../../$@ $> $(LIBS)

clean:
	rm -f *.o
	rm -f GNUmakefile

ifeq ($(findstring CYGWIN,$(shell uname)), CYGWIN)
	rm -f ../../char-server.exe
else
	rm -f ../../char-server
endif
