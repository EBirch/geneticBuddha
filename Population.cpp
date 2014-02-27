#include "Population.h"

Population::Population(std::vector<std::shared_ptr<Node>> population, double crossoverRate, double mutateRate)
	:population(population)
	,crossoverRate(crossoverRate)
	,mutateRate(mutateRate)
{}

void Population::crossover(std::shared_ptr<Node> first, std::shared_ptr<Node> second){
	//use breadth-first here
}

void Population::mutate(std::shared_ptr<Node> tree){

}

double Population::score(std::shared_ptr<Node> tree){

}

void Population::doGeneration(){

}

