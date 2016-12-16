//
// Created by Songfu on 24/11/2016.
//

#include "Solution.h"

Solution::Solution(const Problem& pbm) : _pbm{pbm}
{
	d_coord.resize(_pbm.dimension());
	_vecteuraccel.resize(_pbm.dimension());
    initialize();
}

Solution::Solution(const Solution& sol): _pbm{sol._pbm},
										 _current_fitness{sol._current_fitness}
{
	d_coord.resize(sol.d_coord.size());
	_vecteuraccel.resize(sol._vecteuraccel.size());
	d_coord = sol.d_coord;
    _mass = sol._mass;
    _vecteuraccel=sol._vecteuraccel;
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

void Solution::initialize()
{
	for (int i = 0; i < d_coord.size(); ++i)
	{
		d_coord[i] = (double) rand() / (double) RAND_MAX * (_pbm.UpperLimit - _pbm.LowerLimit) + _pbm.LowerLimit;
	}
 	_mass = 0;
    _vecteuraccel.reserve((unsigned long long int) _pbm.dimension());
}

void Solution::fitness() {
	_current_fitness=(_pbm.function())(d_coord);
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
		distance += pow(d_coord[i] - sol.d_coord[i],2);
	distance = sqrt(distance);
    return distance;
}

double Solution::get_mass() const {
	return _mass;
}

void Solution::set_mass(double mass) {
	_mass=mass;
}

void Solution::normeVecteur()
{
    double temp = 0;
    for(int i = 0; i < _pbm.dimension(); i++)
        temp += pow(_vecteuraccel[i], 2);
    temp = sqrt(temp);
    for(int i = 0; i < _pbm.dimension(); i++)
        _vecteuraccel[i] /= temp;
}

std::vector<double> Solution::get_vecteuraccel() const
{
    return _vecteuraccel;
}

void Solution::set_vecteuraccel(double accel, int position)
{
        _vecteuraccel[position] = accel;
}

void Solution::moveSolution(double duration)
{
    for(int i = 0; i < _pbm.dimension(); i++)
        d_coord[i] += _vecteuraccel[i] * pow(duration, 2);
}

