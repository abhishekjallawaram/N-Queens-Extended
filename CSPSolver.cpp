#include "CSPSolver.h"
#include "BoardHelper.h"
#include <vector>
#include <iostream>

bool CSPSolver::solveNQueensUtil(std::vector<std::vector<int>>& board, int col) {
    int N = board.size();
    if (col >= N) return true;

    for (int i = 0; i < N; ++i) {
        if (BoardHelper::isSafe(board, i, col)) {
            board[i][col] = 1;
            // std::cout << "Placed queen at (" << i << ", " << col << ")" << std::endl;
            if (solveNQueensUtil(board, col + 1)) return true;
            board[i][col] = 0;
            //std::cout << "Removed queen from (" << i << ", " << col << ")" << std::endl;
        }
    }
    return false;
}

std::vector<std::vector<int>> CSPSolver::solve(int N, int M, int Q, int K, double startTime, int tmax) {
    std::vector<std::vector<int>> board = BoardHelper::createEmptyBoard(N, M);
    bool solved = solveNQueensUtil(board, 0);
    if (!solved) {
        throw std::runtime_error("No solution found");
    }
    return board;
}
