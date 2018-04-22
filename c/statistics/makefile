#main/Makefile

out: functions.o main.o
		g++ functions.o main.o -o out

functions.o: functions.c functions.h
		g++ -c functions.c -o functions.o

main.o: main.c
		g++ -c main.c -o main.o