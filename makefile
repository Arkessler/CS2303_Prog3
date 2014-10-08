#all: process.o queue.o main.o fcfs.o rr.o util.o
#	g++ -o prog3 *.o -lm
#	g++ -o prog3 main.o process.o rr.o fcfs.o queue.o util.o -lm
#	g++ -o prog3 util.o process.o queue.o fcfs.o rr.o main.o -lm

#debug: CC += -DDEBUG -g
#debug: all

all: prog3

prog3: main.o
	g++ -o prog3 main.o

main.o: main.cpp rr.o fcfs.o queue.o process.o util.o
	g++  -c -g -Wall -o main.o main.cpp

rr.o: rr.h rr.cpp queue.o process.o process.h util.h
	g++ -c -g -Wall  -o rr.o rr.cpp

fcfs.o: fcfs.h fcfs.cpp queue.o process.o queue.h process.h util.h
	g++ -c -g -Wall -o fcfs.o fcfs.cpp

queue.o: queue.cpp process.o queue.h process.h
	g++ -c -g -Wall -o queue.o queue.cpp -lm

process.o: process.cpp process.h
	g++ -c -g  -Wall -o process.o process.cpp

util.o: util.cpp util.h queue.h
	g++ -c -g -Wall -o util.o util.cpp

clean:
	rm -rf prog3 *.o 2> /dev/null
