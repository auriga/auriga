all: login-server

COMMON_SRC = $(shell ls ../common/*.c)

ifeq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
COMMON_SRC += $(shell ls ../common/zlib/*.c)
endif

ifdef SQLFLAG
	LOGIN_SRC = $(shell ls *.c | grep -v '_txt\.c')
else
	LOGIN_SRC = $(shell ls *.c | grep -v '_sql\.c')
endif

login-server: $(LOGIN_SRC:.c=.o) $(COMMON_SRC:.c=.o)
	$(CC) -o ../../$@ $> $(LIBS)

clean:
	rm -f *.o
	rm -f GNUmakefile

ifeq ($(findstring CYGWIN,$(shell uname)), CYGWIN)
	rm -f ../../login-server.exe
else
	rm -f ../../login-server
endif
