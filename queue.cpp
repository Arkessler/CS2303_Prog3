#ifndef QUEUE_CPP_
#define QUEUE_CPP_

#include <iostream>
using std::endl;
using std::cout;
using std::flush;
#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "util.h"
#include "process.h"
#define DEBUG_DEL 1
// Pops the next element off of the queue
// This returns a pointer to the next head element,
// and stores a pointer to the process in the given
// out location. This frees the given queue element,
// so do not attempt to use it again. To just get the
// process element, use the peak method

queue* queue::pop(process **out) {
  if(DEBUG1) cout<< "in pop" <<endl<<get_front()<<endl <<flush;
  queueNode* next = get_front()->get_next();
  if(DEBUG1) cout<< "before peak" <<endl<<flush;
  peak(out);
  if(DEBUG1) cout << "Peaked in pop"<<endl<<flush;
  delete get_front();
  //set_front(next);
  if(DEBUG1) cout <<"after delete" <<endl;
  queue *nextQ = new queue(next);
  return nextQ;
}

// Peaks at the next element of the queue, and stores
// a pointer to the element at the given location.
void queue::peak(process **out) {
  if (get_front()) *out = (get_front())->get_proc();
}

// Enqueues an element in a given list, mallocing a new
// queueNode structure for the element. If null is passed 
// in for head, a new queue will be created
queue* queue::enqueue(process *proc) {
  if(DEBUG1) cout << "in enqueue"<< endl;

  //if(DEBUG1) cout <<"can use getfront()"<<endl<<(get_front())<<endl<<flush;

  if (get_front() == NULL) {
    if(DEBUG1) cout <<"no front" << endl<<flush;

    queueNode *newQ = new queueNode(proc);
    return new queue(newQ);
  } else {
    if(DEBUG1) cout<< "has front"<<endl<<flush;
    get_front()->set_next(get_front()->get_next()->enqueue(proc));
    return new queue(get_front());
  }
}

queueNode* queueNode::enqueue(process *proc){
  if(!this){
    return new queueNode(proc);
  }
  else{
    set_next(get_next()->enqueue(proc));
    return this;
  }
}


// Inserts the given proces into the queue, sorted by
// cpu time. Returns a pointer to the new head of the queue
queue* queue::sortedInsert(process *proc){
  if(DEBUG) {
    cout<< "in sorted Insert!"<< endl << flush;
  }
  if(DEBUG) cout<< "passed get_front assignment : "<<(get_front() == NULL) << endl <<flush;

  if (get_front()==NULL){
    if(DEBUG) cout<<"front is Null"<<endl<<flush;
    queueNode *newQ = new queueNode(proc);
    return new queue(newQ);
  }
  else if(proc->procLessThan(get_front()->get_proc())){
    if(DEBUG) {
      cout<<"new process less than front"<<endl << flush;
      fflush(stdout);
    }
    queueNode *newQ = new queueNode(proc);
    return new queue(newQ);
  }
  else{
    if(DEBUG) {
      cout <<"new process is greater than front"<<endl <<flush;
    }
    get_front()->set_next(get_front()->get_next()->sortedInsert(proc));
    return new queue(get_front());
  }
}



queueNode* sortedInsert(queueNode *head, process *proc_n){

  if(head) head->get_proc();
  if(DEBUG) cout<<"in new sort, head is null "<<(head == NULL)<<endl;//<<"process aTime is "<< head->get_proc()->get_aTime() <<endl<<flush; //   " proc is less than " <<(proc->procLessThan(head->get_proc())) <<endl<<flush;
  if(head == NULL){
    if(DEBUG) cout<<"no front" <<endl<<flush;
    queueNode *newQ = new queueNode(proc_n);
    if(DEBUG) cout << newQ->get_proc() <<endl; 
    return newQ;
  }
  else if(proc_n->procLessThan(head->get_proc())){
    if(DEBUG) cout<<"process is less than the front process" <<endl<<flush;
    queueNode *newQ = new queueNode(proc_n);
    newQ->set_next(head);
    return newQ;
  }
  else{
    if(DEBUG) cout<<"process is greater than front process"<<endl<<flush;
    head->set_next(sortedInsert(head->get_next(), proc_n));
    return head;
  }

}



queueNode* queueNode::sortedInsert(process *proc) {
  if(DEBUG) cout << "is this (ptr) null?  "<< (this == NULL) <<endl <<flush;
  if (this == NULL) {
    // Empty case, return a new element
    queueNode *newQ = new queueNode(proc);
    return newQ;
  } else if (proc->procLessThan(get_proc())) {
    queueNode *newQ = new queueNode(proc);
    newQ->set_next(this);
    return newQ;
  } else {
    // New process arrives after, insert after
    set_next(get_next()->sortedInsert(proc));
    return this;
  }
}

