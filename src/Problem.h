#ifndef GSA_PROBLEM_H
#define GSA_PROBLEM_H

///
/// \file Problem.h
/// \brief Problème dans lequel une solution évolue

#include <iostream>
#include <vector>

typedef double(*Fonction)(const std::vector<double>&);

///
/// \class Problem
/// \brief Classe contenant les paramètres d'un problème
class Problem
{
public:
    ///
    /// \brief Constructeur
    /// Constructeur de la classe Problem
    /// \param[in] lowLim : Limite inférieur de la solution
    /// \param[in] upLim  : Limite supérieur de la solution
    /// \param[in] dimension : Dimension du problème
    /// \param[in] f : Pointeur sur la fonction à optimiser
    Problem(double lowLim, double upLim, int dimension, Fonction f);
    ///
    /// \brief Destructeur
    /// Destructeur de la classe Problem
    ~Problem()=default;

    //friend std::ostream& operator<<(std::ostream& os, const Problem& pbm);
    //friend std::istream& operator>>(std::istream& is, Problem& pbm);

    ///
    /// \brief Renvoi la dimension du problème
    /// \return dimension
    int dimension() const;
    
    double LowerLimit, UpperLimit;

    ///
    /// \brief Renvoi la fonction à optimiser
    /// \return la fonction
    Fonction function() const;

    ///
    ///\brief Permet de changer de fonction de benchmark
    void switchBenchmark();
private:
    int _dimension;
    Fonction _fonction;
};


#endif //GSA_PROBLEM_H
