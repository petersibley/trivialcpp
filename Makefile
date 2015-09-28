SOURCES=$(wildcard *.cpp)

CXX=c++
LD=c++
IFLAGS= -I/usr/include/ -I/usr/local/include
# Install boost via homebrew 
LIBS= -L/usr/lib -L/usr/local/lib -lm -lc++  -lboost_timer-mt -lboost_system-mt

#CFLAGS=  -g -D_DEBUG
CFLAGS=   -O3 -std=c++14 -stdlib=libc++
PROGRAM=test

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

all: $(PROGRAM)

$(PROGRAM) : $(OBJECTS)
	$(LD) $(LIBS) -o $(PROGRAM) $(OBJECTS)

%.o: %.cpp %.h

clean:
	rm -f $(OBJECTS) $(PROGRAM) 

#-include $(OBJECTALL:=.d)
#%.d : %.cpp
#	set -e; $(CXX) -MM $(CFLAGS) $< \
#		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
#		[ -s $@ ] || rm -f $@
#
.SUFFIXES:  .o .cpp
.cpp.o:
	$(CXX) -c $(IFLAGS) $(CFLAGS) -o $@ $<
