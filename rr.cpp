#ifndef RR_CPP_
#define RR_CPP_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#include "rr.h"
#include "process.h"
#include "queue.h"
#include "util.h"

// Forward Declarations
void processArrive(rr *toRun);

// Initializes a RR scheduling simulator with the given
// list of processes to run
rr::rr(queue *schedQueueN, int sliceN) {
  curTime = 0;
  schedQueue = schedQueueN;
  runningQueue = new queue();
  finishedProcesses = new queue();
  slice = sliceN;
}

// Runs a RR simulation until completion, printing output
// to the console
void rr::runRR(){
  // Controls the loop
  int running = 1;
  // Info printf
  cout << "Starting RR scheduling simulator\n";

  while (running) {
    
    //if(DEBUG1) cout<< get_schedQueue()<< endl;

    // Enqueue new processes
    processArrive();

    if(DEBUG1) cout<<"Processes Enqueued"<<get_runningQueue()<<endl;


    // If there are tasks on the queue, run them for the slice
    if (get_runningQueue()->get_front()) {
      // Get the next process from the queue
      process *next = new process();
      process **nextPtr = &next;
      if(DEBUG1) cout<<"before set running queue"<<endl<<get_runningQueue()->get_front()<<endl;

      set_runningQueue(get_runningQueue()->pop(nextPtr));
      if(DEBUG1) cout<< (*nextPtr)->get_pid()<<endl;
      next = *nextPtr;


      if(DEBUG1) cout<<"after set running queue" <<endl;

      // Increment the clock and decrement the remaining time. If time is > 0, then requeue the process
      // If not, then remove the process, add it to the finished queue, and increment its waitTime
      
      if(DEBUG1) cout << next <<endl;

      if ((next->get_remainTime() - get_slice()) > 0) {
	if(DEBUG1) cout<<"Process is not complete " << next->get_pid() << endl;

	next->set_remainTime( next->get_remainTime() - get_slice());
	if(DEBUG1) cout<<"remain time after" << get_slice() << "ms update " << next->get_remainTime();

	set_curTime( get_curTime() + get_slice());
	set_runningQueue(get_runningQueue()->enqueue(next));
	cout << "Process " << next->get_pid() << " has run for " << get_slice() * 100  << " ms, "<< next->get_remainTime() * 100  << " ms remaining\n";
	continue;
      } else {

	if(DEBUG1) cout<< "Process completed "<<  next->get_pid() <<endl;

	set_curTime( get_curTime() +  next->get_remainTime());
	next->set_remainTime(0);
	next->set_waitTime(get_curTime() - (next->get_aTime() + next->get_cpuTime()));

	if(DEBUG1) cout<< next->get_pid() <<endl;
	set_finishedProcesses(get_finishedProcesses()->enqueue(next));
	cout << "Process " <<next->get_pid() <<" finished at " << get_curTime() * 100  << " ms\n";
	continue;
      }
    } else {
      DEBUG_PRINT("No process in the queue");

      // If there are processes left, advance to that process's arrival time. Otherwise, we're done
      if (get_schedQueue()->get_front()) {
	process *next;
	get_schedQueue()->peak(&next);
	set_curTime(next->get_aTime());
	//DEBUG_PRINT("Advanced clock to %d ms", toRun->curTime * 100);
	continue; 
      } else {
	//DEBUG_PRINT("Finished RR scheduling at %d ms, now calculating stats", toRun->curTime * 100);
	running = 0;
	break;
      }
    }
  }

  // Output a couple of new lines to the output for formatting
  cout<< "\n\n--------SIMULATION COMPLETE---------\n";
  
  processesStats(finishedProcesses);

  // Flush and close the file
  cout<< "Ended RR simulation\n";
}

// Destroys a given RR scheduling simulator, freeing all
// remaining resources
rr::~rr() {
  // Free the scheduling queue
  delete schedQueue;
  delete runningQueue;
  delete finishedProcesses;
}

// Removes all arriving processes for the current time
// and adds them to the scheduling queue
void rr::processArrive() {

  int moreProcesses = get_schedQueue() ? 1 : 0;
  while (moreProcesses) {
    process *proc = NULL;
    get_schedQueue()->peak(&proc);
    if (proc && get_curTime() >= proc->get_aTime()) {
      if(DEBUG1) cout<< "Process has arrived at the scheduling queue"<<endl;

      set_schedQueue(get_schedQueue()->pop(&proc));

      //if(DEBUG1) cout<< get_schedQueue()->get_front() <<endl;
      set_runningQueue(get_runningQueue()->enqueue(proc));
    } else {
      moreProcesses = 0;
    }
  }
}


int rr::get_curTime(){
  return curTime;
}

int rr::get_slice(){
  return slice;
}

queue *rr::get_schedQueue(){
  return schedQueue;
}

queue *rr::get_runningQueue(){
  return runningQueue;
}

queue *rr::get_finishedProcesses(){
  return finishedProcesses;
}

rr *rr::set_curTime(int time){
  curTime = time;
  return this;
}

rr *rr::set_slice(int sliceTime){
  slice = sliceTime;
  return this;
}

rr *rr::set_schedQueue(queue *newQ){
  schedQueue = newQ;
  return this;
}

rr *rr::set_runningQueue(queue *newQ){
  runningQueue = newQ;
  return this;
}

rr *rr::set_finishedProcesses(queue *newQ){
  finishedProcesses = newQ;
  return this;
}

#endif
