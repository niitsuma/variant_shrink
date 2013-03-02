CC		= g++

INCDIR		= /usr/local/include
#INCDIR		= /opt/local/include

#CFLAGS		= -std=c++0x -Wall \

CFLAGS		= -Wall \
		-I/$(INCDIR) \
		-I.

OBJS		= $(SRCS:.c=.o)

PROGRAM		= variant_shrink_test.exe example.exe
#PROGRAM		= unit_test.exe
#PROGRAM		= test.exe


.PHONY: all

all:	$(PROGRAM)


%.exe: %.cpp variant_shrink.hpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $<

#all:variant_shrink_test

test : variant_shrink_test.exe
	./variant_shrink_test.exe



#variant_shrink_test.exe : variant_shrink_test.cpp variant_shrink.hpp
#	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) variant_shrink_test.cpp -o variant_shrink_test.exe


