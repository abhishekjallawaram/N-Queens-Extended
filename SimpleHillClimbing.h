#ifndef SIMPLE_HILL_CLIMBING_H
#define SIMPLE_HILL_CLIMBING_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "BoardHelper.h"

class HillClimbing {
public:
    virtual std::vector<std::vector<int> > execute(int N, int M, int Q, int K, double startTime, int tmax) = 0;
    virtual ~HillClimbing() = default;
};

class SimpleHillClimbing : public HillClimbing {
public:
    std::vector<std::vector<int> > execute(int N, int M, int Q, int K, double startTime, int tmax) override;
};

#endif // SIMPLE_HILL_CLIMBING_H
