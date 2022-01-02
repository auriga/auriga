# $Id: Makefile,v 1.1 2003/06/20 05:30:43 lemit Exp $

CC = gcc -pipe

# Detecting gcc version
GCC_MAJOR_VERSION = $(shell $(CC) -v 2>&1 | grep '^gcc' | cut -d' ' -f3 | cut -d'.' -f1)
GCC_MINOR_VERSION = $(shell $(CC) -v 2>&1 | grep '^gcc' | cut -d' ' -f3 | cut -d'.' -f2)

# 2020-02-05aRagexeRE: 20200205
# 2019-05-30aRagexeRE: 20190530
# 2018-04-18bRagexeRE: 20180418
# 2017-08-30bRagexeRE: 20170830
# 2017-06-14bRagexeRE: 20170614
# 2016-12-28aRagexeRE: 20161228
# 2015-10-29aRagexeRE: 20151029
# 2015-05-13aRagexe: 20150513
# 2014-10-22bRagexe: 20141022
# 2014-03-05bRagexe: 20140305
# 2014-01-15eRagexe: 20140115
# 2013-12-23cRagexeRE: 20131223
# 2013-07-31aRagexeRE: 20130731
# 2012-09-25aRagexeRE: 20120925
# 2012-06-18aRagexeRE: 20120618
# 2012-04-10aRagexeRE: 20120410
# 2012-04-04aRagexeRE: 20120404
# 2012-03-28aRagexeRE: 20120328
# 2012-03-07aRagexeRE: 20120307
# 2012-02-22aRagexeRE: 20120222
# 2012-02-01aRagexeRE: 20120201
# 2011-11-02aRagexeRE: 20111102
# 2011-10-25aRagexeRE: 20111025
# 2011-09-28aRagexeRE: 20110928
# 2011-07-19aRagexeRE: 20110719
# 2011-03-09aRagexeRE: 20110309
# 2011-01-11aRagexeRE: 20110111
# 2010-10-20aRagexeRE: 20101020
# 2010-08-03aRagexeRE: 20100803
# 2010-07-28aRagexeRE: 20100728
# 2010-07-21aRagexeRE: 20100721
# 2010-06-29aRagexeRE: 20100629
# 2010-06-15aRagexeRE: 20100615
# 2010-04-14aRagexeRE: 20100414
# 2010-02-23aRagexeRE: 20100223
# 2009-12-08aRagexeRE: 20091208
# 2009-11-18cRagexeRE: 20091118
# 2009-11-04aRagexeRE: 20091104
# 2009-07-15aRagexeRE: 20090715
# 2009-06-17aRagexeRE: 20090617
# 2009-06-03aRagexeRE: 20090603
# 2008-11-26cSakexe or 2008-11-26aRagexeRE: 20081126
# 2008-11-13aSakexe: 20081113
# 2008-08-20aSakexe: 20080820
# 2008-05-28aSakexe or 2008-08-27aRagexeRE: 20080827
# 2008-01-02aSakexe: 20080102
# 2007-11-28aSakexe: 20071128
# 2007-11-06aSakexe: 20071106
# 2007-09-04aSakexe: 20070904
# 2007-07-11aSakexe: 20070711
# 2007-05-21aSakexe: 20070521
# 2007-02-12aSakexe: 20070212
# 2006-10-23aSakexe: 20061023
PACKETDEF = -DPACKETVER=20151029 -DNEW_006b

PLATFORM = $(shell uname)

MYSQL_INCLUDE = /usr/local/include/mysql
MYSQL_LIBS = /usr/local/lib/mysql

ifeq ($(findstring CYGWIN,$(PLATFORM)), CYGWIN)
    OS_TYPE = -DCYGWIN -DFD_SETSIZE=4096
endif
ifeq ($(findstring MINGW,$(PLATFORM)), MINGW)
    OS_TYPE = -DMINGW -DFD_SETSIZE=4096
endif

