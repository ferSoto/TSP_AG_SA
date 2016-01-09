/**
* Author: Fernando de Jesús Soto
*/

#include <vector>
#include <cstdlib>

class Graph
{
public:
	typedef std::pair<double, double> coordinate;
	typedef std::vector<coordinate> coordinates_list;

	//Constructor
	//Receives a list of coordinates (X, Y)
	Graph(coordinates_list coordinates);
	Graph();
	//Receives a string of ints and returns the cost of the path
	//described in the string.
	double getPathCost(std::vector<int> path);

private:
	//Returns euclidean distance between two coordinates.
	double getDistance(coordinate a, coordinate b);
	static std::vector<std::vector<double>> distance_matrix;
	
};