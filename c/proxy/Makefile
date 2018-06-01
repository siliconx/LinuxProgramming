CC=g++
CFLAGS= -g -Wall -Werror

all: proxy

proxy: proxy.c
	$(CC) $(CFLAGS) -o proxy.o -c proxy.c
	$(CC) $(CFLAGS) -o proxy proxy.o

clean:
	rm -f proxy *.o

tar:
	tar -cvzf z6110x0002_ass3_$(USER).tgz proxy.c README Makefile
