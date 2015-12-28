#------------------------------------------------------------------------------
PROGRAM=eigentest
SOURCE=$(PROGRAM).cpp
OBJECT=$(SOURCE).o
EIGEN=/usr/local/include/eigen3
BOOST=/usr/local/lib/libboost_program_options-mt.dylib

CC=clang
CC_OPT=-D_HAS_CPP0X -std=c++11 -Wall -g -Wno-deprecated-register -DEIGEN3_ACTIVATED
CPPC=clang++
CPPC_OPT=-std=c++11 -Wall -g -Wno-deprecated-register -DEIGEN3_ACTIVATED -Wl,-search_paths_first -Wl,-headerpad_max_install_names
#------------------------------------------------------------------------------

all: $(PROGRAM)

$(PROGRAM): $(SOURCE)
	$(CC) $(CC_OPT) -I$(EIGEN) -o $(OBJECT) -c $(SOURCE)
	$(CPPC) $(CPPC_OPT) $(OBJECT) -o$(PROGRAM) $(BOOST)

clean:
	rm -f $(PROGRAM)