ifeq ($(findstring FreeBSD,$(PLATFORM)), FreeBSD)
    MAKE = gmake
else
    MAKE = make
endif

CFLAGS = -D_XOPEN_SOURCE -D_BSD_SOURCE -Wall -Wextra -I../common -I../common/lua $(PACKETDEF) $(OS_TYPE)
LIBS = -lm

#Link Zlib(NOTrecommended)
#CFLAGS += -DLOCALZLIB

#debug(recommended)
CFLAGS += -g

#optimize(recommended)
#CFLAGS += -O2
#CFLAGS += -O3
#CFLAGS += -ffast-math
ifeq ($(GCC_MAJOR_VERSION), 4)
    ifeq ($(GCC_MINOR_VERSION), 7)
        CFLAGS += -O2
    endif
    ifeq ($(GCC_MINOR_VERSION), 8)
        CFLAGS += -Og
    endif
    ifeq ($(GCC_MINOR_VERSION), 9)
        CFLAGS += -Og
    endif
endif
ifeq ($(GCC_MAJOR_VERSION), 5)
    CFLAGS += -Og
endif
ifeq ($(GCC_MAJOR_VERSION), 6)
    CFLAGS += -Og
endif
ifeq ($(GCC_MAJOR_VERSION), 7)
    CFLAGS += -Og
endif

# C Standard - ISO/IEC 9899:1999
CFLAGS += -std=c99

# Ignore Warning
CFLAGS += -Wno-unused-function -Wno-unused-parameter -Wno-unused-result -Wno-unused-value -Wno-unused-variable
CFLAGS += -Wno-pointer-sign -Wno-sign-compare

# No Strict Aliasing
CFLAGS += -fno-strict-aliasing

ifdef SQLFLAG
    CFLAGS += -I$(MYSQL_INCLUDE)
    LIBS += -L$(MYSQL_LIBS)
        ifeq ($(findstring MINGW32,$(PLATFORM)), MINGW32)
            LIBS += -lmysql
        else
            LIBS += -lmysqlclient
        endif
else
    CFLAGS += -DTXT_ONLY
endif

ifeq ($(findstring MINGW32,$(PLATFORM)), MINGW32)
    CFLAGS += -Wno-unknown-pragmas
    LIBS += -lwsock32 -limagehlp
else
    ifneq ($(findstring LOCALZLIB,$(CFLAGS)), LOCALZLIB)
        LIBS += -lz
    endif
endif

#-----------------BUILD OPTION-------------------
# change authfifo comparing data
#CFLAGS += -DCMP_AUTHFIFO_IP
#CFLAGS += -DCMP_AUTHFIFO_LOGIN2

# disable httpd
CFLAGS += -DNO_HTTPD

# disable httpd-external-CGI
CFLAGS += -DNO_HTTPD_CGI

# disable csvdb via script
#CFLAGS += -DNO_CSVDB_SCRIPT

# usable pre refine system
#CFLAGS += -DPRE_RENEWAL

# usable MB
#CFLAGS += -DCLASS_MB

# enable dynamic memory allocation of status change data
CFLAGS += -DDYNAMIC_SC_DATA

# enable journal system (text mode only)
#CFLAGS += -DTXT_ONLY -DTXT_JOURNAL

# account regist MailAddress
#CFLAGS += -DAC_MAIL

# account regist Birth Date
#CFLAGS += -DAC_BIRTHDATE

# disable save of status change data
#CFLAGS += -DNO_SCDATA_SAVING

# enable timer cache
#CFLAGS += -DTIMER_CACHE=256

#-----------------CPU MARCH-------------------
#GCC 3.2.x~

#i386 (Intel)
#CFLAGS +=-march=i386 -fomit-frame-pointer

#i486 (Intel)
#CFLAGS +=-march=i486 -fomit-frame-pointer

#Pentium 1 (Intel)
#CFLAGS +=-march=pentium -fomit-frame-pointer

#Pentium MMX (Intel)
#CFLAGS +=-march=pentium-mmx -fomit-frame-pointer

