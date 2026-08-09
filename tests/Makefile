# Unit tests (Unity). Independent from production server builds.
#
# Source lists are shared conceptually with vc_test.bat / vc_test_clean.bat.
# When adding a test .c under tests/, update TEST_SRCS here and the matching
# for-loops in the .bat files (see doc/unit_test.txt).

# Use gcc by default (Make's built-in CC is "cc", so ?= would not override it).
CC = gcc

UNITY_DIR = ../third_party/unity/src
COMMON_DIR = ../src/common

CFLAGS = -std=c11 -Wall -Wextra -Og -I$(COMMON_DIR) -I$(UNITY_DIR)

TEST_SRCS = \
	test_main.c \
	test_md5calc.c \
	test_utils.c \
	test_db.c \
	test_misc.c

COMMON_NAMES = md5calc utils db lock nullpo

TEST_OBJS = $(TEST_SRCS:.c=.o)
COMMON_OBJS = $(addsuffix .o,$(COMMON_NAMES))
LOCAL_OBJS = $(TEST_OBJS) stubs/malloc_stub.o $(COMMON_OBJS) unity.o

TARGET = unit_tests

.PHONY: all test clean

all: test

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(LOCAL_OBJS)
	$(CC) $(CFLAGS) -o $@ $(LOCAL_OBJS)

$(TEST_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

stubs/malloc_stub.o: stubs/malloc_stub.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(COMMON_OBJS): %.o: $(COMMON_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

unity.o: $(UNITY_DIR)/unity.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(LOCAL_OBJS)
