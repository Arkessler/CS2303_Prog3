#ifndef QUEUE_CPP_
#define QUEUE_CPP_

#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "util.h"
#include "process.h"

// Pops the next element off of the queue
// This returns a pointer to the next head element,
// and stores a pointer to the process in the given
// out location. This frees the given queue element,
// so do not attempt to use it again. To just get the
// process element, use the peak method

queue* queue::pop(process **out) {
  queueNode* next = get_front()->get_next();
  peak(out);
  set_front(next);
  delete get_front();
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
  if (get_front() == NULL) {
    queueNode *newQ = new queueNode(proc);
    return new queue(newQ);
  } else {
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
  if (get_front()==NULL){
    queueNode *newQ = new queueNode(proc);
    return new queue(newQ);
  }
  else if(proc->procLessThan(get_front()->get_proc())){
    queueNode *newQ = new queueNode(proc);
    return new queue(newQ);
  }
  else{
    get_front()->set_next(get_front()->get_next()->sortedInsert(proc));
    return new queue(get_front());
  }
}

queueNode* queueNode::sortedInsert(process *proc) {
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
     newQ->set_next(get_next()->cloneQueue());
     return newQ;
   }
     else{
       return NULL;
     }
 }

// Frees the entire queue, and the process elements contained within
queue::~queue() {
  if (get_front()) {
    delete get_front()->get_next();
    if (get_front()->get_proc()) delete get_front()->get_proc();
    delete get_front();
  }
}

 queueNode::~queueNode(){
   if(this){
     delete get_next();
     if(get_proc())
       delete get_proc();
   }
}

// Conveniece helper for creating new queue elements and 
// giving them a process
 queueNode::queueNode(process *proc) {
  next = NULL;
  proc = proc;
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
  return front;
}

void queue::set_front(queueNode *newQ){
  front = newQ;
}



#endif
