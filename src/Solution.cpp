//
// Created by Songfu on 24/11/2016.
//

#include "Solution.h"

Solution::Solution(const Problem& pbm) : _pbm{pbm} {}

Solution::Solution(const Solution& sol): _pbm{sol.pbm()} {
	d_coord.reserve(sol.solution().size());
	std::vector<double>& vecSol = sol.solution();
	for (int i = 0; i < vecSol.size(); ++i)
		d_coord[i] = vecSol[i];
}

friend std::ostream& operator<< (std::ostream& os, const Solution& sol) {
	//toDo
	os<<"Le problème lié à la solution est : "<<sol.pbm()<<""<<std::endl;
	return os;
}
    
friend std::istream& operator>> (std::istream& is, Solution& sol) {
	//toDo

	return is;
}

const Problem& pbm() const {
	return &_pbm;
}

Solution& operator=  (const Solution& sol) {
	//toDo
}

bool operator== (const Solution& sol) const {
	//toDo
}

bool operator!= (const Solution& sol) const {
	//toDo
}

void initialize() {
	srand(time(NULL));
	for (int i = 0; i < _solution.size(); ++i) 
		_solution[i] = rand() % (upperLimit - lowerLimit) + lowerLimit;
 	_mass = rand() / RAND_MAX;
}

double fitness() {
	int sum = 0;
	for (int i = 0; i < _solution.size() / 2; ++i) {
		sum += 100 * pow((pow(_solution[2*i], 2) - _solution[2*i+1]), 2) + pow(_solution[2*i] - 1, 2);
	}
	_current_fitness = sum;
}

double get_fitness() {
	return _current_fitness;
}

unsigned int size() const {
	return _solution.size();
}

std::vector<double>& solution() {
	return &_solution;
}

double& position(const int index) { //retournera une position du tableau d_coord

}

void position(const int index, const double value);