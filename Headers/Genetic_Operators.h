/**
* Author: Fernando de Jesús Soto
* Date: 
*/
#include "Inhabitant.h"

#ifndef GENETIC_OPERATORS_H
#define GENETIC_OPERATORS_H

class Genetic_Operators
{
public:
	typedef std::pair<Inhabitant,Inhabitant> phh;
	typedef std::vector<int> vi;
	//Partially Matched Crossover
	static phh PMX(Inhabitant father, Inhabitant mother);
	//Mutation
	static void exchangeMutation(Inhabitant* h, double probability);
private:
	//Used in PMX
	static bool belongs(int s, vi S);
};

#endif