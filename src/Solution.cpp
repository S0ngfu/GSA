#include "Solution.h"

Solution::Solution(const Problem& pbm) : _pbm{pbm}
{
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

void Solution::initialize()
{
	d_coord.resize((unsigned long long int) _pbm.dimension());
	for (int i = 0; i < d_coord.size(); ++i)
	{
		d_coord[i] = (double) rand() / (double) RAND_MAX * (_pbm.UpperLimit - _pbm.LowerLimit) + _pbm.LowerLimit;
	}
 	_mass = 0;
    _vecteuraccel.resize((unsigned long long int) _pbm.dimension(),0);
    fitness();
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

std::vector<double>& Solution::get_coord() const
{
	return (std::vector<double>&) d_coord;
}


double Solution::position(const int index) {
    return d_coord[index];
}

double Solution::distEucl(const Solution& sol) const
{
	double distance = 0;
	for(int i = 0; i < d_coord.size(); ++i)
		distance += pow(d_coord[i] - sol.d_coord[i],2);
	distance = sqrt(distance);
    return distance;
}

double Solution::get_mass() const
{
	return _mass;
}

void Solution::set_mass(double mass) 
{
	_mass = mass;
}

void Solution::normeVecteur()
{
    double temp = 0;
    for(int i = 0; i < _vecteuraccel.size(); i++)
        temp += pow(_vecteuraccel[i], 2);
    if(temp != 0)
    {
    	temp = sqrt(temp);
    	for(int i = 0; i < _vecteuraccel.size(); i++)
        	_vecteuraccel[i] /= temp;
    }
}

void Solution::set_vecteuraccel(const Solution& sol, double g)
{
	if( _mass != 0)
        for(int i = 0 ; i < d_coord.size() ; i++)
        {
            double accel = gravitationalValue(sol, i, g);
            _vecteuraccel[i] += static_cast <double> (rand()) * static_cast <double> (RAND_MAX) * accel / _mass;
        }
}

void Solution::moveSolution(double duration)
{
    for(int i = 0; i < _pbm.dimension(); i++)
        d_coord[i] += _vecteuraccel[i] * pow(duration, 2);
}

double Solution::gravitationalValue(const Solution &sol, int i, double g) {
    double random = (double) rand() / (double) RAND_MAX;
    double temp = random * g * _mass * sol._mass * (sol.d_coord[i] - d_coord[i]) / distEucl(sol);
    return temp;
}

