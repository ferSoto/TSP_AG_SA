#include <algorithm>
#include <cmath>
#include <iostream>
#include "..\Headers\Simulated_Annealing.h"
#include "..\Headers\Graph.h"

typedef std::vector<int> Path;
typedef std::pair<Path, double> Solution;

Simulated_Annealing::Simulated_Annealing(Path path)
{
	this->current_best_solution = std::make_pair(path, city.getPathCost(path));
	historical_best_solution = current_best_solution;
	cooling_schedule = 7;
}

void Simulated_Annealing::cooling()
{
	//Setting up initial temperature.
	T = current_best_solution.first.size() * 10000;
	do {
		for (int i = 0; i < cooling_schedule; i++) {
			//Getting new solution in the neighborhood.
			candidate = newSolution(current_best_solution);
			//If the new solution is better than our current best solution, this new solution becomes our current best solution.
			//Otherwise, we eval new solution using metropolis step. If metropolis step returns true, the new solution becomes 
			//the current best solution.
			if (current_best_solution.second >= candidate.second) {
				current_best_solution = candidate;
			}
			else if(metropolisStep(current_best_solution.second, candidate.second)){
				current_best_solution = candidate;
			}
			//If our current best solution is better than the historical better solution, it becomes the new historical best solution.
			if (current_best_solution.second <= historical_best_solution.second)
				historical_best_solution = current_best_solution;
		}
		//Cooling temperature.
		T *= 0.9;
	} while (T > 0.1);
}

Solution Simulated_Annealing::getHistoricalBestSolution()
{
	return historical_best_solution;
}

//Prints historical best solution.
void Simulated_Annealing::printHistoricalBestSolution()
{
	for (int i : historical_best_solution.first) {
		std::cout << '-' << i;
	}
	std::cout << "\t\t= " << historical_best_solution.second;
}


//Returns a new solution in the neighborhood of the current best solution.
Solution Simulated_Annealing::newSolution(Solution solution)
{
	//Getting new solution in the neighborhood.
	for (int i = 0; i < solution.first.size() / 5; i++) {
		std::swap(solution.first[rand() % solution.first.size()], solution.first[rand() % solution.first.size()]);
		solution.second = city.getPathCost(solution.first);
	}
	return solution;
}

//Returns wheter a solution is accepted or not.
bool Simulated_Annealing::metropolisStep(double fx, double fx1)
{
	return exp(-1*(fx1-fx)/T) > rand()/RAND_MAX;
}
