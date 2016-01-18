/**
* Author: Fernando de Jesús Soto
* Date: 
*/

#include <cstdio>
#include <algorithm>
#include <omp.h>
#include "../Headers/Population.h"
#include "../Headers/Inhabitant.h"
#include "../Headers/Graph.h"

typedef std::vector<Inhabitant> vh;
typedef std::vector<int> vi;

//Constructor
Population::Population(int size){
	inhabitant.resize(size);
	p_size = size;
	is_sorted = false;
}

//Private functions


//Getters & Setters
int Population::getSize(){ //return size of population
	return p_size;
}

Inhabitant Population::getInhabitant(int position){ //Return an Inhabitant from one position
	return this->inhabitant[position];
}

void Population::setInhabitant(Inhabitant h, int position){ //Put an Inhabitant in his position
	inhabitant.at(position) = h;
}

double Population::getPopulationCost(){
	return population_cost;	
}

void Population::setPopulationCost(){
	double sum = 0;
	#pragma omp parallel shared(sum) 
	{
		#pragma omp for schedule(static, 2)
		for(int i = 0; i < p_size; i++){
			#pragma omp critical
			sum += inhabitant[i].getCost();
		}
	}
	this->population_cost = sum;
}

//Public functions


void Population::printPopulation(){
	for (int i = 0; i < p_size; ++i){
		inhabitant.at(i).printInhabitant();
	}
	printf("Population cost = %lf\n", population_cost);
}

void Population::beginPopulation(int genotype_size){
	//Creating first inhabitant of the population.
	vi new_path;
	Graph sameGraph;
	new_path.resize(genotype_size);
	for(int i = 0; i < genotype_size; i++)
		new_path[i] = i;
	this->inhabitant[0].setGenotype(new_path);
	this->inhabitant[0].setCost(sameGraph.getPathCost(new_path));
	//Based in the first element, we're going to create the others inhabitants
	//To do this, we're going to use a variant of Knuth Algorithm
	for(int i = 1; i < this->p_size; i++){
		//Each new inhabitant is based in its predecessor.
		for(int j = 0; j < genotype_size; j++){
			std::swap(new_path[j], new_path[j + rand() % (genotype_size - j)]);
		}
		this->inhabitant[i].setGenotype(new_path);
		this->inhabitant[i].setCost(sameGraph.getPathCost(new_path));
	}
}

//Return the best inhabitant of the k selected.
Inhabitant Population::tournamentSelection(int k)
{
	int fittest;
	fittest = rand() % 100;
	for (int i = 1; i < k; i++)
	{
		int candidate = rand() % 100;
		fittest = (this->inhabitant[fittest].getCost() <= this->inhabitant[candidate].getCost() ? fittest : candidate);
	}
	
	return this->inhabitant[fittest];
}

//Return an inhabitant based on its ranking in the population.
Inhabitant Population::rouletteRankingSelection()
{
	int current_inhabitant;
	long sum, bar;
	if (!is_sorted) {
		std::sort(inhabitant.begin(), inhabitant.end());
		is_sorted = true;
	}
	bar = rand() % (long)population_cost;
	current_inhabitant = 0;
	sum = 0;
	while (sum < bar)
	{
		current_inhabitant++;
		sum += (long)inhabitant[p_size - current_inhabitant].getCost();
	}
	return inhabitant[p_size -  current_inhabitant];
}

//Return the fittest inhabitant of the population.
Inhabitant Population::getFittest()	
{
	if (!is_sorted) {
		std::sort(inhabitant.begin(), inhabitant.end());
		is_sorted = true;
	}
	return this->inhabitant[0];
}
