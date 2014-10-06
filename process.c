#include <stdlib.h>
#include <stdio.h>
#include "process.h"

// Mallocs space for a new process
process* createProc(int pid, int aTime, int cpuTime) {
  process *new = malloc(sizeof(process));
  new->pid = pid;
  new->aTime = aTime;
  new->cpuTime = cpuTime;
  new->waitTime = 0;
  new->remainTime = cpuTime;
  return new;
}

// Compares two processes, returning 0 if the old
// process comes before the new process, 1 otherwise
int procLessThan(process *new , process *old) {
  return new->aTime <= old->aTime;
}

// Gets the difference between this wait time and the average wait time
float getDifference(process *proc, float avg) {
  return proc->waitTime - avg;
}

// Creates a clone of the given process. This is malloced,
// be sure to free it later
process* cloneProc(process *proc) {
  process *new = malloc(sizeof(proc));
  new->pid = proc->pid;
  new->aTime = proc->aTime;
  new->cpuTime = proc->cpuTime;
  new->waitTime = proc->waitTime;
  new->remainTime = proc->remainTime;
  return new;
}
