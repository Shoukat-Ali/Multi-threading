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


# Chef and stove multi-threading using mutex (CHEFSTOVEMUTEX)
HDR_CHEFSTOVEMUTEX = $(addprefix $(HEADER_DIR),chef_stove.h)
SRC_CHEFSTOVEMUTEX = $(addprefix $(SRC_DIR),chef_stove.c)
MAIN_CHEFSTOVEMUTEX = $(addprefix $(MAIN_DIR),test_chef_stove.c)


# Detached threads exmaple (DTCHTHRD)
HDR_DTCHTHRD = $(addprefix $(HEADER_DIR),detached_threads.h)
SRC_DTCHTHRD = $(addprefix $(SRC_DIR),detached_threads.c)
MAIN_DTCHTHRD = $(addprefix $(MAIN_DIR),test_detached_threads.c)


# Simple Producer and Consumer using mutex and conditional variable exmaple (SPRODCOSM)
HDR_SPRODCOSM = $(addprefix $(HEADER_DIR),simple_prod_cosm.h)
SRC_SPRODCOSM = $(addprefix $(SRC_DIR),simple_prod_cosm.c)
MAIN_SPRODCOSM = $(addprefix $(MAIN_DIR),test_simple_prod_cosm.c)



#Object files
OBJS_STHRD = main_SThrd.o src_SThrd.o
OBJS_LPARGTHRD = main_LPArgThrd.o src_LPArgThrd.o
OBJS_MUTEXTHRD = main_MutexThrd.o src_MutexThrd.o
OBJS_CHEFSTOVEMUTEX = main_ChefStoveMutex.o src_ChefStoveMutex.o
OBJS_DTCHTHRD = main_DetachThrd.o src_DetachThrd.o
OBJS_SPRODCOSM = main_SProdCosm.o src_SProdCosm.o



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



# Chef and stove multi-threading using mutex (CHEFSTOVEMUTEX)
main_ChefStoveMutex.o: $(MAIN_CHEFSTOVEMUTEX)
	$(CC) $(CFLAGS) $< -o $@

src_ChefStoveMutex.o: $(SRC_CHEFSTOVEMUTEX) $(HDR_CHEFSTOVEMUTEX)
	$(CC) $(CFLAGS) $< -o $@

test_ChefStoveMutex: $(OBJS_CHEFSTOVEMUTEX)
	$(CC) $^ -o $@


# Detached threads exmaple (DTCHTHRD)
main_DetachThrd.o: $(MAIN_DTCHTHRD)
	$(CC) $(CFLAGS) $< -o $@

src_DetachThrd.o: $(SRC_DTCHTHRD) $(HDR_DTCHTHRD)
	$(CC) $(CFLAGS) $< -o $@

test_DetachThrd: $(OBJS_DTCHTHRD)
	$(CC) $^ -o $@


# Simple Producer and Consumer using mutex and conditional variable exmaple (SPRODCOSM)
main_SProdCosm.o: $(MAIN_SPRODCOSM)
	$(CC) $(CFLAGS) $< -o $@

src_SProdCosm.o: $(SRC_SPRODCOSM) $(HDR_SPRODCOSM)
	$(CC) $(CFLAGS) $< -o $@

test_SProdCosm: $(OBJS_SPRODCOSM)
	$(CC) $^ -o $@




.PHONY : clean
clean_SThrd:
	rm test_SThrd $(OBJS_STHRD)

clean_LPArgThrd:
	rm test_LPArgThrd $(OBJS_LPARGTHRD)

clean_MutexThrd:
	rm test_MutexThrd $(OBJS_MUTEXTHRD)

clean_ChefStoveMutex:
	rm test_ChefStoveMutex $(OBJS_CHEFSTOVEMUTEX)

clean_DetachThrd:
	rm test_DetachThrd $(OBJS_DTCHTHRD)

clean_SProdCosm:
	rm test_SProdCosm $(OBJS_SPRODCOSM)