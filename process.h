#ifndef PROCESS_H_
#define PROCESS_H_

#include <stdio.h>

// A process is defined by the process ID, the arrival time (in 100 millisecond intervals), 
// and the cpu time (in 100 millisecond intervals). It keeps track of how much time it has
// waited, and how much time it has left in it's run
typedef struct PROCESS {
  int pid;
  int aTime;
  int cpuTime;
  int waitTime;
  int remainTime;
} process;

class process{
 public:
  process();
  process(int, int, int);
  int procLessThan(process *);
  float getDifference(float);
  process *cloneProc(process *);
  ~process();

  int get_pid();
  int get_aTime();
  int get_cpuTime();
  int get_waitTime();
  int get_remainTime();

  void set_pid(int);
  void set_aTime(int);
  void set_cpuTime(int);
  void set_waitTime(int);
  void set_remainTime(int);

 private:
  int pid;
  int aTime;
  int cpuTime;
  int waitTime;
  int remainTime;
};

// Mallocs space for a new process
process* createProc(int pid, int aTime, int cpuTime);

// Compares two processes, returning 0 if the old
// process comes before the new process, 1 otherwise
int procLessThan(process *new , process *old);

// Gets the difference between this wait time and the average wait time
float getDifference(process *proc, float avg);

// Creates a clone of the given process. This is malloced,
// be sure to free it later
process* cloneProc(process *proc);

#endif
