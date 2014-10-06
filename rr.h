#ifndef RR_H_
#define RR_H_

#include "queue.h"

typedef struct {
  int curTime;
  int slice;
  queue *schedQueue;
  queue *runningQueue;
  queue *finishedProcesses;
} rr;

// Initializes a RR scheduling simulator with the given
// list of processes to run
rr* initRR(queue *schedQueue, int slice);

// Runs a RR simulation until completion, printing output
// to the console
void runRR(rr *toRun);

// Destroys a given RR scheduling simulator, freeing all
// remaining resources
void destroyRR(rr *toDestroy);

#endif
