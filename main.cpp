#include <mpi.h>
#include <iostream>
#include <fstream>
#include <tuple>
#include "Node.h"
#include "Population.h"

int processors, rank;

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processors);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	std::fstream file("./image.ppm");
	std::vector<std::tuple<int, int, int>> points;
	std::string temp;
	std::getline(file, temp);
	int width = 0;
	int height = 0;
	int depth = 0;
	file >> width >> height >> depth;
	for(int j = 0; j < height; ++j){
		for(int i = 0; i < width; ++i){
			int val;
			file >> val >> val >> val;
			points.push_back(std::make_tuple(i, j, val));
		}
	}
	file.close();

	Population pop(10, 0.5, 0.01);
	for(int i = 0; i < 5; ++i){
		pop.doGeneration(points);
	}
	std::vector<std::pair<float, std::shared_ptr<Node>>> bestResults;
	if(rank == 0){
		for(int i = 1; i < processors; ++i){
			int size = 0;
			MPI_Recv(&size, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::string temp;
			temp.resize(size);
			MPI_Recv(&temp[0], size, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::stringstream stream(temp);
			std::pair<float, std::shared_ptr<Node>> tree = std::make_pair(0.0, deserializeTree(stream));
			pop.score(points, tree);
			bestResults.push_back(tree);
		}
	}
	else{
		int size = pop.best.second.length();
		MPI_Send(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(&pop.best.second[0], pop.best.second.length(), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}

	if(rank == 0){
		std::sort(bestResults.begin(), bestResults.end());
		std::ofstream out("./doneImage.ppm");
		out << "P2" << std::endl << width << " " << height << std::endl << depth << std::endl;
		for(auto &point : points){
			int val = bestResults[0].second->eval(std::get<0>(point), std::get<1>(point));
			out << val << " " << val << " " << val << " ";
		}
		out.close();
	}

	MPI_Finalize();
}
