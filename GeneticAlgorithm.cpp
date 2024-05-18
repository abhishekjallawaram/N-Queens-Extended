#include "GeneticAlgorithm.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

std::vector<std::vector<int>> GeneticAlgorithm::solve(int N, int M, int Q, int K, double startTime, int tmax) {
    int populationSize = 200;  // Increase population size
    double mutationRate = 0.02; // Adjust mutation rate
    int generations = 2000;    // Increase generations

    std::vector<std::vector<int>> population = initializePopulation(N, populationSize);
    std::vector<int> bestIndividual;
    int bestFitness = -1;

    auto start = std::chrono::steady_clock::now();

    for (int generation = 0; generation < generations; ++generation) {
        std::vector<std::pair<int, std::vector<int>>> fitnessPopulation;

        for (const auto& individual : population) {
            int fit = fitness(individual);
            fitnessPopulation.push_back({fit, individual});
            if (fit > bestFitness) {
                bestFitness = fit;
                bestIndividual = individual;
            }
        }

        std::sort(fitnessPopulation.begin(), fitnessPopulation.end(), std::greater<>());

        std::vector<std::vector<int>> newPopulation;

        for (int i = 0; i < populationSize / 2; ++i) {
            auto& parent1 = fitnessPopulation[i].second;
            auto& parent2 = fitnessPopulation[(i + 1) % (populationSize / 2)].second;

            std::vector<int> child1 = crossover(parent1, parent2);
            std::vector<int> child2 = crossover(parent2, parent1);

            mutate(child1, mutationRate);
            mutate(child2, mutationRate);

            newPopulation.push_back(child1);
            newPopulation.push_back(child2);
        }

        population = newPopulation;

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        if (elapsed_seconds.count() > tmax) {
            break;
        }
    }

    // Convert the best individual to board representation
    std::vector<std::vector<int>> board(N, std::vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        board[i][bestIndividual[i]] = 1; // Place a queen
    }

    return board;
}

std::vector<std::vector<int>> GeneticAlgorithm::initializePopulation(int N, int populationSize) {
    std::vector<std::vector<int>> population;
    for (int i = 0; i < populationSize; ++i) {
        population.push_back(createIndividual(N));
    }
    return population;
}

std::vector<int> GeneticAlgorithm::createIndividual(int N) {
    std::vector<int> individual(N);
    std::iota(individual.begin(), individual.end(), 0); // Fill with 0, 1, 2, ..., N-1
    std::shuffle(individual.begin(), individual.end(), std::default_random_engine(std::random_device()()));
    return individual;
}

int GeneticAlgorithm::fitness(const std::vector<int>& individual) {
    int conflicts = 0;
    int N = individual.size();
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (individual[i] == individual[j] ||
                individual[i] - i == individual[j] - j ||
                individual[i] + i == individual[j] + j) {
                ++conflicts;
            }
        }
    }
    return -conflicts; // Fewer conflicts is better
}

std::vector<int> GeneticAlgorithm::crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
    int N = parent1.size();
    std::vector<int> child(N, -1);
    int crossoverPoint = std::rand() % N;

    // Copy the first part from parent1
    for (int i = 0; i < crossoverPoint; ++i) {
        child[i] = parent1[i];
    }

    // Copy the remaining part from parent2, ensuring no duplicates
    for (int i = 0; i < N; ++i) {
        if (std::find(child.begin(), child.end(), parent2[i]) == child.end()) {
            *std::find(child.begin(), child.end(), -1) = parent2[i];
        }
    }

    return child;
}

void GeneticAlgorithm::mutate(std::vector<int>& individual, double mutationRate) {
    int N = individual.size();
    for (int i = 0; i < N; ++i) {
        if ((std::rand() / (double)RAND_MAX) < mutationRate) {
            int j = std::rand() % N;
            std::swap(individual[i], individual[j]);
        }
    }
}
