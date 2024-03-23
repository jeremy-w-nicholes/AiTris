#ifndef AIGA_H
#define AIGA_H

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class AI_Agent {
public:
    float weight_complete_lines;
    float weight_holes;
    float weight_bumpiness;
    float weight_aggregate_height;
    float fitness;

    AI_Agent() : fitness(0) {
        srand(time(NULL));
        weight_complete_lines = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        weight_holes = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        weight_bumpiness = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        weight_aggregate_height = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
};

class GeneticAlgorithm {
private:
    std::vector<AI_Agent> population;
    int populationSize;

public:
    GeneticAlgorithm(int size) : populationSize(size) {
        for (int i = 0; i < populationSize; ++i) {
            population.push_back(AI_Agent());
        }
    }

    void evaluateFitness() {
        // Placeholder for fitness evaluation logic
        // You need to implement the logic to evaluate the fitness of each agent
        for (auto &agent : population) {
            // The fitness calculation should be based on the agent's performance in the game
            // For example, agent.fitness = playGameWithAI(agent);
            agent.fitness = static_cast <float> (rand()); // Replace this with real fitness calculation
        }
    }

    void selection() {
        // Sort the agents based on their fitness
        std::sort(population.begin(), population.end(), [](const AI_Agent &a, const AI_Agent &b) -> bool {
            return a.fitness > b.fitness;
        });

        // Keep the top N agents, discard the rest
        population.resize(populationSize / 2);
    }

    // Add methods for crossover and mutation
};



#endif // AIGA_H