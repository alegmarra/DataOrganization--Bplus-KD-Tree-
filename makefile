SRCPATH=src/
TARGETPATH=lib/
SOURCES := $(shell find $(SRCPATH) -name *.cpp)
OBJECTS := $(patsubst $(TARGETPATH)%.cpp,$(TARGETPATH)%.o,$(SOURCES))
EXECUTABLE=run
CC=g++
CFLAGS=-I$(SRCPATH)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(CFLAGS)
	
lib/%.o: src/%cpp
	echo $(SOURCES)
	$(CC) -c -o $@ $<
	
clean:
	rm -rf $(TARGETPATH) $(EXECUTABLE) > /dev/null 2>&1
