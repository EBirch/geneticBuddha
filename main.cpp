#include <mpi.h>
#include <iostream>
#include <fstream>
#include "Node.h"
#include "Population.h"

int processors, rank;

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processors);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	// std::cout<<"Rank: "<<rank<<" of "<<processors<<std::endl;

	Population pop(20, 0.5, 0.01);
	pop.doGeneration();
	// pop.doGeneration();
	// std::cout<<pop.population[0].second->eval(0.5, 0.5)<<std::endl;
	// auto what = serializeTree(pop.population[0].second);
	// // std::string what = "1 0 1 1 1 1 2 1 0 1 5.577634 2 0 0 1 9.495168 0 0 -6.201732 ";
	// std::stringstream haha(what);
	// auto hope = deserializeTree(haha);
	// std::cout<<hope->eval(0.5, 0.5)<<std::endl;
	// std::cout<<what<<std::endl;
	//-0.912277

	MPI_Finalize();
}
