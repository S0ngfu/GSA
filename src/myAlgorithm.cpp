#include "myAlgorithm.cpp"


myAlgorithm::myAlgorithm(const Problem& pbm,const SetUpParams& setup): _setup{setup} {
	_solutions.reserve(_setup.population_size());
	for (int i = 0; i < _setup.population_size(); ++i) {
		Solution *s = new Solution(pbm);
		_solutions[i] = s;
	}
}

myAlgorithm::~myAlgorithm() {
	for (int i = 0; i < _setup.population_size(); ++i)
		delete _solutions[i];
}

friend std::ostream& myAlgorithm::operator<< (std::ostream& os, const MyAlgorithm& myAlgo) {
	//toDo
	return os;
}

friend std::istream& myAlgorithm::operator>> (std::istream& is, MyAlgorithm& myAlgo) {
	//toDo
	return is;
}

MyAlgorithm& myAlgorithm::operator= (const MyAlgorithm& myAlgo) {
	//toDo
	return myAlgo;
}

const SetUpParams& myAlgorithm::setup() const {
	return _setup;
}

void myAlgorithm::initialize() {
	for (int i = 0; i < _setup.population_size(); ++i)
		_solutions[i].initialize();
}

void myAlgorithm::evaluate() {
	_fitness_values.reserve(_setup.population_size());
	for (int i = 0; i < _setup.population_size(); ++i) {
		_fitness_values[i].fitness = _solutions[i].fitness();
		_fitness_values[i].index = i;
	}
}

const std::vector<Solution*>& myAlgorithm::solutions() const {
	return _solutions;
}

unsigned int myAlgorithm::upper_cost() const {
	return _upper_cost;
}
		
unsigned int myAlgorithm::lower_cost() const {
	return _lower_cost;
}

Solution& myAlgorithm::solution(const unsigned int index) const {
	return _solutions[index];
}
        
std::vector<struct particle>&  myAlgorithm::fitness_values() {
	return _fitness_values;
}

double myAlgorithm::fitness(const unsigned int index) const {
	return _fitness_values[i].fitness; //Pas sûr si on regarde l'index du tableau _fitness_values ou l'index du .index du struct
}

//Reste 5 méthodes à implémenter