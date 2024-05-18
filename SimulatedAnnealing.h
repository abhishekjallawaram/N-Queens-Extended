#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include "BoardHelper.h"
#include "SimpleHillClimbing.h"

class SimulatedAnnealing : public HillClimbing {
public:
    std::vector<std::vector<int> > execute(int N, int M, int Q, int K, double startTime, int tmax) override;
};

#endif // SIMULATED_ANNEALING_H
