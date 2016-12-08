
#include "MyAlgorithm.h"

MyAlgorithm::MyAlgorithm(const Problem &pbm, const SetUpParams &setup): _setup{setup} {
	_solutions.reserve(_setup.population_size());
	for (int i = 0; i < _setup.population_size(); ++i) {
		Solution *s = new Solution(pbm);
		_solutions[i] = s;
	}
}

MyAlgorithm::~MyAlgorithm() {
	for (int i = 0; i < _setup.population_size(); ++i)
		delete _solutions[i];
}

/* ToFix
std::ostream& MyAlgorithm::operator<< (std::ostream& os, const MyAlgorithm& myAlgo) {
	//toDo
	return os;
}

std::istream& MyAlgorithm::operator>> (std::istream& is, MyAlgorithm& myAlgo) {
	//toDo
	return is;
}

MyAlgorithm& MyAlgorithm::operator= (const MyAlgorithm& myAlgo) {
	//toDo
	return myAlgo;
}
*/

const SetUpParams& MyAlgorithm::setup() const {
	return _setup;
}

void MyAlgorithm::initialize()
{
	for (int i = 0; i < _setup.population_size(); ++i)
        _solutions[i]->initialize();
}

void MyAlgorithm::evaluate() {
	_fitness_values.reserve(_setup.population_size());
	for (int i = 0; i < _setup.population_size(); ++i) {
		_fitness_values[i].fitness = _solutions[i]->fitness();
		_fitness_values[i].index = i;
	}
}

const std::vector<Solution*>& MyAlgorithm::solutions() const {
	return _solutions;
}

unsigned int MyAlgorithm::upper_cost() const {
	return _upper_cost;
}
		
unsigned int MyAlgorithm::lower_cost() const {
	return _lower_cost;
}

Solution& MyAlgorithm::solution(const unsigned int index) const {
	return *_solutions[index];
}
        
std::vector<struct particle>&  MyAlgorithm::fitness_values() {
	return _fitness_values;
}

double MyAlgorithm::fitness(const unsigned int index) const {
	return _fitness_values[index].fitness; //Pas sûr si on regarde l'index du tableau _fitness_values ou l'index du .index du struct
}

//Reste 5 méthodes à implémenter