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
  queue *pop( process **);
  void peak(process **);
  queue* enqueue(process *);
  queue* sortedInsert(process *);
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
};//
#endif
