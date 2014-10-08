#include <iostream>
using namespace std;
#include "util.h"

// Processes all of the stats for a given queue, and prints
// them to a given file
void processesStats(queue *stats) {
  float avg, var;
  
  // Calculate the average and variance
  processEX(stats, &avg, &var);
  
  // Print the average and variance
  cout << "The mean response time for all processes was "<<  avg * 100 << " ms\n";
  cout << "The response time variance for all processes was " << var * 100 << " ms\n";

  // Print the max and min wait times
  cout << "The shortest wait time was "<< getQueueMin(stats) *100 << " ms\n";
  cout << "The longest wait time was " << getQueueMax(stats) * 100 << " ms\n";
  
}
