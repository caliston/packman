# Makefile for PackMan

#include FixDeps:Rules/make

CXX=g++
CXXFLAGS = -O2 -Wall -mpoke-function-name -mthrowback -ITBX: -ILibPKG: -ILibCurl: -I../LibPkg/\!LibPkg

# extra libs required by autobuilder libcurl
#EXTRALIBS = -lssh2 -lssl -lcrypto

LD = g++
LDFLAGS = -LTBX: -ltbx -L../LibPkg/\!LibPkg -lpkg -LRTK: -lrtk -LLibCurl: -lcurl -LZLib: -lz -lstdc++ -static $(EXTRALIBS)

TARGET=!PackMan/!RunImage,ff8

CCSRC = $(wildcard src/*.cc)
OBJECTS = $(CCSRC:.cc=.o)

all:	$(TARGET)

$(TARGET): packman
	elf2aif packman $(TARGET)

packman:	$(OBJECTS)
	$(LD) $(LDFLAGS) -o packman $(OBJECTS)

#include $(CCSRC:.cc=.d)

clean:
	rm -f $(TARGET)
	rm -f $(OBJECTS)
