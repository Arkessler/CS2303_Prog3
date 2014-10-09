CFLAGS = -c
CC = g++ -Wall

all: process.o queue.o main.o fcfs.o rr.o util.o
	$(CC) -o prog3 main.o process.o queue.o rr.o fcfs.o  util.o -lm

debug: CC += -DDEBUG -g
debug: all

main.o: main.cpp queue.h process.h fcfs.h util.h rr.h
	$(CC) $(CFLAGS) main.cpp

rr.o: rr.h rr.cpp queue.h process.h util.h
	$(CC) $(CFLAGS) rr.cpp

fcfs.o: fcfs.h fcfs.cpp queue.h process.h util.h
	$(CC) $(CFLAGS) fcfs.cpp

queue.o: queue.cpp queue.h process.h
	$(CC) $(CFLAGS) queue.cpp -lm

process.o: process.cpp process.h
	$(CC) $(CFLAGS) process.cpp

util.o: util.cpp util.h queue.h
	$(CC) $(CFLAGS) util.cpp

clean:
	rm -rf prog3 *.o 2> /dev/null
