#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "util.h"

// Forward declaration of createQueueElement
queue* createQueueElement(process *proc);

// Pops the next element off of the queue
// This returns a pointer to the next head element,
// and stores a pointer to the process in the given
// out location. This frees the given queue element,
// so do not attempt to use it again. To just get the
// process element, use the peak method
queue* pop(queue *head, process **out) {
  queue* next = head->next;
  peak(head, out);
  free(head);
  return next;
}

// Peaks at the next element of the queue, and stores
// a pointer to the element at the given location.
void peak(queue *head, process **out) {
  if (head) *out = head->proc;
}

// Enqueues an element in a given list, mallocing a new
// queue structure for the element. If null is passed 
// in for head, a new queue will be created
queue* enqueue(queue *head, process *proc) {
  if (head == NULL) {
    return createQueueElement(proc);
  } else {
    head->next = enqueue(head->next, proc);
    return head;
  }
}

// Inserts the given proces into the queue, sorted by
// cpu time. Returns a pointer to the new head of the queue
queue* sortedInsert(queue *head, process *proc) {
  if (head == NULL) {
    // Empty case, return a new element
    return createQueueElement(proc);
  } else if (procLessThan(proc, head->proc)) {
    // New process arrives before, insert before
    queue *new = createQueueElement(proc);
    new->next = head;
    return new;
  } else {
    // New process arrives after, insert after
    head->next = sortedInsert(head->next, proc);
    return head;
  }
}

// Gets the average wait times of all the processes in the list
float getQueueAverage(queue *head){
  queue *cur;
  int total = 0, count = 0;

  // Loop until we reach the tail of the list
  for (cur = head; cur; cur = cur->next) {
    total += cur->proc->waitTime;
    count++;
  }

  return ((float) total)/count;
}

// Calculates the variance of the queue, given the average wait time
// The formula for variance is sum((waitTime_i - mean)^2)/n
float getQueueVariance(queue* head, float avg) {
  // Accumulators for the total and count
  float total = 0;
  int count = 0;
  queue *cur;

  // Loop until we reach the tail of the list
  for (cur = head; cur; cur = cur->next) {
    float diff = getDifference(head->proc, avg);
    total += pow(diff, 2);
    count++;
  }

  return total/count;
}

// Calculates the average and variance of all given processes. The forumla
// for response time is finish time - arrival time. The formula
// for variance is EX^2 - (EX)^2, where X is the average response
// time 
void processEX(queue *head, float *avg, float *var) {
  float x, x2;
  int count;
  queue *cur;

  for (cur = head; cur; cur = cur->next) {
    int repTime = cur->proc->waitTime + cur->proc->cpuTime;
    x += repTime;
    x2 += pow(repTime, 2);
    count++;
  }

  (*avg) = x / count;
  (*var) = (x2 / count) - pow((*avg), 2);
}

// Gets the minimum wait time of the queue
int getQueueMin(queue *head) {
  // If head is null, just return 0
  if (!head) {
    return 0;
  }
  
  int min = head->proc->waitTime + head->proc->cpuTime;
  queue *cur;

  for (cur = head; cur; cur = cur->next) {
    min = min < cur->proc->waitTime + cur->proc->cpuTime ? min : cur->proc->waitTime + cur->proc->cpuTime;
  }

  return min;
}

// Gets the maximum wait time of the queue
int getQueueMax(queue *head) {
  // If head is null, just return 0
  if (!head) {
    return 0;
  }
  
  int max = head->proc->waitTime + head->proc->cpuTime;
  queue *cur;

  for (cur = head; cur; cur = cur->next) {
    max = max > cur->proc->waitTime + cur->proc->cpuTime ? max : cur->proc->waitTime + cur->proc->cpuTime;
  }

  return max;
}

// Clones the given queue, and the process elements within.
// These are malloced, be sure to free them later
queue* cloneQueue(queue *head) {
  if (head) {
    queue* new = createQueueElement(cloneProc(head->proc));
    new->next = cloneQueue(head->next);
    return new;
  } else {
    return NULL;
  }
}

// Frees the entire queue, and the process elements contained within
void freeQueue(queue* head) {
  if (head) {
    freeQueue(head->next);
    if (head->proc) free(head->proc);
    free(head);
  }
}

// Conveniece helper for creating new queue elements and 
// giving them a process
queue* createQueueElement(process *proc) {
    queue *new = malloc(sizeof(queue));
    new->next = NULL;
    new->proc = proc;
    return new;
}
