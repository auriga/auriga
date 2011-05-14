# Makefile for zlib
# Copyright (C) 1995-2003 Jean-loup Gailly.
# For conditions of distribution and use, see copyright notice in zlib.h

ZLIB_SRC = $(shell ls *.c)

ifeq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
all: $(ZLIB_SRC:.c=.o)
else
all:
endif

clean:
	rm -f *.o
	rm -f GNUmakefile
