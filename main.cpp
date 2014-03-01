#include <mpi.h>
#include <iostream>
#include "Node.h"
#include "Population.h"

int main(int argc, char **argv){
	int processors, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processors);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	Population pop(20, 0.5, 0.01);

	MPI_Finalize();
}
