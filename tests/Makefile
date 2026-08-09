# Unit tests (Unity). Independent from production server builds.

# Use gcc by default (Make's built-in CC is "cc", so ?= would not override it).
CC = gcc

UNITY_DIR = ../third_party/unity/src
COMMON_DIR = ../src/common

CFLAGS = -std=c11 -Wall -Wextra -Og -I$(COMMON_DIR) -I$(UNITY_DIR)

# Object paths kept under tests/ (not next to production .c files).
LOCAL_OBJS = \
	test_main.o \
	test_md5calc.o \
	test_utils.o \
	test_db.o \
	test_misc.o \
	stubs/malloc_stub.o \
	md5calc.o \
	utils.o \
	db.o \
	lock.o \
	nullpo.o \
	unity.o

TARGET = unit_tests

.PHONY: all test clean

all: test

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(LOCAL_OBJS)
	$(CC) $(CFLAGS) -o $@ $(LOCAL_OBJS)

test_main.o: test_main.c
	$(CC) $(CFLAGS) -c -o $@ $<

test_md5calc.o: test_md5calc.c
	$(CC) $(CFLAGS) -c -o $@ $<

test_utils.o: test_utils.c
	$(CC) $(CFLAGS) -c -o $@ $<

test_db.o: test_db.c
	$(CC) $(CFLAGS) -c -o $@ $<

test_misc.o: test_misc.c
	$(CC) $(CFLAGS) -c -o $@ $<

stubs/malloc_stub.o: stubs/malloc_stub.c
	$(CC) $(CFLAGS) -c -o $@ $<

md5calc.o: $(COMMON_DIR)/md5calc.c
	$(CC) $(CFLAGS) -c -o $@ $<

utils.o: $(COMMON_DIR)/utils.c
	$(CC) $(CFLAGS) -c -o $@ $<

db.o: $(COMMON_DIR)/db.c
	$(CC) $(CFLAGS) -c -o $@ $<

lock.o: $(COMMON_DIR)/lock.c
	$(CC) $(CFLAGS) -c -o $@ $<

nullpo.o: $(COMMON_DIR)/nullpo.c
	$(CC) $(CFLAGS) -c -o $@ $<

unity.o: $(UNITY_DIR)/unity.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(LOCAL_OBJS)
