#ifndef INC_METAHEURISTIC
#define INC_METAHEURISTIC

///
/// \file MyAlgorithm.h
/// \brief Implémentation du GSA (Gravitational Search Algorithm)

#include "Solution.h"
#include "SetUpParams.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

///
/// \class MyAlgorithm
/// \brief Classe implémentant l'algorithme GSA
class MyAlgorithm
{
private:
	std::vector<Solution*> _solutions;     // individuals in population
	const SetUpParams& _setup;
	unsigned int _upper_cost,_lower_cost; // lower and upper fitness of individuals in population

public:

	///
	/// \brief Constructeur
	/// \param[in] pbm : Problème que doit résoudre l'algorithme
	/// \param[in] setup : Paramètres de l'algorithme
	MyAlgorithm(const Problem& pbm,const SetUpParams& setup);

	///
	/// \brief Destructeur
	/// Destructeur de la classe MyAlgorithm
	~MyAlgorithm();

	//friend std::ostream& operator<< (std::ostream& os, const MyAlgorithm& myAlgo);
	//friend std::istream& operator>> (std::istream& is, MyAlgorithm& myAlgo);

	///
	/// \brief Renvoi l'objet de la classe SetUpParams
	/// \return SetUpParams
	const SetUpParams& setup() const;

	///
	/// \brief Initialise la population de solution
	void initialize();

	///
	/// \brief Évalue la fitness de chaque solution de la population
	void evaluate();

	///
	/// \brief Met à jour la masse de chaque solution de la population
    void updateMass();

	///
	/// \brief Relativise la masse de chaque solution de la population
    void reduceMass();

	///
	/// \brief Met à jour la position de chaque solution de la population
    void updatePosition();

	///
	/// \brief Retourne la population
	/// \return Tableau de pointeurs de solutions
	const std::vector<Solution*>& solutions() const;

	///
	/// \brief Retourne l'indice de la solution ayant la plus grande fitness
	/// \return Indice de la solution
	unsigned int upper_cost() const;

	///
	/// \brief Retourne l'indice de la solution ayant la plus petite fitness
	/// \return Indice de la solution
	unsigned int lower_cost() const;

	///
	/// \brief Retourne une solution de la population
	/// \param index : Indice de la solution
	/// \return Une solution
	Solution& solution(const unsigned int index) const;

	///
	/// \brief Permet de trier le vecteur de solution
	/// \param gauche
	/// \param droite
	void quickSort(int gauche, int droite);
	int partition(int gauche, int droite);

    void updateaccel(double g, unsigned int kbest);
	double best_fitness() const;
	double worst_fitness() const;
	Solution& best_solution() const;
	Solution& worst_solution() const;
	void evolution(int iter); /*makes an evolution step*/
	double g_update(int iter, int max_iter) const;
	unsigned int kBest(int iter, int max_tier) const;


	void main();
};

#endif
