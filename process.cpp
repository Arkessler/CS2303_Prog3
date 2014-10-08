#include <stdlib.h>
#include <stdio.h>
#include "process.h"

// Mallocs space for a new process
process::process(int new_pid, int new_aTime, int new_cpuTime) {;
  pid = new_pid;
  aTime = new_aTime;
  cpuTime = new_cpuTime;
  waitTime = 0;
  remainTime = new_cpuTime;
}

// Compares two processes, returning 0 if the old
// process comes before the new process, 1 otherwise
int process::procLessThan(process *old) {
  return aTime <= old->get_aTime();
}

// Gets the difference between this wait time and the average wait time
float getDifference(float avg) {
  return waitTime - avg;
}

// Creates a clone of the given process. This is malloced,
// be sure to free it later
process* process::cloneProc(process *proc) {
  process *newProc = new process();
  new->pid = proc->pid;
  new->aTime = proc->aTime;
  new->cpuTime = proc->cpuTime;
  new->waitTime = proc->waitTime;
  new->remainTime = proc->remainTime;
  return new;
}
