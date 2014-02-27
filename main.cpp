#include <mpi.h>
#include <iostream>
#include <vector>
#include <random>
#include "Node.h"

int main(int argc, char **argv){
	int processors, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processors);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Finalize();
}