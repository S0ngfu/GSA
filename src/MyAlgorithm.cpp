
#include "MyAlgorithm.h"

MyAlgorithm::MyAlgorithm(const Problem &pbm, const SetUpParams &setup):
		_setup{setup},
		_mutationProbability{0.1},
		_crossoverProbability{0.5}
{
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
	for (int i = 0; i < _setup.population_size(); ++i)
		_solutions[i]->fitness();

	updateCost();
}


void MyAlgorithm::updateCost() {
	double min, max;
    min = max = _solutions[0]->get_fitness();
	for (unsigned int i = 1; i < _setup.population_size(); ++i) {
		double temp = _solutions[i]->get_fitness();
		if (temp < min) {
			min = temp;
			_lower_cost = i;
		}
		else if (temp > max) {
			max = temp;
			_upper_cost = i;
		}
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

double MyAlgorithm::fitness(const unsigned int index) const {
	return _solutions[index]->fitness();
}

double MyAlgorithm::best_fitness() const {
	return _solutions[_upper_cost]->get_fitness();
}

double MyAlgorithm::worst_fitness() const {
	return _solutions[_lower_cost]->get_fitness();
}

Solution& MyAlgorithm::best_solution() const {
	return *_solutions[_upper_cost];
}

Solution& MyAlgorithm::worst_solution() const {
	return *_solutions[_lower_cost];
}

void MyAlgorithm::evolution(int iter) {
	//Récupération de la meilleure fitness pour cette itération
	//IL FAUT CORRIGER UPPER/LOWER COST JE COMPRENDS PAS

    evaluate();
	//Constante G
	double g = g_update(iter, _setup.nb_evolution_steps());

    // VOIR https://www.researchgate.net/profile/Hossein_Nezamabadi-pour/publication/222853813_GSA_a_Gravitational_Search_Algorithm/links/0912f50645d730966a000000.pdf
    // PAGE 6

	//https://fr.mathworks.com/matlabcentral/fileexchange/27756-gravitational-search-algorithm--gsa-/content/Gravitational%20Search%20algorithm/GSA.m
}

void MyAlgorithm::main() {
    double moy_best_fit=0.0;
	for(int runs=0 ; runs < _setup.independent_runs() ; runs++)
	{
		initialize();
		for(int iter=0 ; iter < _setup.nb_evolution_steps() ; iter++)
		{
			evolution(iter);
		}
		evaluate();
        //ToDo : ceci est temporaire, il faut plus opti et faire une fonction dédié à cela
        double best_fit=100000;
        for(int i = 0 ; i < _setup.population_size() ; i++)
            if(best_fit > _solutions[i]->get_fitness())
                best_fit=_solutions[i]->get_fitness();
		moy_best_fit+= best_fit;//meilleure fitness de la solution (me souvient plus de la formule);
	}
    moy_best_fit/=_setup.independent_runs();
    std::cout<<"Moyenne : "<<moy_best_fit<<std::endl;
    //Affichage de la moyenne des meilleures fitness.
}

double MyAlgorithm::g_update(int iter, int max_iter) const {
	const double g=100;
    int alpha = 20;
	return g * exp(-alpha * (iter / max_iter));
}