// Gets the average wait times of all the processes in the list
float queue::getQueueAverage(){
  queueNode *cur;
  int total = 0, count = 0;

  // Loop until we reach the tail of the list
  for (cur = get_front(); cur; cur = cur->get_next()) {
    total += cur->get_proc()->get_waitTime();
    count++;
  }

  return ((float) total)/count;
}

// Calculates the variance of the queue, given the average wait time
// The formula for variance is sum((waitTime_i - mean)^2)/n
float queue::getQueueVariance(float avg) {
  // Accumulators for the total and count
  float total = 0;
  int count = 0;
  queueNode *cur;

  // Loop until we reach the tail of the list
  for (cur = get_front(); cur; cur = cur->get_next()) {
    float diff = get_front()->get_proc()->getDifference(avg);
    total += pow(diff, 2);
    count++;
  }

  return total/count;
}

// Calculates the average and variance of all given processes. The forumla
// for response time is finish time - arrival time. The formula
// for variance is EX^2 - (EX)^2, where X is the average response
// time 
void queue::processEX(float *avg, float *var) {
  float x, x2;
  int count;
  queueNode *cur;

  for (cur = get_front(); cur; cur = cur->get_next()) {
    int repTime = cur->get_proc()->get_waitTime() + cur->get_proc()->get_cpuTime();
    x += repTime;
    x2 += pow(repTime, 2);
    count++;
  }

  (*avg) = x / count;
  (*var) = (x2 / count) - pow((*avg), 2);
}

// Gets the minimum wait time of the queue
int queue::getQueueMin() {
  // If head is null, just return 0
  if (!get_front()) {
    return 0;
  }
  
  int min = get_front()->get_proc()->get_waitTime() + get_front()->get_proc()->get_cpuTime();
  queueNode *cur;

  for (cur = get_front(); cur; cur = cur->get_next()) {
    min = min < cur->get_proc()->get_waitTime() + cur->get_proc()->get_cpuTime() ? min : cur->get_proc()->get_waitTime() + cur->get_proc()->get_cpuTime();
  }

  return min;
}

// Gets the maximum wait time of the queue
int queue::getQueueMax() {
  // If head is null, just return 0
  if (!get_front()) {
    return 0;
  }
  
  int max = get_front()->get_proc()->get_waitTime() + get_front()->get_proc()->get_cpuTime();
  queueNode *cur;

  for (cur = get_front(); cur; cur = cur->get_next()) {
    max = max > cur->get_proc()->get_waitTime() + cur->get_proc()->get_cpuTime() ? max : cur->get_proc()->get_waitTime() + cur->get_proc()->get_cpuTime();
  }

  return max;
}

// Clones the given queue, and the process elements within.
// These are malloced, be sure to free them later
queue* queue::cloneQueue() {
  if (get_front()) {
    if(DEBUG1) cout << "run clone" <<endl;
    queue* newQ = new queue(new queueNode(get_front()->get_proc()->cloneProc()));
    newQ->get_front()->set_next(get_front()->get_next()->cloneQueue());
    return newQ;
  } else {
    return NULL;
  }
}

 queueNode* queueNode::cloneQueue(){
   if(this){

     queueNode *newQ = new queueNode(get_proc()->cloneProc());
     if(DEBUG1) cout <<newQ->get_proc()->get_pid() <<endl;
     newQ->set_next(get_next()->cloneQueue());
     return newQ;
   }
     else{
       return NULL;
     }
 }

// Frees the entire queue, and the process elements contained within
queue::~queue() {
  if(DEBUG_DEL) cout<< " in delete for queue" <<endl;
  if (get_front()) {
    delete get_front()->get_next();
    if(DEBUG_DEL) cout<<" deleted next" <<endl;
  }
}

 queueNode::~queueNode(){
   if(DEBUG_DEL) cout << "in delete for queueNode"<<endl;
   // if(this){
   if(0){
   if(get_proc())
       delete get_proc();
   }
   //if(DEBUG_DEL) cout<< " deleted proc"<<endl;
 }

// Conveniece helper for creating new queue elements and 
// giving them a process
 queueNode::queueNode(process *proc) {
   set_next(NULL);
  set_proc(proc);
}

 queue::queue(queueNode *newQ){
   front = newQ;
}


queueNode *queueNode::get_next(){
  return next;
}

void queueNode::set_next(queueNode *newQ){
  next = newQ;
}

process *queueNode::get_proc(){
  return proc;
}

void queueNode::set_proc(process *newP){
  proc = newP;
}

queueNode *queue::get_front(){
  if(front == NULL)
    return NULL;
  else
    return front;
}

void queue::set_front(queueNode *newQ){
  front = newQ;
}

queue::queue(){
  front = NULL;
}

#endif
