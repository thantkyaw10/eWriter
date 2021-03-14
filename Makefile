SRCS= IT8951.c miniGUI.c main.c AsciiLib.c bmp.c eWriter.c
 
CC= gcc

# name for executable
EXE = eWriter

CFLAGS = -Wall

# space-separated list of header files
HDRS = AsciiLib.h eWriter.h IT8951.h miniGUI.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS = -lbcm2835

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)


# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o

