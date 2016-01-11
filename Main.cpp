/**
* Author: Fernando de Jesús Soto
* Date: 
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <iostream>
#include <omp.h>
#include "Headers/Inhabitant.h"
#include "Headers/Population.h"
#include "Headers/Graph.h"
#include "Headers/Genetic_Operators.h"
#include "Headers/Simulated_Annealing.h"

#define chunk 5			//Number of iterations per thread
#define pop_size 200	//Number of inhabitants per generation

using namespace std;

typedef pair<double, double> coordinate;
typedef vector<coordinate> coordinates_list;
typedef vector<int> Path;
typedef pair<Path, double> Solution;


/*****Redirect input from a txt*****/
int main(int argc, char const *argv[])
{	
	srand(time(NULL));

	coordinates_list coordinates;	
	double x, y, mutation_prob;
	int cities_number, generations;

	//Reading coordinates of all the cities
	while(cin>>x>>y){
		coordinates.push_back(make_pair(x, y));
		if(cin.eof())
			break;
	}
	cities_number = coordinates.size();
	//Creating graph.
	Graph city(coordinates);

	//Creating first population.
	Population current_gen(pop_size);
	current_gen.beginPopulation(cities_number);
	//Setting total population cost.
	current_gen.setPopulationCost();
	//Printing first population
	//current_gen.printPopulation();
	
	//Body of Genetic Algorithm
	//For this example, our stop condition will be 200 generations.
	generations = 250;
	while (generations--) {
		Population next_gen(pop_size);
		//Genetic algorithms are highly parallel, that's why we're going to parallel this part
		#pragma omp parallel shared(next_gen)
		{
			#pragma omp for schedule(static, chunk) 
			for (int i = 0; i < pop_size; i+=2){
				
				/*******************This part defines selection********************/
				
				pair<Inhabitant, Inhabitant> parents;
				//For tournament selection, 5 is an arbitrary value.
				parents.first  = current_gen.tournamentSelection(5);
				parents.second = current_gen.tournamentSelection(5);

				/*******************This part defines crossover********************/

				//There isn't a crossover mutation, so, crossover will occur always.
				parents = Genetic_Operators::PMX(parents.first, parents.second);
				//After this point, our "parents" become into "offsprings".

				/*******************This part defines mutation*********************/

				//Mutation probability is defined arbitrary as 0.1.
				mutation_prob = 0.1;
				//Mutations for first offspring
				Genetic_Operators::exchangeMutation(&parents.first, mutation_prob);
				//Mutation for second offspring
				Genetic_Operators::exchangeMutation(&parents.second, mutation_prob);

				//Getting cost for both offsprings.
				parents.first.setCost(city.getPathCost(parents.first.getGenotype()));
				parents.second.setCost(city.getPathCost(parents.second.getGenotype()));

				/*******************This part defines replacement******************/
				next_gen.setInhabitant(parents.first, i);
				next_gen.setInhabitant(parents.second, i + 1);
			}

		}
		//With Elitism we save the fittest inhabitant of the current generation.
		/*As there exist the posibility that the whole new generation will be fitter than the best inhabitant of the old generation,
		if we tray 10 times without success of conserve the best inhabitant, then we're consider that it isn't fitter than any inhabitant
		of the new generation.
		*/
		Inhabitant fittest;
		fittest = current_gen.getFittest();
		int candidate;
		int oportunities;
		oportunities = 10;
		while (true) {
			oportunities--;
			candidate = rand() % 100;
			if (fittest.getCost() <= next_gen.getInhabitant(candidate).getCost()) {
				next_gen.setInhabitant(fittest, candidate);
				break;
			}
			if (!oportunities)
				break;
		}
		next_gen.setPopulationCost();
		//Making new generation the actual generation.
		current_gen = next_gen;
	}

	//current_gen.printPopulation();
	Inhabitant fittest = current_gen.getFittest();
	fittest.printInhabitant();
	
	/*****************************************Using simulated annealing*****************************************/
	cout << "\n\n";
	vector<int> vi;
	for (int i = 0; i < cities_number; i++)
		vi.push_back(i);
	for (int i = 0; i < cities_number; i++) {
		swap(vi[i], vi[i + (rand() % (cities_number - i))]);
	}
	Simulated_Annealing sa(vi);
	sa.cooling();
	sa.printHistoricalBestSolution();
	

 	return 0;
}