# New Makefile that automatically depends itself
#
# $Id: Makefile,v 1.3 1996/12/17 19:52:37 chase Exp $
#

CXX = g++ --std=c++11 -m32
CC  = $(GCC)
GCC = g++ --std=c++11 -m32
LD  = $(CXX)

WFLAGS = -Wall
SYMFLAGS = -g

OPTFLAGS =-w -O
CFLAGS = $(OPTFLAGS) $(WFLAGS) $(SYMFLAGS)
CXXFLAGS = $(CFLAGS)
LDFLAGS = $(PROFILE) -g

PROGRAM = blip

CXXSRCS = $(wildcard *.cpp) $(wildcard nodes/*.cpp)
SRCS = $(CXXSRCS)

OBJS = $(CXXSRCS:.cpp=.o)

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)

clean:
	-rm -f $(OBJS) $(PROGRAM)
