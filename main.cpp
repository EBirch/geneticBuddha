#include <mpi.h>
#include <iostream>
#include "Node.h"
#include "Population.h"

int main(int argc, char **argv){
	int processors, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processors);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// auto tree = getRandomTree();
	std::vector<std::shared_ptr<Node>> pop;
	pop.push_back(getRandomTree());
	pop.push_back(getRandomTree());
	Population population(pop, 0.5, 0.5);
	std::cout<<population.population[0]->eval(0.5, 0.5)<<std::endl;
	std::cout<<population.population[1]->eval(0.5, 0.5)<<std::endl;
	population.crossover(population.population[0], population.population[1]);
	std::cout<<population.population[0]->eval(0.5, 0.5)<<std::endl;
	std::cout<<population.population[1]->eval(0.5, 0.5)<<std::endl;
	// std::cout<<tree->eval(0.5)<<std::endl;

	MPI_Finalize();
}
