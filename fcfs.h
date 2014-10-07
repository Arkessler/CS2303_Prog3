#ifndef FCFS_H_
#define FCFS_H_

#include "queue.h"

class fcfs{
 public:
  fcfs(queue *);
  void run_fcfs();
  int get_curTime();
  void set_curTime(int);
  queue *get_schedQueue();
  void set_schedQueue(queue *);
  queue *get_finishedProcesses();
  void set_finishedProcesses();
  ~fcfs();
 private:
  int curTime;
  queue *schedQueue;
  queue *finishedProcesses;
}


#endif
