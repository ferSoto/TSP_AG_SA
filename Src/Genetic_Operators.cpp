/**
* Author: Fernando de Jesús Soto
* Date: 
*/
#include "../Headers/Genetic_Operators.h"
#include <cstdlib>
#include <queue>
#include <algorithm>

typedef std::pair<int,int> pii;
typedef std::pair<Inhabitant,Inhabitant> phh;
typedef std::queue<int> qi;
typedef std::vector<int> vi;
typedef unsigned int ui;

//Check if an element s belongs to the set S.
bool Genetic_Operators::belongs(int s, vi S){
	vi::iterator it;
	for (it = S.begin(); it != S.end(); it++)
		if(s == *it)
			return true;
	return false;
}

//Partially Matched Crossover
phh Genetic_Operators::PMX(Inhabitant father, Inhabitant mother){
	phh sons = std::make_pair(Inhabitant(father.getSize()), Inhabitant(father.getSize()));
	pii x_points, temp_pair;		//Crossover points
	qi nx_father, nx_mother; 	//no-crossover elements for each Inhabitant.
	
	//Choosing crossover points.
	temp_pair.first = rand() % mother.getSize();
	temp_pair.second = rand() % mother.getSize();
	x_points.first = std::min(temp_pair.first, temp_pair.second);
	x_points.second = std::max(temp_pair.first, temp_pair.second);
	
	vi x_mother, x_father;
	for (int i = x_points.first; i <= x_points.second; i++) {
		x_mother.push_back(mother[i]);
		x_father.push_back(father[i]);
	}

	//If element i from father and mother (respectively) doesn't belongs 
	//to the elements to cross, put them in their queue.
	for(int i = 0; i < father.getSize(); i++){
		if(!belongs(father[i], x_mother))
			nx_father.push(father[i]);
		if(!belongs(mother[i], x_father))
			nx_mother.push(mother[i]);
	}

	/***************************************************************************************************************************************/
	//Doing the crossover and creating new Inhabitants.
	for (int i = 0; i < father.getSize(); ++i){
		if ( i < x_points.first || i > x_points.second){
			sons.first.setGen(i, nx_father.front());
			sons.second.setGen(i, nx_mother.front());
			nx_mother.pop();
			nx_father.pop();
		}else{
			sons.first.setGen(i, x_mother.at(i - x_points.first));
			sons.second.setGen(i, x_father.at(i - x_points.first));
		}
	}
	return sons;
}

//Probability goes between [0,1]
void Genetic_Operators::exchangeMutation(Inhabitant* h, double probability){
	for (int i = 0; i < h->getSize(); ++i){
		if((double)rand()/RAND_MAX < probability){ 	//Mutation for son 1
			//swapping positions
			int aux_var, aux_pos;
			aux_var = h->getGen(i);
			aux_pos = rand()%h->getSize();
			h->setGen(h->getGen(aux_pos), i);
			h->setGen(aux_var, aux_pos);
		}
	}
}