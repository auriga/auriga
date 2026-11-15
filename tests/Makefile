# Unit tests (Unity). Independent from production server builds.
#
# Source lists are shared conceptually with vc_test.bat / vc_test_clean.bat.
# When adding a test .c under tests/, update TEST_SRCS here and the matching
# for-loops in the .bat files (see doc/unit_test.txt).

# Use gcc by default (Make's built-in CC is "cc", so ?= would not override it).
CC = gcc

UNITY_DIR = ../third_party/unity/src
COMMON_DIR = ../src/common
XXHASH_DIR = ../third_party/xxhash
LZ4_DIR = ../third_party/lz4

CFLAGS = -std=c11 -Wall -Wextra -Og -I$(COMMON_DIR) -I$(UNITY_DIR) -I../src/map -I$(XXHASH_DIR) -I$(LZ4_DIR)

TEST_SRCS = \
	test_main.c \
	test_md5calc.c \
	test_utils.c \
	test_db.c \
	test_misc.c \
	test_status_calc_ctrl.c \
	test_pc_ui.c \
	test_cashshop.c \
	test_stylist.c \
	test_grf_protected.c

COMMON_NAMES = md5calc utils db lock nullpo grf_protected

STUB_SRCS = stubs/malloc_stub.c stubs/grfio_stub.c

MAP_CTRL_SRC = ../src/map/status_calc_ctrl.c
MAP_CTRL_OBJ = status_calc_ctrl.o
MAP_UI_OBJ = pc_ui.o
MAP_CASH_OBJ = cashshop.o
MAP_STYLIST_OBJ = stylist.o

TEST_OBJS = $(TEST_SRCS:.c=.o)
STUB_OBJS = $(STUB_SRCS:.c=.o)
COMMON_OBJS = $(addsuffix .o,$(COMMON_NAMES))
LOCAL_OBJS = $(TEST_OBJS) $(STUB_OBJS) $(COMMON_OBJS) $(MAP_CTRL_OBJ) $(MAP_UI_OBJ) $(MAP_CASH_OBJ) $(MAP_STYLIST_OBJ) lz4.o unity.o

TARGET = unit_tests

.PHONY: all test clean

all: test

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(LOCAL_OBJS)
	$(CC) $(CFLAGS) -o $@ $(LOCAL_OBJS)

$(TEST_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(STUB_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(COMMON_OBJS): %.o: $(COMMON_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAP_CTRL_OBJ): $(MAP_CTRL_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAP_UI_OBJ): ../src/map/pc_ui.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAP_CASH_OBJ): ../src/map/cashshop.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAP_STYLIST_OBJ): ../src/map/stylist.c
	$(CC) $(CFLAGS) -c -o $@ $<

lz4.o: $(LZ4_DIR)/lz4.c
	$(CC) $(CFLAGS) -c -o $@ $<

unity.o: $(UNITY_DIR)/unity.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(LOCAL_OBJS)