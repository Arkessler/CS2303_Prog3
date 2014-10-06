#ifndef FCFS_H_
#define FCFS_H_

#include "queue.h"

typedef struct {
  int curTime;
  queue *schedQueue;
  queue *finishedProcesses;
} fcfs;

// Initializes an FCFS scheduling simulator with the given
// list of processes to run.
fcfs* initFCFS(queue *schedQueue);

// Runs a FCFS simulation until completion, printing output
// to the console
void runFCFS(fcfs *toRun);

// Destroys a given FCFS scheduling simulator, freeing all
// remaining resources
void destoryFCFS(fcfs *toDestroy);

#endif
