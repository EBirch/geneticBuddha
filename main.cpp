#include <mpi.h>
#include <iostream>
#include "Node.h"

int main(int argc, char **argv){
	int processors, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processors);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	auto tree = getRandomTree();
	std::cout<<tree->eval(1)<<std::endl;

	MPI_Finalize();
}
