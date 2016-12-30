#ifndef GSA_SOLUTION_H
#define GSA_SOLUTION_H

///
/// \file Solution.h
/// \brief Implémentation d'un solution

#include "Problem.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

///
/// \class Solution
/// \brief Classe contenant les données d'une solution
class Solution
{
public:
    ///
    /// \brief Constructeur
    /// Constructeur de la classe Solution
    /// \param[in] pbm : Problème dans lequel la solution évolue
    Solution (const Problem& pbm);

    ///
    /// \brief Constructeur par recopie
    /// Constructeur par recopie
    /// \param[in] sol : Solution à recopier
    Solution (const Solution& sol);

    const Problem& pbm() const;

    ///
    /// \brief Initialise la solution
    void initialize();

    ///
    /// \brief Calcule la fitness de la solution
    void fitness();

    ///
    /// \brief Renvoi la fitness de la solution
    /// \return Fitness
    double get_fitness() const;

    ///
    /// \brief Renvoi la taille de la solution
    /// \return Taille
    unsigned int size() const;

    ///
    /// \brief Permet de récupérer le tableau de coordonnées de la solution
    /// \return Tableau de coordonnées
    std::vector<double>& get_coord() const;

    double position(const int index);

    ///
    /// \brief Calcule la distance euclidienne entre 2 solutions
    /// \param[in] sol : Solution avec laquelle elle calcule la distance
    /// \return Distance euclidienne
    double distEucl(const Solution& sol) const;

    ///
    /// \brief Permet de normaliser le vecteur
    void normeVecteur();

    ///
    /// \brief Permet de récupérer la masse d'une solution
    /// \return La masse de la solution
    double get_mass() const;

    ///
    /// \brief Permet de modifier la masse d'une solution
    /// \param[in] mass : Nouvelle masse de la solution
    void set_mass(double mass);

    ///
    /// \brief Permet de déplacer une solution en fonction d'une durée
    /// \param[in] duration : Durée du déplacement
    void moveSolution(double duration);

    ///
    /// \brief Permet de modifier le vecteur d'accélération
    /// \param[in] accel : Valeur de l'accélération
    /// \param[in] position : Indice du tableau
    void set_vecteuraccel(const Solution& sol, double g);

    ///
    /// \brief Calcule la force de gravitation d'une composante par rapport à un individu
    /// \param[in] sol
    /// \param[in] i
    /// \param[in] g
    /// \return Force gravitationnelle
    double gravitationalValue(const Solution& sol, int i, double g);
private:
    std::vector<double> d_coord;
    double _current_fitness;
    const Problem& _pbm;
    double _mass;
    std::vector <double> _vecteuraccel;
};


#endif //GSA_SOLUTION_H
