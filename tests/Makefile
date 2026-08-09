# Unit tests (Unity). Independent from production server builds.

# Use gcc by default (Make's built-in CC is "cc", so ?= would not override it).
CC = gcc

UNITY_DIR = ../third_party/unity/src
COMMON_DIR = ../src/common

CFLAGS = -std=c11 -Wall -Wextra -Og -I$(COMMON_DIR) -I$(UNITY_DIR)

SRCS = \
	test_main.c \
	test_md5calc.c \
	test_utils.c \
	stubs/malloc_stub.c \
	$(COMMON_DIR)/md5calc.c \
	$(COMMON_DIR)/utils.c \
	$(UNITY_DIR)/unity.c

# Object paths kept under tests/ (not next to production .c files).
LOCAL_OBJS = \
	test_main.o \
	test_md5calc.o \
	test_utils.o \
	stubs/malloc_stub.o \
	md5calc.o \
	utils.o \
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

stubs/malloc_stub.o: stubs/malloc_stub.c
	$(CC) $(CFLAGS) -c -o $@ $<

md5calc.o: $(COMMON_DIR)/md5calc.c
	$(CC) $(CFLAGS) -c -o $@ $<

utils.o: $(COMMON_DIR)/utils.c
	$(CC) $(CFLAGS) -c -o $@ $<

unity.o: $(UNITY_DIR)/unity.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(LOCAL_OBJS)
