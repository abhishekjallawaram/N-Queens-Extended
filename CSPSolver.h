#ifndef CSPSOLVER_H
#define CSPSOLVER_H

#include "BoardHelper.h"
#include <vector>

class CSPSolver {
public:
    std::vector<std::vector<int>> solve(int N, int M, int Q, int K, double startTime, int tmax);

private:
    bool solveNQueensUtil(std::vector<std::vector<int>>& board, int col);
};

#endif // CSPSOLVER_H
