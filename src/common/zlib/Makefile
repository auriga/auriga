# Makefile for zlib
# Copyright (C) 1995-2003 Jean-loup Gailly.
# For conditions of distribution and use, see copyright notice in zlib.h

ifeq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
all: adler32.o compress.o crc32.o deflate.o trees.o zutil.o inflate.o inftrees.o inffast.o
else
all:
endif

clean:
	rm -f *.o
	rm -f GNUmakefile
