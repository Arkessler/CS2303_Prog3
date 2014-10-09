#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "fcfs.h"
#include "rr.h"
#include "util.h"
#define DEBUG_PRINT

// Forward declaration of readInput
queue* readInput(int);

int main(int argc, char **argv) {
  // Queue variables for all three scheduling types, and for main itself
  queue *mainQueue, *fcfsQueue, *rrQueue;
  int slice = 0, numProc = 0;

  DEBUG_PRINT("Starting program");

  DEBUG_PRINT("Reading in argv and c input");

  // Ensure the appropriate number of inputs were given
  if (argc != 3) {
    cout<<"Usage: ./prog3 sources slice\n";
    cout<<"Where sources is the number of processes to read in\n";
    cout<<"And slice is the time size of the round-robin slices\n";
    return EXIT_FAILURE;
  }

  DEBUG_PRINT("Correct number of arguments are valid");

  // Process the inputs
  numProc = atoi(argv[1]);
  slice = atoi(argv[2]);

  DEBUG_PRINT("Arguments retrieved");

  // Ensure inputs are valid
  if (!(numProc > 0)) {
    cout<<"You entered an invalid number of processes to schedule, exiting\n";
    DEBUG_PRINT("NumProc was %d", numProc);
    return EXIT_FAILURE;
  }

  if (!(slice > 0)) {
    cout<<"You entered an invalid time slice for round robin, round robin will be skipped\n";
    DEBUG_PRINT("Slice was %d", slice);
  }

  if (DEBUG) cout<<"correct inputs"<<endl;

  // Read in the input, and set up the schedule list
  mainQueue = readInput(numProc);  
 
  if(DEBUG1) cout<< "Finished Read"<<endl;

  // Clone the main list for the three schedule queues, and
  // dispose of it when we're done
  DEBUG_PRINT("Starting FCFS Clone");
  
  if(DEBUG1) cout<< "starting FCFS cloning" <<endl;
  fcfsQueue = new queue();
  fcfsQueue = mainQueue->cloneQueue();
  
  if(DEBUG1) cout<< "starting RR cloning" <<endl;

  DEBUG_PRINT("Starting RR Clone");
  
  rrQueue = new queue();
  rrQueue = mainQueue->cloneQueue();
  DEBUG_PRINT("Starting Free");

  if(DEBUG1) cout<< "deleting main queue" <<endl;
  delete mainQueue;
  DEBUG_PRINT("Finished clone and free\n\n");


  /*  THIS ISN'T NECESSARY FOR LAB
  if(DEBUG1) cout<< "starting FCFS sim" <<endl;
  // Do the FCFS simulation
  DEBUG_PRINT("Starting FCFS initialization");
  fcfs *fcfsSim = new fcfs(fcfsQueue);
  DEBUG_PRINT("Initialized FCFS");
  fcfsSim->run_fcfs();
  
  if(DEBUG1) cout<<"ending FCFS sim" <<endl;
  DEBUG_PRINT("FCFS run complete");
  delete fcfsSim;
  if(DEBUG1) cout<<"deleted FCFS sim"<<endl;
  DEBUG_PRINT("FCFS destroyed\n\n");
  */


  // Do the RR Simulation if slice is valid
  if (slice > 0) {
    if(DEBUG1)cout<< "Starting RR initialization"<<endl;
    rr *rrSim = new rr(rrQueue, slice);
    if(DEBUG1)cout<< "Initialized RR"<<endl;
    rrSim->runRR();
    if(DEBUG1)cout<< "RR run complete"<<endl;
    delete rrSim;
    if(DEBUG1)cout<<"RR destroyed\n\n"<<endl;
  }

  DEBUG_PRINT("SIMULATION COMPLETE!");

  return EXIT_SUCCESS;
}

// Reads in the input from stdin. Starts by reading in a number for how 
// many lines to read, then reads in that many lines. It returns a queue
// containing all of the read in lines, in arrival-time order
queue* readInput(int numProc) {
  int i;
  queue *head = new queue();

  // Loop until all lines have been read 
  for (i = 0; i < numProc; i++) {
    cout<<"\nPlease enter process information in the form process_id, arrival_time, and cpu_time\n";
    int pid;
    int aTime;
    int cpuTime;
    int ioTime;
    cin>>pid;
    cin>>aTime;
    cin>>cpuTime;
    cin>> ioTime;

    if(DEBUG) cout<<"read in correctly"<< endl;
    process *proc = new process(pid, aTime, cpuTime, ioTime);
    if(DEBUG) cout<<"assigned correctly, :"<<proc->get_pid()<<" "<< proc->get_aTime() << " " << proc->get_cpuTime() << endl;
    head->set_front(sortedInsert(head->get_front(), proc));
    if(DEBUG) cout<<"passed insert correctly "<< head->get_front()->get_proc() <<endl;//->get_pid() <<endl;
  }

  return head;
}
