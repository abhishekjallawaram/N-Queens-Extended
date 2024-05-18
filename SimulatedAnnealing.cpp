#include "SimulatedAnnealing.h"
#include "BoardHelper.h"
#include <chrono>
#include <random>
#include <iostream>
#include <utility>
#include <tuple>

std::vector<std::vector<int> > SimulatedAnnealing::execute(int N, int M, int Q, int K, double startTime, int tmax) {
    auto board = BoardHelper::createBoard(N, M, Q, K);
    int minimumAttack = BoardHelper::getTotalAttack(board);
    double temperature = 200;
    double schedule = 0.99;
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

        temperature *= schedule;
        std::shuffle(occupiedPositions.begin(), occupiedPositions.end(), gen);

        for (const auto& position : occupiedPositions) {
            int previousAttack = BoardHelper::getTotalAttack(board);
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
            int colIndex = rangeM[0];

            board[row][col] = board[row][colIndex];
            board[row][colIndex] = positionInitValue;
            int currentAttack = BoardHelper::getTotalAttack(board);
            int delta = currentAttack - previousAttack;
            std::uniform_real_distribution<> dis(0, 1);
            double prob = dis(gen);
            double cooling = std::exp(-delta / temperature);

            if (delta <= 0 || prob > cooling) {
                minimumAttack = currentAttack;
                if (prob > cooling) {
                    temperature += 200;
                }
                if (currentAttack == 0) {
                    return board;
                }
                break;
            } else {
                board[row][colIndex] = board[row][col];
                board[row][col] = positionInitValue;
            }

            if (minimumAttack == 0) {
                return board;
            }
        }
    }

    return board;
}
