all: login-server

COMMON_SRC = $(shell ls ../common/*.c)

ifeq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
COMMON_SRC += $(shell ls ../common/zlib/*.c)
endif

LOGIN_SRC = $(shell ls *.c)
ifdef SQLFLAG
	LOGIN_SRC += $(shell ls sql/*.c)
else
	LOGIN_SRC += $(shell ls txt/*.c)
endif

login-server: $(LOGIN_SRC:.c=.o) $(COMMON_SRC:.c=.o)
	$(CC) -o ../../$@ $> $(LIBS)

clean:
	rm -f *.o
ifdef SQLFLAG
	rm -f sql/*.o
else
	rm -f txt/*.o
endif
	rm -f GNUmakefile

ifeq ($(findstring CYGWIN,$(shell uname)), CYGWIN)
	rm -f ../../login-server.exe
else
	rm -f ../../login-server
endif
