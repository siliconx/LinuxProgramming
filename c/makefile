#main/Makefile

all: executable

executable: source.o main.o
		g++ source.o main.o -o executable $(CXXFLAGS)

source.o: source.c source.h
		g++ -c source.c -o source.o $(CXXFLAGS)

main.o: main.c
		g++ -c main.c -o main.o $(CXXFLAGS)