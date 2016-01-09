/**
* Author: Fernando de Jesús Soto
* Date: 
*/
#include <vector>

#ifndef INHABITANT_H
#define INHABITANT_H

class Inhabitant
{
public:
	typedef std::vector<int> vi;
	Inhabitant(int size);
	Inhabitant();
	int operator[](int i);	//For easy access to genotype elements.
	//Getters & Setters
	vi getGenotype();
	void setGenotype(vi geno);
	double getCost();
	void setCost(double value);
	int getSize();
	void setGen(int g, int position);
	int getGen(int position);
	//Functions
	void printInhabitant();
	bool operator<(Inhabitant other);
private: 
	vi genotype;
	double cost;	//Cost of the path
	int g_size;		//genotype's length
};

#endif