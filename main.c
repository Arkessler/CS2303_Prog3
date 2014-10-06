#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "fcfs.h"
#include "rr.h"
#include "util.h"

// Forward declaration of readInput
queue* readInput();

int main(int argc, char **argv) {
  // Queue variables for all three scheduling types, and for main itself
  queue *mainQueue, *fcfsQueue, *rrQueue;
  int slice = 0, numProc = 0;

  DEBUG_PRINT("Starting program");

  DEBUG_PRINT("Reading in argv and c input");

  // Ensure the appropriate number of inputs were given
  if (argc != 3) {
    printf("Usage: ./prog3 sources slice\n");
    printf("Where sources is the number of processes to read in\n");
    printf("And slice is the time size of the round-robin slices\n");
    return EXIT_FAILURE;
  }

  DEBUG_PRINT("Correct number of arguments are valid");

  // Process the inputs
  numProc = atoi(argv[1]);
  slice = atoi(argv[2]);

  DEBUG_PRINT("Arguments retrieved");

  // Ensure inputs are valid
  if (!(numProc > 0)) {
    printf("You entered an invalid number of processes to schedule, exiting\n");
    DEBUG_PRINT("NumProc was %d", numProc);
    return EXIT_FAILURE;
  }

  if (!(slice > 0)) {
    printf("You entered an invalid time slice for round robin, round robin will be skipped\n");
    DEBUG_PRINT("Slice was %d", slice);
  }

  DEBUG_PRINT("Arguments processes, starting input read");

  // Read in the input, and set up the schedule list
  mainQueue = readInput(numProc);  
  DEBUG_PRINT("Finished Read");

  // Clone the main list for the three schedule queues, and
  // dispose of it when we're done
  DEBUG_PRINT("Starting FCFS Clone");
  fcfsQueue = cloneQueue(mainQueue);
  DEBUG_PRINT("Starting RR Clone");
  rrQueue = cloneQueue(mainQueue);
  DEBUG_PRINT("Starting Free");
  freeQueue(mainQueue);
  DEBUG_PRINT("Finished clone and free\n\n");

  // Do the FCFS simulation
  DEBUG_PRINT("Starting FCFS initialization");
  fcfs *fcfsSim = initFCFS(fcfsQueue);
  DEBUG_PRINT("Initialized FCFS");
  runFCFS(fcfsSim);
  DEBUG_PRINT("FCFS run complete");
  destoryFCFS(fcfsSim);
  DEBUG_PRINT("FCFS destroyed\n\n");

  // Do the RR Simulation if slice is valid
  if (slice > 0) {
    DEBUG_PRINT("Starting RR initialization");
    rr *rrSim = initRR(rrQueue, slice);
    DEBUG_PRINT("Initialized RR");
    runRR(rrSim);
    DEBUG_PRINT("RR run complete");
    destroyRR(rrSim);
    DEBUG_PRINT("RR destroyed\n\n");
  }

  DEBUG_PRINT("SIMULATION COMPLETE!");

  return EXIT_SUCCESS;
}

// Reads in the input from stdin. Starts by reading in a number for how 
// many lines to read, then reads in that many lines. It returns a queue
// containing all of the read in lines, in arrival-time order
queue* readInput(int numProc) {
  int i;
  queue *head = NULL;

  // Loop until all lines have been read 
  for (i = 0; i < numProc; i++) {
    printf("\nPlease enter process information in the form process_id, arrival_time, and cpu_time\n");
    int pid;
    int aTime;
    int cpuTime;
    scanf("%d %d %d", &pid, &aTime, & cpuTime);
    process *proc = createProc(pid, aTime, cpuTime);
    head = sortedInsert(head, proc);
  }

  return head;
}
