#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>

class GeneticAlgorithm {
public:
    std::vector<std::vector<int>> solve(int N, int M, int Q, int K, double startTime, int tmax);

private:
    std::vector<std::vector<int>> initializePopulation(int N, int populationSize);
    std::vector<int> createIndividual(int N);
    int fitness(const std::vector<int>& individual);
    std::vector<int> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2);
    void mutate(std::vector<int>& individual, double mutationRate);
};

#endif // GENETICALGORITHM_H
