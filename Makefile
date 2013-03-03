# Makefile for Irrlicht Examples: Stripped for a template
# It's usually sufficient to change just the target name and source file list
# and be sure that CXX is set to a valid compiler

# Note: Lines after >>>>>> comments should be updated

# >>>>> Executable file name (.exe appended if necessary) 
Target := Borbie\'s\ Big\ Adventure

# >>>>> Space-separated list of source files
Sources := main.cpp

# >>>>> Folder where Irrlicht is installed (no ending '/')
IrrlichtHome := /home/student/miodowj195/Desktop/Games/irrlicht-1.8

# >>>>> Folder for output file (no ending '/')
# win32 note: should contain a copy of Irrlicht.dll
BinPath = bin/

# >>>>> Full path of root of the sample code (where assets lives)
PathToRootOfDemo=$(CURDIR)

# ------------------------------------------------------------------------
# User-defined compiler flags; may need to match library compiler flags
# ------------------------------------------------------------------------

# preprocessor flags, e.g. defines and include paths
USERCPPFLAGS = -DROOT_DIR=$(PathToRootOfDemo)

# compiler flags such as optimization flags; uncomment one or the other
# Optimized build --------------------------------------------------------
USERCXXFLAGS = -O3 -ffast-math
# Debugging build --------------------------------------------------------
# USERCXXFLAGS = -g -Wall

# linker flags such as additional libraries and link paths
USERLDFLAGS =

####
#no changes necessary below this line
####

CPPFLAGS = -I$(IrrlichtHome)/include -I/usr/X11R6/include $(USERCPPFLAGS)
CXXFLAGS = $(USERCXXFLAGS)
LDFLAGS = $(USERLDFLAGS)

#default target is Linux
all: all_linux

# target specific settings
all_linux all_win32 stabtic_win32: LDFLAGS += -L$(IrrlichtHome)/lib/$(SYSTEM) -lIrrlicht
all_linux: LDFLAGS += -L/usr/X11R6/lib$(LIBSELECT) -lGL -lXxf86vm -lXext -lX11 -lXcursor
all_linux clean_linux: SYSTEM=Linux
all_win32 clean_win32 static_win32: SYSTEM=Win32-gcc
all_win32 clean_win32 static_win32: SUF=.exe
static_win32: CPPFLAGS += -D_IRR_STATIC_LIB_
all_win32: LDFLAGS += -lopengl32 -lm
static_win32: LDFLAGS += -lgdi32 -lwinspool -lcomdlg32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 -lopengl32
# name of the binary - only valid for targets which set SYSTEM
DESTPATH = $(BinPath)/$(Target)$(SUF)

all_linux all_win32 static_win32: $(BinPath)
	$(warning Building...)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(Sources) -o $(DESTPATH) $(LDFLAGS)

clean: clean_linux clean_win32
	$(warning Cleaning...)

clean_linux clean_win32:
	@$(RM) $(DESTPATH)

$(BinPath):
	mkdir -p $(BinPath)

.PHONY: all all_win32 static_win32 clean clean_linux clean_win32

#multilib handling
ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif
#solaris real-time features
ifeq ($(HOSTTYPE), sun4)
LDFLAGS += -lrt
endif

