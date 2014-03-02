#include "Population.h"
#include <mpi.h>

extern int processors;
extern int rank;

Population::Population(int popSize, double crossoverRate, double mutateRate)
	:population(popSize)
	,crossoverRate(crossoverRate)
	,mutateRate(mutateRate)
	,rng(time(NULL))
	,dist(0, 1)
	,best(std::numeric_limits<float>::max(), "")
{
	std::generate(population.begin(), population.end(), [&](){return std::make_pair(0.0, getRandomTree());});
}

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

void Population::score(std::vector<std::tuple<int, int, int>> &points, std::pair<float, std::shared_ptr<Node>> &tree){
	double error = 0.0;
	for(auto &point : points){
		error += abs(tree.second->eval(std::get<0>(point), std::get<1>(point)) - std::get<2>(point));
	}
	tree.first = error;
}

void Population::doGeneration(std::vector<std::tuple<int, int, int>> &points){
	std::vector<std::pair<float, std::shared_ptr<Node>>> newPop;
	for(auto &func : population){
		score(points, func);
	}
	std::sort(population.begin(), population.end());
	if(population[0].first < best.first){
		best = std::make_pair(population[0].first, serializeTree(population[0].second));
	}
	for(int i = 0; i < population.size() - 1; i += 2){
		crossover(population[i].second, population[i + 1].second);
		mutate(population[i].second);
		mutate(population[i + 1].second);
		newPop.push_back(std::make_pair(0.0, population[i].second));
		newPop.push_back(std::make_pair(0.0, population[i + 1].second));
	}
	migrate(newPop);
	population = newPop;
}

void Population::migrate(std::vector<std::pair<float, std::shared_ptr<Node>>> &newPop){
	std::uniform_real_distribution<double> migrateDist(0, 1);
	int next = (rank + 1) % processors;
	int prev = (rank - 1 < 0) ? processors - 1 : rank - 1;
	std::vector<std::pair<float, std::shared_ptr<Node>>> tempPop;
	if(rank % 2 == 0){
		for(int i = 0; i < newPop.size() / 10; ++i){
			int index = migrateDist(rng) * newPop.size();
			auto treeString = serializeTree(newPop[index].second);
			int size = treeString.length();
			MPI_Send(&size, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
			MPI_Send(&treeString[0], treeString.length(), MPI_CHAR, next, 0, MPI_COMM_WORLD);
		}
		for(int i = 0; i < newPop.size() / 10; ++i){
			int size = 0;
			MPI_Recv(&size, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::string temp;
			temp.resize(size);
			MPI_Recv(&temp[0], size, MPI_CHAR, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::stringstream stream(temp);
			tempPop.push_back(std::make_pair(0.0, deserializeTree(stream)));
		}	
	}
	else{
		for(int i = 0; i < newPop.size() / 10; ++i){
			int size = 0;
			MPI_Recv(&size, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::string temp;
			temp.resize(size);
			MPI_Recv(&temp[0], size, MPI_CHAR, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::stringstream stream(temp);
			tempPop.push_back(std::make_pair(0.0, deserializeTree(stream)));
		}
		for(int i = 0; i < newPop.size() / 10; ++i){
			int index = migrateDist(rng) * newPop.size();
			auto treeString = serializeTree(newPop[index].second);
			int size = treeString.length();
			MPI_Send(&size, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
			MPI_Send(&treeString[0], treeString.length(), MPI_CHAR, next, 0, MPI_COMM_WORLD);
		}	
	}
	for(auto &thing : tempPop){
		newPop.push_back(thing);
	}
}
