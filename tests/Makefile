SOURCES=$(wildcard *.cpp)
ELMSOURCES=$(wildcard ../elm/*.cpp)

CXX=c++
LD=c++
IFLAGS= -I/usr/include/ -I/usr/local/include -I../
LIBS= -L/usr/lib -L/usr/local/lib -lm -lc++  

#CFLAGS=  -g -D_DEBUG
CFLAGS=   -O3 -std=c++14 -stdlib=libc++
PROGRAM=test

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
ELMOBJECTS = $(patsubst %.cpp,%.o,$(ELMSOURCES))

all: $(PROGRAM)
	./test

$(PROGRAM) : $(OBJECTS) $(ELMOBJECTS)
	$(LD) $(LIBS) -o $(PROGRAM) $(OBJECTS) $(ELMOBJECTS)

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
