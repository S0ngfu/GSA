#include "MyAlgorithm.h"

MyAlgorithm::MyAlgorithm(const Problem &pbm, const SetUpParams &setup):
		_setup{setup},
		_mutationProbability{0.1},
		_crossoverProbability{0.5}
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
    evaluate();
    quickSort(0, _setup.population_size());

    //Meilleurs individus K
    unsigned int kbest = kBest(iter, _setup.nb_evolution_steps());
	crossoverAndMutation(kbest);
    updateMass();
    reduceMass();
    updateAccel(iter, kbest);
    updatePosition();
}

void MyAlgorithm::main() 
{
    double moy_best_fit = 0.0;
    double moy_worst_fit = 0.0;
    std::cout << "\t\tbest\tworst" << std::endl;
	for(int runs = 0; runs < _setup.independent_runs(); runs++)
	{
        initialize();
		double best_fit = best_fitness(), worst_fit = worst_fitness();
		for(int iter = 0 ; iter < _setup.nb_evolution_steps(); iter++)
		{
			evolution(iter);
			if(best_fitness() < best_fit)
			{
				best_fit = best_fitness();
				worst_fit = worst_fitness();
			}
		}
		evaluate();
		if(best_fitness() < best_fit)
		{
			best_fit = best_fitness();
			worst_fit = worst_fitness();
		}
        std::cout<<"Execution "<<runs+1<<" : "<<best_fit<<"\t"<<worst_fit<<std::endl;

		moy_best_fit += best_fit;
	    moy_worst_fit += worst_fit;
    }
    moy_best_fit /= _setup.independent_runs();
    moy_worst_fit /= _setup.independent_runs();

	//Affichage de la moyenne des meilleures fitness.
    std::cout << "\nMoyenne meilleures fitness : " << moy_best_fit << std::endl;
    std::cout << "Moyenne pires fitness : " << moy_worst_fit << std::endl;
}

double MyAlgorithm::gUpdate(int iter, int max_iter) const
{
	const double g = 10;
    int alpha = 20;
	return (g * exp(-alpha * iter / max_iter));
}

void MyAlgorithm::updateAccel(int iter, unsigned int kbest)
{
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
        _solutions[i]->moveSolution(1);
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

void MyAlgorithm::crossoverAndMutation(unsigned int kbest) {
	for(int i = kbest ; i < _solutions.size() ; i++)
	{
		int random = rand() % kbest;

		for(int j = 0 ; j < _setup.solution_size() ; j++)
		{
			if((double) rand() / (double) RAND_MAX < _crossoverProbability)
			{
				//double temp = _solutions[random]->position(j);
				std::swap(_solutions[random]->get_coord()[j],_solutions[i]->get_coord()[j]);
				//_solutions[i]->get_coord()[j] = _solutions[random]->get_coord()[j];
			}
			if((double) rand() / (double) RAND_MAX < _mutationProbability)
			{
				Problem prob = _solutions[i]->pbm();
				_solutions[i]->get_coord()[j] = (double) rand() / (double) RAND_MAX * (prob.UpperLimit - prob.LowerLimit) + prob.LowerLimit;;
			}
		}
	}
}
