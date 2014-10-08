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
float process::getDifference(float avg) {
  return get_waitTime() - avg;
}

// Creates a clone of the given process. This is malloced,
// be sure to free it later
process* process::cloneProc() {
  process *newProc = new process();
  newProc->set_pid(get_pid());
  newProc->set_aTime(get_aTime());
  newProc->set_cpuTime(get_cpuTime());
  newProc->set_waitTime(get_waitTime());
  newProc->set_remainTime(get_remainTime());
  return newProc;
}

