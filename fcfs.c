#include <stdlib.h>
#include <stdio.h>
#include "fcfs.h"
#include "util.h"

// Forward Declarations
void checkTimings(fcfs *toRun, process *proc);

// Initializes an FCFS scheduling simulator with the given
// list of processes to run.
fcfs::fcfs(queue *newSchedQueue){
  set_curTime(0);
  set_schedQueue(newSchedQueue);
  set_finishedProcesses(NULL);
}


// Runs a FCFS Simulation until completion, printing output
// to the console
void fcfs::runFCFS() {
  // Will control whether to continue the simulation
  int running = 1;
  // The file for simulation output
  FILE *file = fopen("fcfs_stats.txt", "w");

  // Info printf
  printf("Starting FCFS scheduling simulation\n");

  while (running) {
    // See if the next process is null. If so, set running to 0 and break
    if (!getSchedQueue()) {
      running = 0;
      break;
    }

    // Pop the next process off of the scheduling queue 
    process *nextProc;
    setSchedQueue(pop(toRun->schedQueue, &nextProc));

    ///////From here gonna update
    DEBUG_PRINT("FCFS: Process %d started", nextProc->pid);
      
    // Check the timings so that the simulation time and wait times are correct
    checkTimings(toRun, nextProc);

    // Output starting stats to the file
    fprintf(file, "Process %d started at %d ms, waited for %d.\n", nextProc->pid, toRun->curTime * 100, nextProc->waitTime * 100);

    // Increment the clock, then add the process to the finished queue
    toRun->curTime += nextProc->cpuTime;
    toRun->finishedProcesses = enqueue(toRun->finishedProcesses, nextProc);

    // Print the final leaving time
    fprintf(file, "Process %d finished at %d ms.\n", nextProc->pid, toRun->curTime * 100);
    fflush(file);
  }

  DEBUG_PRINT("Ended main fcfs loop, starting averaging");

  // Output a couple of new lines to the output for formatting
  fprintf(file, "\n\n--------SIMULATION COMPLETE---------\n");

  processesStats(file, toRun->finishedProcesses);

  // Flush and close the file
  fflush(file);
  fclose(file);

  printf("Ended FCFS simulation\n");
}

// Destroys a given FCFS scheduling simulator, freeing all
// remaining resources.
void destoryFCFS(fcfs *toDestroy) {
  // Destory any remaining schedule queue elements
  freeQueue(toDestroy->schedQueue);
 
  // Destory the finished processes
  freeQueue(toDestroy->finishedProcesses);

  // Finally, free the fcfs struct itself
  free(toDestroy);
}

// Checks the timings of the incoming process.
// If there is still time before the process arrives,
// increment the clock to that point.
// If the process is past due, increment the wait
// time of the process appropriately
void checkTimings(fcfs *toRun, process *proc) {
  if (toRun->curTime < proc->aTime) toRun->curTime = proc->aTime;
  else proc->waitTime = toRun->curTime - proc->aTime;
}


int fcfs::get_curTime(){ // converted by Max.
  return curTime;
}

void fcfs::set_curTime(int time){
  curTime = time;
}

queue *get_schedQueue(){
  return schedQueue;
}

void set_schedQueue(queue *newQueue){
  schedQueue = newQueue;
}

queue *get_finishedProcesses(){
  return finishedProcesses;
}

void set_finishedProcesses(queue *newQueue){
  finishedProcesses = newQueue;
}
