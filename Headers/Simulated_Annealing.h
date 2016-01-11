#include <algorithm>
#include <vector>
#include "Graph.h"

#ifndef SIMULATED_ANNEALING
#define SIMULATED_ANNEALING

class Simulated_Annealing
{
public:
	typedef std::vector<int> Path;
	//First = Path, Second = Path cost.
	typedef std::pair<Path, double> Solution;

	Simulated_Annealing(Path path);
	
	//Cool the temperature while calculates solutions.
	void cooling();

	//Resturns the best solution found.
	Solution getHistoricalBestSolution();
	//Prints historical best solution.
	void printHistoricalBestSolution();

private:
	double T;							//Initial Temperature.
	int cooling_schedule;				//Number of iterations per temperature.
	Solution candidate;					//New solution in the neigborhood of another.
	Solution current_best_solution;		//Path with the best cost (distance).	
	Solution historical_best_solution;	//Best solution obtained.
	Graph city;							//Graph we work with.

	//Returns a new solution in the neighborhood of the current best solution.
	Solution newSolution(Solution solution);

	//Returns wheter a solution is accepted or not.
	bool metropolisStep(double fx, double fx1);
};

#endif
