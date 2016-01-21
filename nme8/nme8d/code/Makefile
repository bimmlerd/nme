CC=g++
CFLAGS=-I/usr/local/include/eigen3/ -std=c++11 -c -Wall -O3
LDFLAGS=
SOURCES=NatCSI.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=natcsi

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
