#include <stdio.h>
#include <stdlib.h>
#include "util.h"

// Processes all of the stats for a given queue, and prints
// them to a given file
void processesStats(FILE *file, queue *stats) {
  float avg, var;
  
  // Calculate the average and variance
  processEX(stats, &avg, &var);
  
  // Print the average and variance
  fprintf(file, "The mean response time for all processes was %f ms\n", avg * 100);
  fprintf(file, "The response time variance for all processes was %f\n", var * 100);

  // Print the max and min wait times
  fprintf(file, "The shortest wait time was %d ms\n", getQueueMin(stats) * 100);
  fprintf(file, "The longest wait time was %d ms\n", getQueueMax(stats) * 100);
  
  fflush(file);
}
