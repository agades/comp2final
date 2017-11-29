CC = gcc
LDLIBS=-lrt
CFLAGS=-g -Wall
TARGETS = final
all: $(TARGETS)

final: main.c parser.c http_worker.c recurso.c ardconnect.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -fv $(TARGETS) *.o  
