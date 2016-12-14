//
// Created by Songfu on 24/11/2016.
//

#include "Solution.h"

Solution::Solution(const Problem& pbm) : _pbm{pbm} {}

Solution::Solution(const Solution& sol): _pbm{sol._pbm},
										 _current_fitness{sol._current_fitness}
{
	d_coord.reserve(sol.d_coord.size());
	d_coord = sol.d_coord;
}

/*
std::ostream& Solution::operator<< (std::ostream& os, const Solution& sol) {
	//toDo

	return os;
}
    
std::istream& Solution::operator>> (std::istream& is, Solution& sol) {
	//toDo

	return is;
}
*/

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
	srand((unsigned int) time(NULL));
	for (int i = 0; i < d_coord.size(); ++i) 
		d_coord[i] = rand() % static_cast<int>((_pbm.UpperLimit - _pbm.LowerLimit)) + _pbm.LowerLimit;

 	_mass = rand() / RAND_MAX;
}

double Solution::fitness() {
	//ToDo
	_current_fitness=(_pbm.function())(solution());
}

double Solution::get_fitness() const {
	return _current_fitness;
}

unsigned int Solution::size() const {
	return static_cast<unsigned int>(d_coord.size());
}

std::vector<double>& Solution::solution() const
{
	return (std::vector<double>&) d_coord;
}

double& Solution::position(const int index) //retournera une position du tableau d_coord
{
	return d_coord[index];
}

void Solution::position(const int index, const double value) {
    d_coord[index]=value;
}

double Solution::distEucl(const Solution& sol) const
{
	double distance = 0;
	for(int i = 0; i < d_coord.size(); ++i)
		distance += sqrt(pow(d_coord[i],2) - pow(sol.d_coord[i],2));
}

double Solution::get_accel() const {
	return _accel;
}

void Solution::set_accel(double accel) {
	_accel=accel;
}

double Solution::get_mass() const {
	return _mass;
}

void Solution::set_mass(double mass) {
	_mass=mass;
}
