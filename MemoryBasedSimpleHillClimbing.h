#ifndef MEMORY_BASED_SIMPLE_HILL_CLIMBING_H
#define MEMORY_BASED_SIMPLE_HILL_CLIMBING_H

#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include "BoardHelper.h"
#include "SimpleHillClimbing.h"

class MemoryBasedSimpleHillClimbing : public HillClimbing {
public:
    std::vector<std::vector<int> > execute(int N, int M, int Q, int K, double startTime, int tmax) override;

private:
    std::vector<std::vector<int> > memoryBasedSimpleHillClimbing(int N, int M, int Q, int K, double startTime, int tmax, std::set<std::vector<std::vector<int> > >& boardsSeen);
};

#endif // MEMORY_BASED_SIMPLE_HILL_CLIMBING_H
