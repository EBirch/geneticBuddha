#include "Population.h"

Population::Population(std::vector<std::shared_ptr<Node>> population, double crossoverRate, double mutateRate)
	:population(population)
	,crossoverRate(crossoverRate)
	,mutateRate(mutateRate)
	,rng(time(NULL))
	,dist(0, 1)
{}

void Population::crossover(std::shared_ptr<Node> &first, std::shared_ptr<Node> &second){
	std::queue<std::shared_ptr<Node>> firstQueue;
	std::queue<std::shared_ptr<Node>> secondQueue;
	firstQueue.push(first);
	secondQueue.push(second);
	while(firstQueue.size() && secondQueue.size()){
		if(!firstQueue.front()->children.size() || !secondQueue.front()->children.size()){
			if(!firstQueue.front()->children.size()){
				firstQueue.pop();
			}
			if(!secondQueue.front()->children.size()){
				secondQueue.pop();
			}
			continue;
		}
		if(dist(rng) <= crossoverRate){
			std::uniform_int_distribution<int> firstDist(0, firstQueue.front()->children.size() - 1);
			std::uniform_int_distribution<int> secondDist(0, secondQueue.front()->children.size() - 1);
			std::swap(firstQueue.front()->children[firstDist(rng)], secondQueue.front()->children[secondDist(rng)]);
		}
		for(auto &child : firstQueue.front()->children){
			firstQueue.push(child);
		}
		for(auto &child : secondQueue.front()->children){
			secondQueue.push(child);
		}
		firstQueue.pop();
		secondQueue.pop();
	}
}

void Population::mutate(std::shared_ptr<Node> &tree){
	for(auto &child : tree->children){
		if(dist(rng) <= mutateRate){
			child = getRandomTree();
		}
		mutate(child);
	}
}

double Population::score(std::shared_ptr<Node> &tree){
	return 0.0;
}

void Population::doGeneration(){

}
