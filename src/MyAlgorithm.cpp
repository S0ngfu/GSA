
#include "MyAlgorithm.h"

MyAlgorithm::MyAlgorithm(const Problem &pbm, const SetUpParams &setup):
		_setup{setup},
		_g{_g_const},
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
	_fitness_values.reserve(_setup.population_size());
	for (int i = 0; i < _setup.population_size(); ++i) {
		_fitness_values[i].fitness = _solutions[i]->fitness();
		_fitness_values[i].index = i;
	}

	_upper_cost = 0;
	_lower_cost = _setup.population_size() - 1;
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
	return _solutions[index]->fitness(); //Pas sûr si on regarde l'index du tableau _fitness_values ou l'index du .index du struct
}

double MyAlgorithm::best_cost() const {
	return _fitness_values[_upper_cost].fitness;
}
		
double MyAlgorithm::worst_cost() const {
	return _fitness_values[_lower_cost].fitness;
}

Solution& MyAlgorithm::best_solution() const {
	return *_solutions[_upper_cost];
}

Solution& MyAlgorithm::worst_solution() const {
	return *_solutions[_lower_cost];
}

void MyAlgorithm::evolution(int iter) {
	//Réduction constante gravitationnelle
	double alpha = 20;
	_g = _g_const * exp(-alpha * (iter / _setup.nb_evolution_steps()));

    /* CECI EST L'ALGO TEL QU'IL EST FAIT DANS LE PROBLEME DES CARTES
     * des modifs peuvent être nécessaires
     *
     * On tire deux individus de la pop au hasard
     * on compare leurs fitness (Winner/Loser)
     * on parcourt chaque valeur de la solution (toute sa dimension)
     * on tire à chaque fois des rand (entre 0 et 1)
     * si le rand est plus petit que la proba du crossover
     * la val du loser devient celle du winner
     * on tire un autre rand, si il est plus petit que la proba de la mutation
     * la val du loser mute
     *
     * si la fitness du loser devient parfaite, on arrête cette itération
     */

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
		moy_best_fit+=best_cost();
	}
    moy_best_fit/=_setup.independent_runs();
    std::cout<<"Moyenne : "<<moy_best_fit<<std::endl;
    //Affichage de la moyenne des meilleures fitness.
}
