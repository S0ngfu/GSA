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

const Problem& Solution::pbm() const {
	return _pbm;
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

void Solution::initialize() {
	srand(time(NULL));
	for (int i = 0; i < d_coord.size(); ++i) 
		d_coord[i] = rand() % (upperLimit - lowerLimit) + lowerLimit;
 	_mass = rand() / RAND_MAX;
}

double Solution::fitness() {
	int sum = 0;
	for (int i = 0; i < d_coord.size() / 2; ++i) {
		sum += 100 * pow((pow(d_coord[2*i], 2) - d_coord[2*i+1]), 2) + pow(d_coord[2*i] - 1, 2);
	}
	_current_fitness = sum;
}

double Solution::get_fitness() {
	return _current_fitness;
}

unsigned int Solution::size() const {
	return d_coord.size();
}

std::vector<double>& Solution::solution() {
	return &d_coord;
}

double& Solution::position(const int index) { //retournera une position du tableau d_coord

}

void Solution::position(const int index, const double value);

double Solution::distEucl(const Solution& sol) const
{
	double distance = 0;
	for(int i = 0; i < d_coord.size(); ++i)
	{
		distance += sqrt(pow(d_coord[i] - sol.d_coord[i], 2));
	}
}