#Pentium PRO (Intel)
#CFLAGS +=-march=pentiumpro -fomit-frame-pointer

#Pentium II (Intel)
#CFLAGS +=-march=pentium2 -fomit-frame-pointer

#Celeron (Mendocino), aka Celeron1 (Intel)
#CFLAGS +=-march=pentium2 -fomit-frame-pointer

#Pentium III (Intel)
#CFLAGS +=-march=pentium3 -fomit-frame-pointer

#Pentium III (Intel)
#CFLAGS +=-march=pentium3 -O3 -fomit-frame-pointer
#   -fforce-addr -falign-functions=4 -fprefetch-loop-arrays

#Celeron (Coppermine) aka Celeron2 (Intel)
#CFLAGS +=-march=pentium3 -fomit-frame-pointer

#Celeron (Willamette?) (Intel)
#CFLAGS +=-march=pentium4 -fomit-frame-pointer

#Pentium 4 (Intel)
#CFLAGS +=-march=pentium4 -fomit-frame-pointer -mfpmath=sse -msse -msse2

#optimize for pentium3
#CFLAGS += -march=i686 -mcpu=pentium3 -mfpmath=sse -mmmx -msse

#optimize for pentium4
#CFLAGS += -march=pentium4 -mfpmath=sse -msse -msse2

#Eden C3/Ezra (Via)
#CFLAGS +=-march=i586 -m3dnow -fomit-frame-pointer

#K6 (AMD)
#CFLAGS +=-march=k6 -fomit-frame-pointer

#K6-2 (AMD)
#CFLAGS +=-march=k6-2 -fomit-frame-pointer

#K6-3 (AMD)
#CFLAGS +=-march=k6-3 -fomit-frame-pointer

#Athlon (AMD)
#CFLAGS +=-march=athlon -fomit-frame-pointer

#Athlon-tbird, aka K7 (AMD)
#CFLAGS +=-march=athlon-tbird -fomit-frame-pointer

#Athlon-tbird XP (AMD)
#CFLAGS +=-march=athlon-xp -pipe -msse -mfpmath=sse -mmmx -fomit-frame-pointer

#Athlon 4(AMD)
#CFLAGS +=-march=athlon-4 -m3dnow -fomit-frame-pointer

#Athlon XP (AMD)
#CFLAGS +=-march=athlon-xp -m3dnow -msse -mfpmath=sse -mmmx -fomit-frame-pointer -m3dnow -msse -mfpmath=sse -mmmx

#Athlon MP (AMD)
#CFLAGS +=-march=athlon-mp -m3dnow -msse -mfpmath=sse -mmmx -fomit-frame-pointer

#Athlon XP XX00+
#CFLAGS +=-march=athlon-xp -m3dnow -msse -mfpmath=sse -mmmx
#-fforce-addr -fomit-frame-pointer -funroll-loops -frerun-cse-after-loop
#-frerun-loop-opt -falign-functions=4 -maccumulate-outgoing-args -fprefetch-loop-arrays

#optimize for Athlon-4(mobile Athlon)
#CFLAGS += -march=athlon -m3dnow -msse -mcpu=athlon-4 -mfpmath=sse

#optimize for Athlon-mp
#CFLAGS += -march=athlon -m3dnow -msse -mcpu=athlon-mp -mfpmath=sse

#optimize for Athlon-xp
#CFLAGS += -march=athlon -m3dnow -msse -mcpu=athlon-xp -mfpmath=sse

#603 (PowerPC / Kuro-Box)
#CFLAGS +=-pipe

#603e (PowerPC / Kuro-Box)
#CFLAGS +=-pipe

#604 (PowerPC / Kuro-Box)
#CFLAGS +=-pipe

#604e (PowerPC / Kuro-Box)
#CFLAGS +=-pipe

#750 aka as G3 (PowerPC)
#CFLAGS +=-mcpu=750 -mpowerpc-gfxopt

