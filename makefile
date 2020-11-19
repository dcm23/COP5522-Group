C=gcc
CFLAG= -Wall -I.. -I. -O3

EXECUTABLE=passguess

all: $(EXECUTABLE)

passguess:  passguess.c microtime.h
	$(CC) $(CFLAG) -c microtime.c
	$(CC) $(CFLAG) -o passguess passguess.c microtime.o

clean:
	rm -f *.o *~ core

realclean:
	rm -f *.o *~ core $(EXECUTABLE)
