CC = gcc
COMMOBJS = 
HEADERS  = cookies.h
SERVOBJS = fortune-server.o cookies.o common-lib.o
SERVOBJT = cookies.o common-lib.o 
COOKOBJS = fortune-client.o common-lib.o
COOKIESO = cookies.o
OBJS = $(SERVOBJS) $(COOKOBJS) $(COMMOBJS) $(COOKIESO)
CFLAGS = -Wall -Wfatal-errors -std=gnu99 -g 

LDLIBS = 
EXECS =	fortune-server fortune-client fetch serve

LFLAGS = 

all: $(EXECS)

%.o: %.c 
	$(CC) -c $(CFLAGS) $<

fetch: common-lib.o

serve: common-lib.o serve.c
	$(CC) -o $@ $(LFLAGS) serve.c common-lib.o -pthread

fortune-server: $(SERVOBJS)
	$(CC) -o $@ $(LFLAGS) $(SERVOBJS)

fortune-client: $(COOKOBJS)
	$(CC) -o $@ $(LFLAGS) $(COOKOBJS)

clean:
	/bin/rm -f $(OBJS) $(EXECS) *~
