HEADER_DIR = ./header/
SRC_DIR = ./source/
MAIN_DIR = ./test/

CXX = g++
CXXFLAGS = -Wall -Werror -c -g3 -O3
CXX11 = -std=c++11
CXXASAN = -fsanitize=address


## Using -fsanitize=thread could return following memory mapping error
## FATAL: ThreadSanitizer: unexpected memory mapping
## 
## then one (temporary) solution could be to run
## sudo sysctl vm.mmap_rnd_bits=30
CXXTSAN = -fsanitize=thread


# Simple Thread example (STHRD)
HDR_STHRD = $(addprefix $(HEADER_DIR),simple_thread.hpp)
SRC_STHRD = $(addprefix $(SRC_DIR),simple_thread.cpp)
MAIN_STHRD = $(addprefix $(MAIN_DIR),test_simple_thread.cpp)




#Object files
OBJS_STHRD = main_SThrd.o src_SThrd.o



# Simple Thread example (STHRD)
main_SThrd.o: $(MAIN_STHRD)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

src_SThrd.o: $(SRC_STHRD) $(HDR_STHRD)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

test_SThrd: $(OBJS_STHRD)
	$(CXX) $(CXXASAN) $^ -o $@




.PHONY : clean
clean_SThrd:
	rm test_SThrd $(OBJS_STHRD) 

