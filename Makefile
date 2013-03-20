
# Makefile for Irrlicht Examples: Stripped for a template
# It's usually sufficient to change just the target name and source file list
# and be sure that CXX is set to a valid compiler

# Note: Lines after >>>>>> comments should be updated
# >>>>> Executable file name (.exe appended if necessary) 
Target := BorbiesBigAdventure

# >>>>> Space-separated list of source files
Sources := $(shell ls -t src/ | grep .cpp)
Objects = $(addprefix obj/, $(Sources:.cpp=.o))

# >>>>> Folder for output file (no ending '/')
BinPath = bin

# Get the OS Size
OS_SIZE = $(shell uname -m | sed -e "s/i.86/32/" -e "s/x86_64/64/")

CPPFLAGS = -DROOT_DIR=.
CXXFLAGS = -g -O3 -ffast-math
# >>>>> Where to look for for headers
INCLUDES += -Iinclude/irrlicht -Iinclude/fmod

# >>>>> Where to look for for libs
# Local Irrlicht and FMOD libraries
LDFLAGS += -Llib/$(OS_SIZE) -lIrrlicht -lfmodex
# system
LDFLAGS += -L/usr/X11R6/lib -lGL -lXxf86vm -lXext -lX11 -lXcursor

all: prep game

test:
	@echo $(Objects)

prep:
	@mkdir -p bin
	@mkdir -p obj


obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $< $(CPPFLAGS) 

game: $(Objects)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $? -o $(BinPath)/$(Target) $(LDFLAGS) -Wl,-rpath=lib/$(OS_SIZE) $(CPPFLAGS)

clean:
	$(RM) -r $(BinPath)
	$(RM) -r obj

