#ifndef PROCESS_CPP_
#define PROCESS_CPP_

//#include <stdlib.h>
//#include <stdio.h>
#include "process.h"
#include "util.h"
#include <iostream>
using std::cout;
using std::endl;
using std::flush;

// Mallocs space for a new process
process::process(int new_pid, int new_aTime, int new_cpuTime, int new_io) {;
  pid = new_pid;
  aTime = new_aTime;
  cpuTime = new_cpuTime;
  waitTime = 0;
  ioTime = new_io;
  remainTime = new_cpuTime;
}

process::process(){
  pid = -1;
  aTime = -1;
  cpuTime = -1;
  waitTime = -1;
  remainTime = -1;
}

// Compares two processes, returning 0 if the old
// process comes before the new process, 1 otherwise
int process::procLessThan(process *old) {
  if(DEBUG) {
    cout<< "in procCompare, aTime "<< get_aTime() <<endl<<flush;
    cout<< " old aTime "<<old->get_aTime()<<endl<<flush;
  }
  return get_aTime() <= old->get_aTime();
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

int process::get_pid(){
  return pid;
}

int process::get_ioTime(){
  return ioTime;
}

void process::set_ioTime(int newTime){
  ioTime = newTime;
}

int process::get_aTime(){
  return aTime;
}

int process::get_cpuTime(){
  return cpuTime;
}

int process::get_waitTime(){
  return waitTime;
}

int process::get_remainTime(){
  return remainTime;
}

void process::set_pid(int newPid){
  pid = newPid;
}

void process::set_aTime(int newA){
  aTime = newA;
}

void process::set_cpuTime(int newC){
  cpuTime = newC;
}

void process::set_waitTime(int newW){
  waitTime = newW;
}

void process::set_remainTime(int newR){
  remainTime = newR;
}

process::~process(){
  if(DEBUG1) cout<< "in delete for process" <<endl;
}
#endif
