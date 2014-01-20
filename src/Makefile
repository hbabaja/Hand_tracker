CC = g++
CFLAGS = -O0
LIBS = `pkg-config opencv --cflags --libs` -lXtst -lgomp

TARGETS = HandTracker

default: HandTracker

all: $(TARGETS)

HandTracker: main.o
	$(CC) $(CFLAGS) main.o $(LIBS) -o HandTracker

clean:
	rm -f *.o *~ a.out $(TARGETS)

.c.o:
	$(CC) -c $(CFLAGS) $<


