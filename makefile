CFLAGS = -c
#CFLAGS = -
CC = g++ -Wall

OBJS = main.o fcfs.o rr.o queue.o process.o util.o 
#OBJS = util.o process.o queue.o rr.o fcfs.o main.o

all: process.h main.o rr.o fcfs.o queue.o process.o util.o 
	$(CC) -o prog3 -lm $(OBJS)  

debug: CC += -DDEBUG -g
debug: all

main.o: queue.h process.h fcfs.h util.h rr.h main.cpp 
	$(CC) $(CFLAGS) main.cpp

rr.o: rr.h process.h queue.h util.h rr.cpp
	$(CC) $(CFLAGS) rr.cpp

fcfs.o: fcfs.h queue.h process.h util.h fcfs.cpp  process.o util.o queue.o
	$(CC) $(CFLAGS) fcfs.cpp

queue.o: queue.h process.h queue.cpp process.o
	$(CC) $(CFLAGS) queue.cpp -lm

process.o: process.h process.cpp
	$(CC) $(CFLAGS) process.cpp

util.o: queue.h util.h util.cpp 
	$(CC) $(CFLAGS) util.cpp

clean:
	rm -rf prog3 *.o 2> /dev/null



