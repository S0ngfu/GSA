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

MyAlgorithm::~MyAlgorithm() 
{
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

const SetUpParams& MyAlgorithm::setup() const 
{
	return _setup;
}

void MyAlgorithm::initialize()
{
	for (int i = 0; i < _setup.population_size(); ++i)
        _solutions[i]->initialize();
    _lower_cost = 0;
	_upper_cost = 29;
}

void MyAlgorithm::evaluate() 
{
	for (int i = 0; i < _setup.population_size(); ++i)
		_solutions[i]->fitness();
}

const std::vector<Solution*>& MyAlgorithm::solutions() const 
{
	return _solutions;
}

unsigned int MyAlgorithm::upper_cost() const 
{
	return _upper_cost;
}
		
unsigned int MyAlgorithm::lower_cost() const 
{
	return _lower_cost;
}

Solution& MyAlgorithm::solution(const unsigned int index) const 
{
	return *_solutions[index];
}

double MyAlgorithm::best_fitness() const
{
	return _solutions[_lower_cost]->get_fitness();
}

double MyAlgorithm::worst_fitness() const
{
	return _solutions[_upper_cost]->get_fitness();
}

Solution& MyAlgorithm::best_solution() const
{
	return *_solutions[_lower_cost];
}

Solution& MyAlgorithm::worst_solution() const
{
	return *_solutions[_upper_cost];
}

void MyAlgorithm::evolution(int iter)
{
	//Récupération de la meilleure fitness pour cette itération
	//IL FAUT CORRIGER UPPER/LOWER COST JE COMPRENDS PAS, IDA TG T NUL
    evaluate();
    quickSort(0, _setup.population_size());
    //Meilleurs individus K
    unsigned int kbest = kBest(iter, _setup.nb_evolution_steps());
    updateMass();
    reduceMass();
    updateAccel(iter, kbest);
    updatePosition();

    // VOIR https://www.researchgate.net/profile/Hossein_Nezamabadi-pour/publication/222853813_GSA_a_Gravitational_Search_Algorithm/links/0912f50645d730966a000000.pdf
    // PAGE 6

	//https://fr.mathworks.com/matlabcentral/fileexchange/27756-gravitational-search-algorithm--gsa-/content/Gravitational%20Search%20algorithm/GSA.m
}

void MyAlgorithm::main() 
{
    double moy_best_fit=0.0;
    double moy_worst_fit=0.0;
    std::cout<<"              best         worst"<<std::endl;
	for(int runs=0 ; runs < _setup.independent_runs() ; runs++)
	{
        initialize();
		for(int iter=0 ; iter < _setup.nb_evolution_steps() ; iter++)
		{
			evolution(iter);
			std::cout << "Evolution " << iter << " : " << best_fitness() << std::endl;
		}
		evaluate();

        std::cout<<"Execution "<<runs<<" : "<<best_fitness()<<" "<<worst_fitness()<<std::endl;

		moy_best_fit += best_fitness();//meilleure fitness de la solution (me souvient plus de la formule);
	    moy_worst_fit += worst_fitness();
    }
    moy_best_fit/=_setup.independent_runs();
    moy_worst_fit/=_setup.independent_runs();
    std::cout<<"Moyenne meilleures fitness : "<<moy_best_fit<<std::endl;
    std::cout<<"Moyenne pires fitness : "<<moy_worst_fit<<std::endl;
    //Affichage de la moyenne des meilleures fitness.
}

double MyAlgorithm::gUpdate(int iter, int max_iter) const
{
	const double g = 10;
    int alpha = 20;
	return (g * exp(-alpha * iter / max_iter));
}

void MyAlgorithm::updateAccel(int iter, unsigned int kbest)
{
    //Constante G
    double g = gUpdate(iter, _setup.nb_evolution_steps());

    for(int i = 0; i < _setup.population_size(); i++)
    {
        for (int j = 0; j < kbest; j++)
        	if(i != j)
                _solutions[i]->set_vecteuraccel(*_solutions[j], g);
    	_solutions[i]->normeVecteur();
	}
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
    double temp = _solutions[0]->get_mass();
    for(int i = 1; i < _setup.population_size(); i++)
        temp += _solutions[i]->get_mass();
    for(int i = 0; i < _setup.population_size(); i++)
        _solutions[i]->set_mass(_solutions[i]->get_mass() / temp);
}

void MyAlgorithm::updatePosition()
{
    for(int i = 0; i < _setup.population_size(); i++)
        _solutions[i]->moveSolution(0.5);
}

void MyAlgorithm::quickSort(int gauche, int droite)
{
	int r;
	if(gauche < droite) 
	{
		r = partition(gauche, droite);
		quickSort(gauche, r);
		quickSort(r+1, droite);
	}
}

int MyAlgorithm::partition(int gauche, int droite)
{   double x = _solutions[gauche]->get_fitness();
    int i = gauche;
	int j;
	for(j = gauche+1; j < droite; j++)
	if (_solutions[j]->get_fitness() <= x)
	{
		i = i+1;
		std::swap(_solutions[i], _solutions[j]);
	}
	std::swap(_solutions[i], _solutions[gauche]);
    return i;
}

unsigned int MyAlgorithm::kBest(int iter, int max_iter) const
{
	unsigned int k = _setup.population_size() - 5;
	return (unsigned int) (trunc((k * (max_iter - iter + 1) / (static_cast <double>(max_iter)) + 5)));
}
