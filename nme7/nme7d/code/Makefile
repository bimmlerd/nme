CC=g++
CFLAGS=-std=c++11 -c -Wall
LDFLAGS=
SOURCES=pi_approx.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=pi_approx

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
