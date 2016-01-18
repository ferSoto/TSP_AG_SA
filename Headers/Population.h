/**
* Author: Fernando de Jesús Soto
* Date: 
*/
#include <vector>
#include <algorithm>
#include "Inhabitant.h"

#ifndef POPULATION_H
#define POPULATION_H


 class Population
 {
 public:
 	typedef std::vector<Inhabitant> vh;
 	Population(int size);
 	//Getters & Setters
 	int getSize();
 	Inhabitant getInhabitant(int position);
 	void setInhabitant(Inhabitant h, int position);
 	double getPopulationCost();
 	void setPopulationCost();
 	//Functions
 	void printPopulation();
 	void beginPopulation(int genotype_size);
	Inhabitant tournamentSelection(int k);		//Returns the best of the k selected elements.
	Inhabitant rouletteRankingSelection();		//Returns an inhabitant based on its ranking in the population.
	Inhabitant getFittest();					//Returns the fittest element of the population.
 private:
 	vh inhabitant;
 	double population_cost;
 	int p_size;		//Size of the population
	bool is_sorted;

 };

 #endif