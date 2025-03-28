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


# Simple jobs example using mutex for shared and exclusive resource (JOBSMUTEX)
HDR_JOBSMUTEX = $(addprefix $(HEADER_DIR),jobs_mutex.hpp)
SRC_JOBSMUTEX = $(addprefix $(SRC_DIR),jobs_mutex.cpp)
MAIN_JOBSMUTEX = $(addprefix $(MAIN_DIR),test_jobs_mutex.cpp)

# Simple conditional variable wait for some condition example (CONDVARWAIT)
HDR_CONDVARWAIT = $(addprefix $(HEADER_DIR),cond_var_wait.hpp)
SRC_CONDVARWAIT = $(addprefix $(SRC_DIR),cond_var_wait.cpp)
MAIN_CONDVARWAIT = $(addprefix $(MAIN_DIR),test_cond_var_wait.cpp)

# Simple atomic template example (ATOMICTEMPT)
HDR_ATOMICTEMPT = $(addprefix $(HEADER_DIR),atomic_exmp.hpp)
SRC_ATOMICTEMPT = $(addprefix $(SRC_DIR),atomic_exmp.cpp)
MAIN_ATOMICTEMPT = $(addprefix $(MAIN_DIR),test_atomic_exmp.cpp)


# Producer-Consumer example (PRODCOSR)
HDR_PRODCOSR = $(addprefix $(HEADER_DIR),producer_consumer.hpp)
SRC_PRODCOSR = $(addprefix $(SRC_DIR),producer_consumer.cpp)
MAIN_PRODCOSR = $(addprefix $(MAIN_DIR),test_producer_consumer.cpp)


#Object files
OBJS_STHRD = main_SThrd.o src_SThrd.o
OBJS_SVECTHRD = main_SVecThrd.o src_SVecThrd.o
OBJS_SMUTEX = main_SMutex.o src_SMutex.o
OBJS_JOBSMUTEX = main_JobsMutex.o src_JobsMutex.o
OBJS_CONDVARWAIT = main_CondVarWait.o src_CondVarWait.o
OBJS_ATOMICTEMPT = main_AtomicTemplate.o src_AtomicTemplate.o
OBJS_PRODCOSR = main_ProdCosr.o src_ProdCosr.o



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


# Simple jobs example using mutex for shared and exclusive resource (JOBSMUTEX)
main_JobsMutex.o: $(MAIN_JOBSMUTEX)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

src_JobsMutex.o: $(SRC_JOBSMUTEX) $(HDR_JOBSMUTEX)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

test_JobsMutex: $(OBJS_JOBSMUTEX)
	$(CXX) $(CXXASAN) $^ -o $@


# Simple conditional variable wait for some condition example (CONDVARWAIT)
main_CondVarWait.o: $(MAIN_CONDVARWAIT)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

src_CondVarWait.o: $(SRC_CONDVARWAIT) $(HDR_CONDVARWAIT)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

test_CondVarWait: $(OBJS_CONDVARWAIT)
	$(CXX) $(CXXASAN) $^ -o $@


# Simple atomic template example (ATOMICTEMPT)
main_AtomicTemplate.o: $(MAIN_ATOMICTEMPT)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

src_AtomicTemplate.o: $(SRC_ATOMICTEMPT) $(HDR_ATOMICTEMPT)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

test_AtomicTemplate: $(OBJS_ATOMICTEMPT)
	$(CXX) $(CXXASAN) $^ -o $@


# Producer-Consumer example (PRODCOSR)
main_ProdCosr.o: $(MAIN_PRODCOSR)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

src_ProdCosr.o: $(SRC_PRODCOSR) $(HDR_PRODCOSR)
	$(CXX) $(CXXFLAGS) $(CXXASAN) $< -o $@

test_ProdCosr: $(OBJS_PRODCOSR)
	$(CXX) $(CXXASAN) $^ -o $@





.PHONY : clean
clean_SThrd:
	rm test_SThrd $(OBJS_STHRD) 

clean_SVecThrd:
	rm test_SVecThrd $(OBJS_SVECTHRD)

clean_SMutex:
	rm test_SMutex $(OBJS_SMUTEX)

clean_JobsMutex:
	rm test_JobsMutex $(OBJS_JOBSMUTEX)

clean_CondVarWait:
	rm test_CondVarWait $(OBJS_CONDVARWAIT)

clean_AtomicTemplate:
	rm test_AtomicTemplate $(OBJS_ATOMICTEMPT)

clean_ProdCosr:
	rm test_ProdCosr $(OBJS_PRODCOSR)