#7400, aka G4 (PowerPC)
#CFLAGS +=-mcpu=7400 -maltivec
#	-mabi=altivec -mpowerpc-gfxopt
#	-maltivec -mabi=altivec -mpowerpc-gfxopt

#7450, aka G4 second generation (PowerPC)
#CFLAGS +=-mcpu=7450 -pipe
#	-maltivec -mabi=altivec -mpowerpc-gfxopt

#PowerPC (If you don't know which one)
#CFLAGS +=-mpowerpc-gfxopt

#Sparc
#CFLAGS +=-fomit-frame-pointer

#Sparc 64
#CFLAGS +=-fomit-frame-pointer

#Linux Zaurus (SL-C7xx)
#CFLAGS +=-pipe -fomit-frame-pointer -Wstrict-prototypes

#---------------------------------------------------

MKDEF = CC="$(CC)" CFLAGS="$(CFLAGS)" LIBS="$(LIBS)"

all clean: src/common/zlib/GNUmakefile src/common/GNUmakefile src/login/GNUmakefile src/char/GNUmakefile src/map/GNUmakefile src/converter/GNUmakefile
	cd src ; cd common ; $(MAKE) $(MKDEF) $@ ; cd ..
	cd src ; cd common ; cd lua ; $(MAKE) $(MKDEF) $@ ; cd ..
	cd src ; cd common ; cd zlib ; $(MAKE) $(MKDEF) $@ ; cd ..
	cd src ; cd login ; $(MAKE) $(MKDEF) $@ ; cd ..
	cd src ; cd char ; $(MAKE) $(MKDEF) $@ ; cd ..
	cd src ; cd converter ; $(MAKE) $(MKDEF) $@ ; cd ..
	cd src ; cd map ; $(MAKE) $(MKDEF) $@ ; cd ..

ifdef SQLFLAG
sql: src/common/zlib/GNUmakefile src/common/GNUmakefile src/login/GNUmakefile src/char/GNUmakefile src/map/GNUmakefile src/converter/GNUmakefile
	cd src ; cd common ; $(MAKE) $(MKDEF) $@ SQLFLAG=1; cd ..
	cd src ; cd common ; cd lua ; $(MAKE) $(MKDEF) $@ ; cd ..
	cd src ; cd common ; cd zlib ; $(MAKE) $(MKDEF) $@ ; cd ..
	cd src ; cd login ; $(MAKE) $(MKDEF) $@ SQLFLAG=1; cd ..
	cd src ; cd char ; $(MAKE) $(MKDEF) $@ SQLFLAG=1; cd ..
	cd src ; cd converter ; $(MAKE) $(MKDEF) $@ SQLFLAG=1; cd ..
	cd src ; cd map ; $(MAKE) $(MKDEF) $@ SQLFLAG=1; cd ..
else
sql:
	$(MAKE) CC="$(CC)" SQLFLAG=1
endif

src/common/GNUmakefile: src/common/Makefile
	sed -e 's/$$>/$$^/' src/common/Makefile > src/common/GNUmakefile
src/common/lua/GNUmakefile: src/common/lua/Makefile
	sed -e 's/$$>/$$^/' src/common/lua/Makefile > src/common/lua/GNUmakefile
src/common/zlib/GNUmakefile: src/common/zlib/Makefile
	sed -e 's/$$>/$$^/' src/common/zlib/Makefile > src/common/zlib/GNUmakefile
src/login/GNUmakefile: src/login/Makefile
	sed -e 's/$$>/$$^/' src/login/Makefile > src/login/GNUmakefile
src/char/GNUmakefile: src/char/Makefile
	sed -e 's/$$>/$$^/' src/char/Makefile > src/char/GNUmakefile
src/map/GNUmakefile: src/map/Makefile
	sed -e 's/$$>/$$^/' src/map/Makefile > src/map/GNUmakefile
src/converter/GNUmakefile: src/converter/Makefile
	sed -e 's/$$>/$$^/' src/converter/Makefile > src/converter/GNUmakefile
