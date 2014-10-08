#include <stdlib.h>
#include <iostream>
using namespace std;
#include "fcfs.h"
#include "queue.h"
#include "process.h"
#include "util.h"

// Forward Declarations
//void checkTimings(fcfs *toRun, process *proc);

// Initializes an FCFS scheduling simulator with the given
// list of processes to run.
fcfs::fcfs(queue *newSchedQueue){
  set_curTime(0);
  set_schedQueue(newSchedQueue);
  set_finishedProcesses(NULL);
}


// Runs a FCFS Simulation until completion, printing output
// to the console
void fcfs::run_fcfs() {
  // Will control whether to continue the simulation
  int running = 1;
  // Info printf
  cout<< "Starting FCFS scheduling simulation\n";

  while (running) {
    // See if the next process is null. If so, set running to 0 and break
    if (!get_schedQueue()) {
      running = 0;
      break;
    }
  
    // Pop the next process off of the scheduling queue 
    process *nextProc;
    set_schedQueue(get_schedQueue()->pop(&nextProc));
  
    ///////From here gonna update
    DEBUG_PRINT("FCFS: Process %d started", nextProc->get_pid());
      
    // Check the timings so that the simulation time and wait times are correct
    checkTimings(nextProc);
  
    // Output starting stats to the file
    cout << "Process "<< nextProc->get_pid() << " started at " << get_curTime() * 100  << " ms, waited for " <<nextProc->get_waitTime() * 100 << ".\n";
  
    // Increment the clock, then add the process to the finished queue
    set_curTime(get_curTime() + nextProc->get_cpuTime());
    set_finishedProcesses(get_finishedProcesses()->enqueue(nextProc));
  
    // Print the final leaving time
    cout << "Process " << nextProc->get_pid() << " finished at "<< get_curTime() * 100 <<" ms.\n";
  }

  DEBUG_PRINT("Ended main fcfs loop, starting averaging");

  // Output a couple of new lines to the output for formatting
  cout<<"\n\n--------SIMULATION COMPLETE---------\n";

  processesStats(finishedProcesses);

  // Flush and close the file
  cout<<"Ended FCFS simulation\n";
}

// Destroys a given FCFS scheduling simulator, freeing all
// remaining resources.
fcfs::~fcfs() {
  // Destory any remaining schedule queue elements
  delete schedQueue;
  delete finishedProcesses;
  // Finally, free the fcfs struct itself
  free(this);
}

// Checks the timings of the incoming process.
// If there is still time before the process arrives,
// increment the clock to that point.
// If the process is past due, increment the wait
// time of the process appropriately
void fcfs::checkTimings(process *proc) {
  if (get_curTime() < proc->get_aTime()) set_curTime(proc->get_aTime());
  else proc->set_waitTime(get_curTime() - proc->get_aTime());
}


int fcfs::get_curTime(){ // converted by Max.
  return curTime;
}

void fcfs::set_curTime(int time){
  curTime = time;
}

queue *fcfs::get_schedQueue(){
  return schedQueue;
}

void fcfs::set_schedQueue(queue *newQueue){
  schedQueue = newQueue;
}

queue *fcfs::get_finishedProcesses(){
  return finishedProcesses;
}

void fcfs::set_finishedProcesses(queue *newQueue){
  finishedProcesses = newQueue;
}
