#ifndef BOARD_HELPER_H
#define BOARD_HELPER_H

#include <vector>
#include <string>

class BoardHelper {
public:
    static int getTotalAttack(const std::vector<std::vector<int> >& board);
    static std::string convertToRepresentation(int value);
    static std::vector<std::vector<int> > createBoard(int N, int M, int Q, int K);
    static std::vector<std::vector<int> > placeQueens(std::vector<std::vector<int> >& board, int Q, int K);
    static std::vector<std::vector<int> > placeKnights(std::vector<std::vector<int> >& board, int K);
    static int countQueenAttack(const std::vector<std::vector<int> >& board, int row, int col);
    static int countKnightAttack(const std::vector<std::vector<int> >& board, int row, int col);
    static bool isSafe(const std::vector<std::vector<int> >& board, int row, int col);
    static std::vector<std::vector<int>> createEmptyBoard(int N, int M);

private:
    static bool goRightQueen(const std::vector<std::vector<int> >& board, int row, int col);
    static bool goLeftQueen(const std::vector<std::vector<int> >& board, int row, int col);
    static bool goUpQueen(const std::vector<std::vector<int> >& board, int row, int col);
    static bool goDownQueen(const std::vector<std::vector<int> >& board, int row, int col);
    static bool goRightUpQueen(const std::vector<std::vector<int> >& board, int row, int col);
    static bool goRightDownQueen(const std::vector<std::vector<int> >& board, int row, int col);
    static bool goLeftUpQueen(const std::vector<std::vector<int> >& board, int row, int col);
    static bool goLeftDownQueen(const std::vector<std::vector<int> >& board, int row, int col);
};

#endif // BOARD_HELPER_H
