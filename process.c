#include <stdlib.h>
#include <stdio.h>
#include "process.h"

// Mallocs space for a new process
process::process(){
  pid = 0;
  aTime = 0;
  cpuTime = 0;
  waitTime = 0;
  remainTime = 0;
}

process::process(int new_pid, int new_aTime, int new_cpuTime) {
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
process* process::cloneProc() {
  process *newProc = new process();
  new->set_pid(pid);
  new->set_aTime(aTime);
  new->set_cpuTime(cpuTime);
  new->set_waitTime(waitTime);
  new->set_remainTime(remainTime);
  return new;
}


int get_pid(){
  return pid;
}

int get_aTime(){
  return aTime;
}

int get_cpuTime(){
  return cpuTime;
}
int get_waitTime(){
  return waitTime;
}
int get_remainTime(){
  return remainTime;
}

void set_pid(int diff){
  pid = diff;
}
void set_aTime(int diff){
  aTime = diff;
}
void set_cpuTime(int diff){
  cpuTime = diff;
}
void set_waitTime(int diff){
  waitTime = diff;
}
void set_remainTime(int diff){
  remainTime = diff;
}
