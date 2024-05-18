#include "BoardHelper.h"
#include <random>
#include <algorithm>
#include <stdexcept>

std::vector<std::vector<int> > BoardHelper::createBoard(int N, int M, int Q, int K) {
    std::vector<std::vector<int> > board(N, std::vector<int>(M, 0));
    if (Q > 0 && K > 0) {
        board = placeQueens(board, Q, K);
        board = placeKnights(board, K);
    } else if (Q > 0) {
        board = placeQueens(board, Q, K);
    } else {
        board = placeKnights(board, K);
    }
    return board;
}

std::vector<std::vector<int>> BoardHelper::createEmptyBoard(int N, int M) {
    return std::vector<std::vector<int>>(N, std::vector<int>(M, 0));
}

bool BoardHelper::isSafe(const std::vector<std::vector<int>>& board, int row, int col) {
    int N = board.size();
    int M = board[0].size();

    for (int i = 0; i < col; ++i) {
        if (board[row][i] == 1) return false;
    }
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 1) return false;
    }
    for (int i = row, j = col; i < N && j >= 0; ++i, --j) {
        if (board[i][j] == 1) return false;
    }

    return true;
}

std::vector<std::vector<int> > BoardHelper::placeQueens(std::vector<std::vector<int> >& board, int Q, int K) {
    int N = board.size();
    int M = board[0].size();
    int placedQueens = 0;
    int knightPlaced = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disN(0, N-1);
    std::uniform_int_distribution<> disM(0, M-1);

    if (Q <= N) {
        int posIncrease = N / Q;
        int prevPos = -1;
        int currRow = 0;
        while (placedQueens < Q) {
            int currPos = disM(gen);
            while (currPos == prevPos || board[currRow][currPos] != 0) {
                currPos = disM(gen);
            }
            board[currRow][currPos] = 1;
            if (knightPlaced < K - 2) {
                if (currRow + 1 < N) {
                    if (currPos + 1 < M && board[currRow + 1][currPos + 1] == 0) {
                        board[currRow + 1][currPos + 1] = 2;
                        knightPlaced++;
                    }
                    if (currPos - 1 >= 0 && board[currRow + 1][currPos - 1] == 0) {
                        board[currRow + 1][currPos - 1] = 2;
                        knightPlaced++;
                    }
                }
            }
            prevPos = currPos;
            currRow = (currRow + posIncrease) % N;
            placedQueens++;
        }
    } else {
        while (placedQueens < Q) {
            int rowPos = disN(gen);
            int colPos = disM(gen);
            if (board[rowPos][colPos] == 0) {
                board[rowPos][colPos] = 1;
                placedQueens++;
            }
        }
    }
    return board;
}

std::vector<std::vector<int> > BoardHelper::placeKnights(std::vector<std::vector<int> >& board, int K) {
    int N = board.size();
    int M = board[0].size();
    int placedKnights = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disN(0, N-1);
    std::uniform_int_distribution<> disM(0, M-1);

    while (placedKnights < K) {
        int rowPos = disN(gen);
        int colPos = disM(gen);
        if (board[rowPos][colPos] == 0) {
            board[rowPos][colPos] = 2;
            placedKnights++;
        }
    }
    return board;
}

bool BoardHelper::goRightQueen(const std::vector<std::vector<int> >& board, int row, int col) {
    int M = board[0].size();
    while (col < M) {
        if (board[row][col] == 0) {
            col++;
        } else if (board[row][col] == 2) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

bool BoardHelper::goLeftQueen(const std::vector<std::vector<int> >& board, int row, int col) {
    while (col >= 0) {
        if (board[row][col] == 0) {
            col--;
        } else if (board[row][col] == 2) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

bool BoardHelper::goUpQueen(const std::vector<std::vector<int> >& board, int row, int col) {
    while (row >= 0) {
        if (board[row][col] == 0) {
            row--;
        } else if (board[row][col] == 2) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

bool BoardHelper::goDownQueen(const std::vector<std::vector<int> >& board, int row, int col) {
    int N = board.size();
    while (row < N) {
        if (board[row][col] == 0) {
            row++;
        } else if (board[row][col] == 2) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

bool BoardHelper::goRightUpQueen(const std::vector<std::vector<int> >& board, int row, int col) {
    int M = board[0].size();
    while (row >= 0 && col < M) {
        if (board[row][col] == 0) {
            row--;
            col++;
        } else if (board[row][col] == 2) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

bool BoardHelper::goRightDownQueen(const std::vector<std::vector<int> >& board, int row, int col) {
    int N = board.size();
    int M = board[0].size();
    while (row < N && col < M) {
        if (board[row][col] == 0) {
            row++;
            col++;
        } else if (board[row][col] == 2) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

bool BoardHelper::goLeftUpQueen(const std::vector<std::vector<int> >& board, int row, int col) {
    while (row >= 0 && col >= 0) {
        if (board[row][col] == 0) {
            row--;
            col--;
        } else if (board[row][col] == 2) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

bool BoardHelper::goLeftDownQueen(const std::vector<std::vector<int> >& board, int row, int col) {
    int N = board.size();
    while (row < N && col >= 0) {
        if (board[row][col] == 0) {
            row++;
            col--;
        } else if (board[row][col] == 2) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

int BoardHelper::countQueenAttack(const std::vector<std::vector<int> >& board, int row, int col) {
    int attackCount = 0;
    if (goRightQueen(board, row, col + 1)) attackCount++;
    if (goLeftQueen(board, row, col - 1)) attackCount++;
    if (goUpQueen(board, row - 1, col)) attackCount++;
    if (goDownQueen(board, row + 1, col)) attackCount++;
    if (goRightUpQueen(board, row - 1, col + 1)) attackCount++;
    if (goRightDownQueen(board, row + 1, col + 1)) attackCount++;
    if (goLeftUpQueen(board, row - 1, col - 1)) attackCount++;
    if (goLeftDownQueen(board, row + 1, col - 1)) attackCount++;
    return attackCount;
}

int BoardHelper::countKnightAttack(const std::vector<std::vector<int> >& board, int row, int col) {
    int attackCount = 0;
    int N = board.size();
    int M = board[0].size();

    std::vector<std::pair<int, int> > knightMoves = {
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}
    };

    for (const auto& move : knightMoves) {
        int newRow = row + move.first;
        int newCol = col + move.second;
        if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < M && board[newRow][newCol] != 0) {
            attackCount++;
        }
    }

    return attackCount;
}

int BoardHelper::getTotalAttack(const std::vector<std::vector<int> >& board) {
    int totalAttack = 0;
    int N = board.size();
    int M = board[0].size();

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            if (board[row][col] == 1) {
                totalAttack += countQueenAttack(board, row, col);
            } else if (board[row][col] == 2) {
                totalAttack += countKnightAttack(board, row, col);
            }
        }
    }

    return totalAttack;
}

std::string BoardHelper::convertToRepresentation(int value) {
    if (value == 1) return "Q";
    if (value == 2) return "K";
    return "E";
}
