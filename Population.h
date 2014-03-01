#ifndef POPULATION_H
#define POPULATION_H

#include "Node.h"
#include <queue>

class Population{
	public:
		std::vector<std::shared_ptr<Node>> population;
		double crossoverRate;
		double mutateRate;
		std::mt19937 rng;
		std::uniform_real_distribution<double> dist;
		Population(std::vector<std::shared_ptr<Node>> population, double crossoverRate, double mutateRate);
		void crossover(std::shared_ptr<Node> &first, std::shared_ptr<Node> &second);
		void mutate(std::shared_ptr<Node> &tree);
		double score(std::shared_ptr<Node> &tree);
		void doGeneration();
};

#endif
