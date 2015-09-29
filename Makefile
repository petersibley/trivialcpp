SOURCES=$(wildcard *.cpp)

CXX=c++
LD=c++
IFLAGS= -I/usr/include/ -I/usr/local/include
LIBS= -L/usr/lib -L/usr/local/lib -lm -lc++  

#CFLAGS=  -g -D_DEBUG
CFLAGS=   -O3 -std=c++14 -stdlib=libc++
PROGRAM=eg

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))



generatedsources:$(PROGRAM)
	./$(PROGRAM)

test: $(PROGRAM) generatedsources
	$(MAKE) -C tests

all: test

$(PROGRAM) : $(OBJECTS)
	$(LD) $(LIBS) -o $(PROGRAM) $(OBJECTS)

%.o: %.cpp %.h

clean:
	rm -f $(OBJECTS) $(PROGRAM) 
	rm -rf elm/*.cpp
	rm -rf elm/*.h
	rm -rf elm/*.o
	rm -rf tests/*.o

#-include $(OBJECTALL:=.d)
#%.d : %.cpp
#	set -e; $(CXX) -MM $(CFLAGS) $< \
#		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
#		[ -s $@ ] || rm -f $@
#
.SUFFIXES:  .o .cpp
.cpp.o:
	$(CXX) -c $(IFLAGS) $(CFLAGS) -o $@ $<
