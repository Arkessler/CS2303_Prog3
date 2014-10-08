
#ifndef UTIL_H_
#define UTIL_H_
#include "queue.h"
#include <iostream>

#ifdef DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__); printf("\n");
#else

#define DEBUG_PRINT(...) // Expand to nothing!
#endif

// Processes all of the stats for a given queue, and prints
// them to a given file
void processesStats(queue *stats);

#endif
