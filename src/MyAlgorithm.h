#ifndef INC_METAHEURISTIC
#define INC_METAHEURISTIC

#include "Solution.h"
#include "SetUpParams.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>


class MyAlgorithm
{
private:
	std::vector<Solution*> _solutions;     // individuals in population
	const SetUpParams& _setup;
	unsigned int _upper_cost,_lower_cost; // lower and upper fitness of individuals in population
	const double _mutationProbability;
	const double _crossoverProbability;

public:
	MyAlgorithm(const Problem& pbm,const SetUpParams& setup);
	~MyAlgorithm();

	//friend std::ostream& operator<< (std::ostream& os, const MyAlgorithm& myAlgo);
	//friend std::istream& operator>> (std::istream& is, MyAlgorithm& myAlgo);
	//MyAlgorithm& operator= (const MyAlgorithm& myAlgo);
	const SetUpParams& setup() const;
	void initialize();

	// creates a array with fitness of all solutions in MyAlgorithm and its position in the MyAlgorithm
	void evaluate();
	void updateCost();

	const std::vector<Solution*>& solutions() const;
	unsigned int upper_cost() const;
	unsigned int lower_cost() const;
	Solution& solution(const unsigned int index) const;
	double fitness(const unsigned int index) const;


	double best_fitness() const;
	double worst_fitness() const;
	Solution& best_solution() const;
	Solution& worst_solution() const;
	void evolution(int iter); /*makes an evolution step*/
	double g_update(int iter, int max_iter) const;


	void main();
};

#endif
