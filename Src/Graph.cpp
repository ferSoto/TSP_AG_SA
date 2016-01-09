/**
* Author: Fernando de Jesús Soto
*/

#include "../Headers/Graph.h"
#include <cmath>
#include <vector>

std::vector<std::vector<double>> Graph::distance_matrix;

Graph::Graph(coordinates_list coordinates){
	//Resizing cost matrix.
	Graph::distance_matrix.resize(coordinates.size());
	for(unsigned int i = 0; i < coordinates.size(); i++)
		Graph::distance_matrix[i].resize(coordinates.size());
	//Filling matrix
	for(unsigned int i = 0; i < coordinates.size(); i++){
		for (unsigned int j = i + 1; j < coordinates.size(); j++){
			Graph::distance_matrix[i][j] = Graph::distance_matrix[j][i] 
				= getDistance(coordinates[i], coordinates[j]);
		}
	}
}

Graph::Graph(){
	
}

//Returns euclidean distance between two points.
double Graph::getDistance(coordinate a, coordinate b){
	//sqrt((x1 -x2)^2 + (y1 - y2)^2)
	return sqrt(pow(a.first - b.first, 2.0) 
		+ pow(a.second - b.second, 2.0));
}


//Returns the distance (Cost) of the given path.
double Graph::getPathCost(std::vector<int> path){
	double cost = 0;
	for (unsigned int i = 0; i < path.size(); ++i){
		cost += Graph::distance_matrix[path[i]][path[(i+1) % path.size()]];
	}
	return cost;
}