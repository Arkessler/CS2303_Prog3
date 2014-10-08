#ifndef QUEUE_H_
#define QUEUE_H_
#include "process.h"

// A generic member of the queue, which has a reference to
// the process in the queue and the next element of the queue


class queueNode{

  friend class queue;
 public:
  queueNode(process *);
  queueNode *get_next();
  queueNode *enqueue(process *);
  queueNode *sortedInsert(process *);
  queueNode *cloneQueue();
  void set_next(queueNode *);
  process *get_proc();
  void set_proc(process *);
  ~queueNode();
  
 private:
  queueNode *next;
  process *proc;
};

class queue{
 public:
  queue();
  queue( queueNode *);
  queue *cloneQueue();
  queueNode *pop( process **);
  void peak(process **);
  queueNode* enqueue(process *);
  queueNode* sortedInsert(process *);
  void processEX(float *, float *);
  int getQueueMin();
  int getQueueMax();
  float getQueueAverage();
  float getQueueVariance(float);

  ~queue();

  queueNode *get_front();
  void set_front(queueNode*);

 private:
  queueNode *front;
};

// Pops the next element off of the queue
// This returns a pointer to the next head element,
// and stores a pointer to the process in the given
// out location. This frees the queue element
queue* pop(queue *head, process **out);

// Peaks at the next element of the queue, and stores
// a pointer to the element at the given location.
void peak(queue *head, process **out);

// Enqueues an element in a given list, mallocing a new
// queue structure for the element
queue* enqueue(queue *head, process *proc);

// Inserts the given proces into the queue, sorted by
// cpu time. Returns a pointer to the new head of the queue
queue* sortedInsert(queue *head, process *proc);

// Calculates the average and variance of the queue, and 
// stores them in the given float pointers
void processEX(queue *head, float *avg, float *var);

// Gets the minimum wait time of the queue
int getQueueMin(queue *head);

// Gets the maximum wait time of the queue
int getQueueMax(queue *head);

// Clones the given queue, and the process elements within.
// These are malloced, be sure to free them later
queue* cloneQueue(queue *head);

// Frees the entire queue, and the process elements contained within
void freeQueue(queue* head);

#endif
