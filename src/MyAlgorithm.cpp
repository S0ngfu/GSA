
#include "MyAlgorithm.h"

MyAlgorithm::MyAlgorithm(const Problem &pbm, const SetUpParams &setup):
		_setup{setup}
{
	_solutions.resize(_setup.population_size());
	for (int i = 0; i < _setup.population_size(); ++i) {
		Solution *s = new Solution(pbm);
		_solutions[i] = s;
	}
	evaluate();
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
    min = _solutions[0]->get_fitness();
	max = _solutions[0]->get_fitness();
	_lower_cost=0;
	_upper_cost=0;
	for (unsigned int i = 1; i < _setup.population_size(); i++)
	{
		double temp = _solutions[i]->get_fitness();
		if (temp <= min)
		{
			min = temp;
			_lower_cost = i;
		}
		else if (temp >= max)
		{
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

void MyAlgorithm::fitness(const unsigned int index) const {
	_solutions[index]->fitness();
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
	//IL FAUT CORRIGER UPPER/LOWER COST JE COMPRENDS PAS, IDA TG T NUL

    evaluate();
	//Constante G
	double g = g_update(iter, _setup.nb_evolution_steps());

    updateMass();
    reduceMass();
    updateaccel(g);
    updatePosition();

    // VOIR https://www.researchgate.net/profile/Hossein_Nezamabadi-pour/publication/222853813_GSA_a_Gravitational_Search_Algorithm/links/0912f50645d730966a000000.pdf
    // PAGE 6

	//https://fr.mathworks.com/matlabcentral/fileexchange/27756-gravitational-search-algorithm--gsa-/content/Gravitational%20Search%20algorithm/GSA.m
}

void MyAlgorithm::main() {
    double moy_best_fit=0.0;
    double moy_worst_fit=0.0;
    std::cout<<"          best      worst"<<std::endl;
	for(int runs=0 ; runs < _setup.independent_runs() ; runs++)
	{
        initialize();
		for(int iter=0 ; iter < _setup.nb_evolution_steps() ; iter++)
		{
			evolution(iter);

		}
		evaluate();

        std::cout<<"Execution "<<runs<<" : "<<best_fitness()<<" "<<worst_fitness()<<std::endl;

		moy_best_fit+= best_fitness();//meilleure fitness de la solution (me souvient plus de la formule);
	    moy_worst_fit+=worst_fitness();
    }
    moy_best_fit/=_setup.independent_runs();
    moy_worst_fit/=_setup.independent_runs();
    std::cout<<"Moyenne meilleures fitness : "<<moy_best_fit<<std::endl;
    std::cout<<"Moyenne pires fitness : "<<moy_worst_fit<<std::endl;
    //Affichage de la moyenne des meilleures fitness.
}

double MyAlgorithm::g_update(int iter, int max_iter) const {
	const double g=100;
    int alpha = 20;
	return g * exp(-alpha * (iter / max_iter));
}

void MyAlgorithm::updateaccel(double g)
{
    for(int i = 0; i < _setup.population_size(); i++)
    {
        for (int j = 0; j < _setup.population_size(); j++)
            if(i != j)
                for(int k = 0; k < _setup.solution_size(); k++)
                    _solutions[i]->set_vecteuraccel(gravitationalValue(*_solutions[i], *_solutions[j], k, g), k);
    }
}

double MyAlgorithm::gravitationalValue(const Solution &sol1, const Solution &sol2, int i, double g)
{
    double temp;
    double random = rand() / RAND_MAX;
    temp = random * g * sol2.get_mass() * (sol2.solution()[i] - sol1.solution()[i]) / sol1.distEucl(sol2);
    return temp;
}

void MyAlgorithm::updateMass()
{
    double best_fit = best_fitness();
    double worst_fit = worst_fitness();
    for(int i = 0; i < _setup.population_size(); i++)
        _solutions[i]->set_mass((_solutions[i]->get_fitness() - worst_fit) / (best_fit - worst_fit));
}

void MyAlgorithm::reduceMass()
{
    double temp = 0;
    for(int i = 0; i < _setup.population_size(); i++)
        temp += _solutions[i]->get_mass();
    for(int i = 0; i < _setup.population_size(); i++)
        _solutions[i]->set_mass(_solutions[i]->get_mass() / temp);
}

void MyAlgorithm::updatePosition()
{
    for(int i = 0; i < _setup.population_size(); i++)
        _solutions[i]->moveSolution(1);
}
