/**
* Author: Fernando de Jesús Soto
* Date: 
*/
#include "../Headers/Inhabitant.h"
#include <cstdio>

typedef std::vector<int> vi;
//Constructor and destructor

//Private Functions

//Getters & Setters
vi Inhabitant::getGenotype(){
	return genotype;
}

void Inhabitant::setGenotype(vi geno){
	genotype = geno;
	g_size = genotype.size();
}

double Inhabitant::getCost(){
	return cost;
}

void Inhabitant::setCost(double value){
	cost = value;
}

int Inhabitant::getSize(){
	return g_size;
}

void Inhabitant::setGen(int g, int position){
	genotype.at(position) = g;
}

int Inhabitant::getGen(int position){
	return genotype.at(position);
}

Inhabitant::Inhabitant(int size)
{
	genotype.resize(size);
	g_size = size;
}

Inhabitant::Inhabitant()
{
}

//Operator
int Inhabitant::operator[](int i){
	return this->genotype.at(i);
}

//Public Functions

void Inhabitant::printInhabitant(){
	for (auto i : genotype){
		if(i < 10)
			printf("-0%d", i);
		else
			printf("-%d", i);
	}
	printf("\t\t= %.3lf\n", cost);
}

bool Inhabitant::operator<(Inhabitant other)
{
	return cost < other.getCost();
}
