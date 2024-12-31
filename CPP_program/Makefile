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

# Simple Vector Thread example using normal and lambda function (SVECTHRD)
HDR_SVECTHRD = $(addprefix $(HEADER_DIR),thread_vec.hpp)
SRC_SVECTHRD = $(addprefix $(SRC_DIR),thread_vec.cpp)
MAIN_SVECTHRD = $(addprefix $(MAIN_DIR),test_thread_vec.cpp)


# Simple mutex example using class (SMUTEX)
HDR_SMUTEX = $(addprefix $(HEADER_DIR),simple_mutex.hpp)
SRC_SMUTEX = $(addprefix $(SRC_DIR),simple_mutex.cpp)
MAIN_SMUTEX = $(addprefix $(MAIN_DIR),test_simple_mutex.cpp)



#Object files
OBJS_STHRD = main_SThrd.o src_SThrd.o
OBJS_SVECTHRD = main_SVecThrd.o src_SVecThrd.o
OBJS_SMUTEX = main_SMutex.o src_SMutex.o



# Simple Thread example (STHRD)
main_SThrd.o: $(MAIN_STHRD)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

src_SThrd.o: $(SRC_STHRD) $(HDR_STHRD)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

test_SThrd: $(OBJS_STHRD)
	$(CXX) $(CXXASAN) $^ -o $@


# Simple Vector Thread example using normal and lambda function (SVECTHRD)
main_SVecThrd.o: $(MAIN_SVECTHRD)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

src_SVecThrd.o: $(SRC_SVECTHRD) $(HDR_SVECTHRD)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

test_SVecThrd: $(OBJS_SVECTHRD)
	$(CXX) $(CXXASAN) $^ -o $@


# Simple mutex example using class (SMUTEX)
main_SMutex.o: $(MAIN_SMUTEX)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

src_SMutex.o: $(SRC_SMUTEX) $(HDR_SMUTEX)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

test_SMutex: $(OBJS_SMUTEX)
	$(CXX) $(CXXASAN) $^ -o $@



.PHONY : clean
clean_SThrd:
	rm test_SThrd $(OBJS_STHRD) 

clean_SVecThrd:
	rm test_SVecThrd $(OBJS_SVECTHRD)

clean_SMutex:
	rm test_SMutex $(OBJS_SMUTEX)