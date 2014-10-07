#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "util.h"
///////
///////DON'T FORGET TO COME BACK WHEN PROCESSES HAVE BEEN FIXED


// Forward declaration of createQueueElement
queue* createQueueElement(process *proc);

// Pops the next element off of the queue
// This returns a pointer to the next head element,
// and stores a pointer to the process in the given
// out location. This frees the given queue element,
// so do not attempt to use it again. To just get the
// process element, use the peak method

//queue functions.

queueNode::queueNode(process *newProcess){
  set_next(NULL);
  set_proc(newProcess);
};

queueNode *queueNode::get_next(){
  return next;
}

process *queueNode:;get_proc(){
  return proc;
}

void queueNode::set_next(queueNode *newNext){
  next = newNext;
}

void queueNode::set_proc(process *newProc){
  proc = newProc;
}

queueNode::~queueNode(){
  delete proc;
  delete next;
}



void queue::pop(process **out) {
  next = get_front()->next;
  peak(out);
  ~queue();
}

// Peaks at the next element of the queue, and stores
// a pointer to the element at the given location.
void queue::peak(process **out) {
  if (get_front()) *out = get_proc();
}

// Enqueues an element in a given list, mallocing a new
// queue structure for the element. If null is passed 
// in for head, a new queue will be created
queue* queue::enqueue(process *proc) {
  if (front == NULL) {
    return new queue(proc);
  } else {
    (front->next)->enqueue(proc);
    return front;
  }
}

// Inserts the given proces into the queue, sorted by
// cpu time. Returns a pointer to the new head of the queue
queue* queue::sortedInsert(process *proc) {
  if (front == NULL) {
    // Empty case, return a new element
    return new queue(proc);
  } else if (procLessThan(proc, front->proc)) {
    // New process arrives before, insert before
    queue *newQ = new queue(proc);
    newQ->next = front;
    return newQ;
  } else {
    // New process arrives after, insert after
    front->next->sortedInsert(proc);
    return front;
  }
}

// Gets the average wait times of all the processes in the list
float queue::getQueueAverage(){
  queue *cur;
  int total = 0, count = 0;

  // Loop until we reach the tail of the list
  for (cur = front; cur; cur = cur->get_next()) {
    total += (cur->get_proc())->waitTime;
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
  for (cur = front; cur; cur = cur->getNext()) {
    float diff = (front->get_proc())->getDifference(avg);
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
  queue *cur;

  for (cur = front; cur; cur = cur->get_next()) {
    int repTime = (cur->get_proc())->get_waitTime() + cur->get_proc()->get_cpuTime();
    x += repTime;
    x2 += pow(repTime, 2);
    count++;
  }

  (*avg) = x / count;
  (*var) = (x2 / count) - pow((*avg), 2);
}

// Gets the minimum wait time of the queue
int queue::getQueueMin(*head) {
  // If head is null, just return 0
  if (!front) {
    return 0;
  }
  
  int min = head->proc->get_waitTime() + head->proc->get_cpuTime();
  queue *cur;

  for (cur = front; cur; cur = cur->next) {
    min = min < cur->proc->get_waitTime() + cur->proc->get_cpuTime() ? min : cur->proc->get_waitTime() + cur->proc->get->cpuTime;
  }

  return min;
}

// Gets the maximum wait time of the queue
int queue::getQueueMax() {
  // If head is null, just return 0
  if (!front) {
    return 0;
  }
  
  int max = (front->get_proc())->get_waitTime() + (front->get_proc())->get_cpuTime();
  queue *cur;

  for (cur = front; cur; cur = cur->get_next()) {
    max = max > (cur->get_proc())->get_waitTime() + (cur->get_proc())->get_cpuTime() ? max : (cur->get_proc())->get_waitTime() + (cur->get_proc()->get_cpuTime());
  }

  return max;
}

// Clones the given queue, and the process elements within.
/////////THIS IS A PROBLEM SITUATION. These are malloced, be sure to free them later
queue* queue::cloneQueue() {
  if (front) {
    queue* newQ = new queueNode(cloneProc(head->get_proc()));
    //////////have to some time check 
    new->next = cloneQueue(head->next);
    return new;
  } else {
    return NULL;
  }
}

// Frees the entire queue, and the process elements contained within
void queue::~queue() {
  if (front) {
    
    //////need to use a while for this part.
    ~queue(head->next);
    if (head->proc) free(head->proc);
    free(head);
  }
}
