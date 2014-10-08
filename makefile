CFLAGS = -c
CC = gcc -Wall

all: process.o queue.o main.o fcfs.o rr.o util.o
	$(CC) -o prog3 main.o process.o queue.o fcfs.o rr.o util.o -lm

debug: CC += -DDEBUG -g
debug: all

main.o: main.c queue.h process.h fcfs.h util.h rr.h
	$(CC) $(CFLAGS) main.c

rr.o: rr.h rr.c queue.h process.h util.h
	$(CC) $(CFLAGS) rr.c

fcfs.o: fcfs.h fcfs.c queue.h process.h util.h
	$(CC) $(CFLAGS) fcfs.c

queue.o: queue.cpp queue.h process.h
	g++ $(CFLAGS) queue.cpp -lm

process.o: process.cpp process.h
	g++ $(CFLAGS) process.cpp

util.o: util.c util.h queue.h
	$(CC) $(CFLAGS) util.c

clean:
	rm -rf prog3 *.o 2> /dev/null
