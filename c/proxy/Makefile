CC=g++

all: proxy

proxy: proxy.c
	$(CC)  -o proxy.o -c proxy.c
	$(CC)  -o proxy proxy.o

clean:
	rm -f proxy *.o
