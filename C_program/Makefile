HEADER_DIR = ./header/
SRC_DIR = ./source/
MAIN_DIR = ./test/

CC = gcc
CFLAGS = -Wall -Werror -c -g3 -O3


# Simple Thread Example (STHRD)
HDR_STHRD = $(addprefix $(HEADER_DIR),simple_thread.h)
SRC_STHRD = $(addprefix $(SRC_DIR),simple_thread.c)
MAIN_STHRD = $(addprefix $(MAIN_DIR),test_simple_thread.c)


# Using loop to create threads and passing argument (LPARGTHRD)
HDR_LPARGTHRD = $(addprefix $(HEADER_DIR),loop_arg.h)
SRC_LPARGTHRD = $(addprefix $(SRC_DIR),loop_arg.c)
MAIN_LPARGTHRD = $(addprefix $(MAIN_DIR),test_loop_arg.c)


# Multi-threading using mutex (MUTEXTHRD)
HDR_MUTEXTHRD = $(addprefix $(HEADER_DIR),simple_mutex.h)
SRC_MUTEXTHRD = $(addprefix $(SRC_DIR),simple_mutex.c)
MAIN_MUTEXTHRD = $(addprefix $(MAIN_DIR),test_simple_mutex.c)



#Object files
OBJS_STHRD = main_SThrd.o src_SThrd.o
OBJS_LPARGTHRD = main_LPArgThrd.o src_LPArgThrd.o
OBJS_MUTEXTHRD = main_MutexThrd.o src_MutexThrd.o


# Simple Thread (STHRD)
main_SThrd.o: $(MAIN_STHRD)
	$(CC) $(CFLAGS) $< -o $@

src_SThrd.o: $(SRC_STHRD) $(HDR_STHRD)
	$(CC) $(CFLAGS) $< -o $@

test_SThrd: $(OBJS_STHRD)
	$(CC) $^ -o $@



# Passing argument to Thread (LPARGTHRD)
main_LPArgThrd.o: $(MAIN_LPARGTHRD)
	$(CC) $(CFLAGS) $< -o $@

src_LPArgThrd.o: $(SRC_LPARGTHRD) $(HDR_LPARGTHRD)
	$(CC) $(CFLAGS) $< -o $@

test_LPArgThrd: $(OBJS_LPARGTHRD)
	$(CC) $^ -o $@


# Multi-threading using mutex (MUTEXTHRD)
main_MutexThrd.o: $(MAIN_MUTEXTHRD)
	$(CC) $(CFLAGS) $< -o $@

src_MutexThrd.o: $(SRC_MUTEXTHRD) $(HDR_MUTEXTHRD)
	$(CC) $(CFLAGS) $< -o $@

test_MutexThrd: $(OBJS_MUTEXTHRD)
	$(CC) $^ -o $@




.PHONY : clean
clean_SThrd:
	rm test_SThrd $(OBJS_STHRD)

clean_LPArgThrd:
	rm test_LPArgThrd $(OBJS_LPARGTHRD)

clean_MutexThrd:
	rm test_MutexThrd $(OBJS_MUTEXTHRD)