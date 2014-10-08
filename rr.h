#ifndef RR_H_
#define RR_H_

#include "queue.h"
class rr{
 public:
  rr(queue *, int);
  void runRR();
  int get_curTime();
  int get_slice();
  queue *get_schedQueue();
  queue *get_finishedProcesses();
  queue *get_runningQueue();
  void processArrive();
  ~rr();

  rr *set_curTime(int);
  rr *set_slice(int);
  rr *set_runningQueue(queue *);
  rr *set_schedQueue(queue *);
  rr *set_finishedProcesses(queue *);

 private:
  int curTime;
  int slice;
  queue *schedQueue;
  queue *runningQueue;
  queue *finishedProcesses;
};

#endif
