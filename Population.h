#ifndef POPULATION_H
#define POPULATION_H

#include "Node.h"
#include <queue>

class Population{
	public:
		std::vector<std::pair<float, std::shared_ptr<Node>>> population;
		std::pair<float, std::string> best;
		double crossoverRate;
		double mutateRate;
		std::mt19937 rng;
		std::uniform_real_distribution<double> dist;
		Population(int popSize, double crossoverRate, double mutateRate);
		void crossover(std::shared_ptr<Node> &first, std::shared_ptr<Node> &second);
		void mutate(std::shared_ptr<Node> &tree);
		void score(std::pair<float, std::shared_ptr<Node>> &tree);
		void doGeneration();
		void migrate(std::vector<std::pair<float, std::shared_ptr<Node>>> &newPop);
};

#endif
