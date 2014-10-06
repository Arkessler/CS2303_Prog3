#include <stdlib.h>
#include <stdio.h>
#include "rr.h"
#include "util.h"

// Forward Declarations
void processArrive(rr *toRun);

// Initializes a RR scheduling simulator with the given
// list of processes to run
rr* initRR(queue *schedQueue, int slice) {
  rr *new = malloc(sizeof(rr));
  new->curTime = 0;
  new->schedQueue = schedQueue;
  new->runningQueue = NULL;
  new->finishedProcesses = NULL;
  new->slice = slice;
  return new;
}

// Runs a RR simulation until completion, printing output
// to the console
void runRR(rr *toRun) {
  // Controls the loop
  int running = 1;
  // The file for simulation output
  FILE *file = fopen("rr_stats.txt", "w");

  // Info printf
  printf("Starting RR scheduling simulator\n");

  while (running) {
    
    DEBUG_PRINT("Enqueueing new processes");

    // Enqueue new processes
    processArrive(toRun);

    DEBUG_PRINT("Processes Enqueued");

    // If there are tasks on the queue, run them for the slice
    if (toRun->runningQueue) {
      // Get the next process from the queue
      process *next = NULL;
      toRun->runningQueue = pop(toRun->runningQueue, &next);

      // Increment the clock and decrement the remaining time. If time is > 0, then requeue the process
      // If not, then remove the process, add it to the finished queue, and increment its waitTime
      if ((next->remainTime - toRun->slice) > 0) {
	DEBUG_PRINT("Process %d is not complete", next->pid);

	next->remainTime -= toRun->slice;
	toRun->curTime += toRun->slice;
	toRun->runningQueue = enqueue(toRun->runningQueue, next);
	fprintf(file, "Process %d has run for %d ms, %d ms remaining\n", next->pid, toRun->slice * 100, next->remainTime * 100);
	continue;
      } else {
	DEBUG_PRINT("Process %d completed", next->pid);

	toRun->curTime += next->remainTime;
	next->remainTime = 0;
	next->waitTime = toRun->curTime - (next->aTime + next->cpuTime);
	toRun->finishedProcesses = enqueue(toRun->finishedProcesses, next);
	fprintf(file, "Process %d finished at %d ms\n", next->pid, toRun->curTime * 100);
	continue;
      }
    } else {
      DEBUG_PRINT("No process in the queue");

      // If there are processes left, advance to that process's arrival time. Otherwise, we're done
      if (toRun->schedQueue) {
	process *next;
	peak(toRun->schedQueue, &next);
	toRun->curTime = next->aTime;
	DEBUG_PRINT("Advanced clock to %d ms", toRun->curTime * 100);
	continue; 
      } else {
	DEBUG_PRINT("Finished RR scheduling at %d ms, now calculating stats", toRun->curTime * 100);
	running = 0;
	break;
      }
    }
  }

  // Output a couple of new lines to the output for formatting
  fprintf(file, "\n\n--------SIMULATION COMPLETE---------\n");
  
  processesStats(file, toRun->finishedProcesses);

  // Flush and close the file
  fflush(file);
  fclose(file);

  printf("Ended RR simulation\n");
}

// Destroys a given RR scheduling simulator, freeing all
// remaining resources
void destroyRR(rr *toDestroy) {
  // Free the scheduling queue
  freeQueue(toDestroy->schedQueue);
  
  // Free the running queue
  freeQueue(toDestroy->runningQueue);

  // Free the finished processes queue
  freeQueue(toDestroy->finishedProcesses);

  // Free the RR scheduling struct itself
  free(toDestroy);
}

// Removes all arriving processes for the current time
// and adds them to the scheduling queue
void processArrive(rr *toRun) {
  int moreProcesses = toRun->schedQueue ? 1 : 0;
  while (moreProcesses) {
    process *proc = NULL;
    peak(toRun->schedQueue, &proc);
    if (proc && toRun->curTime >= proc->aTime) {
      DEBUG_PRINT("Process %d has arrived at the scheduling queue", proc->pid);

      toRun->schedQueue = pop(toRun->schedQueue, &proc);
      toRun->runningQueue = enqueue(toRun->runningQueue, proc);
    } else {
      moreProcesses = 0;
    }
  }
}
