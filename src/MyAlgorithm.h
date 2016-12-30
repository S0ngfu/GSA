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
	/// \param gauche : Extr�mit� gauche du tableau que l'on veut trier
	/// \param droite : Extr�mit� droite du tableau que l'on veut trier
	void quickSort(int gauche, int droite);
	
	///
	/// \brief Fonction auxiliaire pour la fonction quickSort
	/// \param gauche : Extr�mit� gauche du tableau que l'on veut trier
	/// \param droite
	int partition(int gauche, int droite);

	///
	/// \brief Modifie l'acc�l�ration de toutes les solutions en utilisant la formule de gravitation
	/// \param iter : Indice de l'�volution actuelle de l'ex�cution
	/// \param kbest : Les K meilleures solutions qui vont affecter les autres
    void updateAccel(int iter, unsigned int kbest);
    
    ///
	/// \brief Retourne la fitness de la meilleure solution
	double best_fitness() const;
	
	///
	/// \brief Retourne la fitness de la pire solution
	double worst_fitness() const;
	
	///
	/// \brief Retourne la meilleure solution
	Solution& best_solution() const;
	
	///
	/// \brief Retourne la pire solution
	Solution& worst_solution() const;
	
	///
	/// \brief Fait une �volution
	/// \param iter : Indice de l'�volution actuelle de l'ex�cution
	void evolution(int iter);
	
	///
	/// \brief Retourne la pire solution
	/// \param iter : Indice de l'�volution actuelle de l'ex�cution
	/// \param max_iter : Indice de la derni�re �volution de l'ex�cution
	double gUpdate(int iter, int max_iter) const;
	
	///
	/// \brief Retourne les K meilleures solutions qui vont affecter les autres
	/// \param iter : Indice de l'�volution actuelle de l'ex�cution
	/// \param max_iter : Indice de la derni�re �volution de l'ex�cution
	unsigned int kBest(int iter, int max_tier) const;

	///
	/// \brief Lance l'algorithme
	void main();
};

#endif
