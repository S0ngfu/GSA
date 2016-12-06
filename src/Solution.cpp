//
// Created by Songfu on 24/11/2016.
//

#include "Solution.h"

Solution::Solution(const Problem& pbm) : _pbm{pbm} {}

Solution::Solution(const Solution& sol): _pbm{sol.pbm()},
										 _current_fitness{sol.get_fitness()}
{
	d_coord.reserve(sol.solution().size());
	std::vector<double>& vecSol = sol.solution();
	for (int i = 0; i < vecSol.size(); ++i)
		d_coord[i] = vecSol[i];
}

friend std::ostream& Solution::operator<< (std::ostream& os, const Solution& sol) {
	//toDo

	return os;
}
    
friend std::istream& Solution::operator>> (std::istream& is, Solution& sol) {
	//toDo

	return is;
}

const Problem& Solution::pbm() const {
	return _pbm;
}

/*bool operator== (const Solution& sol) const {
	//toDo

}

bool operator!= (const Solution& sol) const {
	//toDo
}*/

void Solution::initialize() {
	srand(time(localtime));
	for (int i = 0; i < d_coord.size(); ++i) 
		d_coord[i] = rand() % static_cast<int>((_pbm.UpperLimit - _pbm.LowerLimit)) + _pbm.LowerLimit;

	srand(time(localtime));
	for (int i = 0; i < d_coord.size(); ++i)
		d_coord[i] = rand() % (static_cast<int>(_pbm.UpperLimit - _pbm.LowerLimit)) + _pbm.LowerLimit;

 	_mass = rand() / RAND_MAX;
}

double Solution::fitness() {
	int sum = 0;
	for (int i = 0; i < d_coord.size() / 2; ++i) {
		sum += 100 * pow((pow(d_coord[2*i], 2) - d_coord[2*i+1]), 2) + pow(d_coord[2*i] - 1, 2);
	}
	_current_fitness = sum;
    return _current_fitness;
}

double Solution::get_fitness() const {
	return _current_fitness;
}

unsigned int Solution::size() const {
	return static_cast<unsigned int>(d_coord.size());
}

std::vector<double>& Solution::solution() const{
	return d_coord;
}

double& Solution::position(const int index) { //retournera une position du tableau d_coord
	return d_coord[index];
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

void Solution::position(const int index, const double value) {
	d_coord[index]=value;
}

