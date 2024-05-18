#include "SimpleHillClimbing.h"
#include "BoardHelper.h"
#include <chrono>
#include <random>
#include <iostream>
#include <utility>
#include <tuple>

std::vector<std::vector<int> > SimpleHillClimbing::execute(int N, int M, int Q, int K, double startTime, int tmax) {
    auto board = BoardHelper::createBoard(N, M, Q, K);
    int minimumAttack = BoardHelper::getTotalAttack(board);
    std::random_device rd;
    std::mt19937 gen(rd());

    while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() - startTime < tmax) {
        if (minimumAttack == 0) {
            return board;
        }

        std::vector<std::pair<int, int> > queenPositions;
        std::vector<std::pair<int, int> > knightPositions;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (board[i][j] == 1) {
                    queenPositions.emplace_back(i, j);
                } else if (board[i][j] == 2) {
                    knightPositions.emplace_back(i, j);
                }
            }
        }

        std::vector<std::pair<int, int> > occupiedPositions = queenPositions;
        occupiedPositions.insert(occupiedPositions.end(), knightPositions.begin(), knightPositions.end());

        std::shuffle(occupiedPositions.begin(), occupiedPositions.end(), gen);

        for (const auto& position : occupiedPositions) {
            int row = position.first;
            int col = position.second;
            int positionInitValue = board[row][col];
            std::vector<int> rangeM;

            for (int x = 0; x < M; ++x) {
                if (x != col) {
                    rangeM.push_back(x);
                }
            }

            std::shuffle(rangeM.begin(), rangeM.end(), gen);
            int newCol = col;

            for (int colIndex : rangeM) {
                board[row][col] = board[row][colIndex];
                board[row][colIndex] = positionInitValue;
                int attackCount = BoardHelper::getTotalAttack(board);

                if (attackCount <= minimumAttack) {
                    minimumAttack = attackCount;
                    newCol = colIndex;
                }

                board[row][colIndex] = board[row][col];
                board[row][col] = positionInitValue;
            }

            board[row][col] = board[row][newCol];
            board[row][newCol] = positionInitValue;

            if (minimumAttack == 0) {
                return board;
            }
        }
    }

    return board;
}
