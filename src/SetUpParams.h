#ifndef GSA_SETUPPARAMS_H
#define GSA_SETUPPARAMS_H

///
/// \file SetUpParams.h
/// \brief Gestion des paramètres

#include <iostream>

///
/// \class SetUpParams
/// \brief Classe contenant les paramètres de l'algorithme
class SetUpParams
{
private:
    unsigned int   _independent_runs;
    unsigned int   _nb_evolution_steps;
    unsigned int   _population_size;
    unsigned int   _solution_size;

public:
    SetUpParams ()=delete;

    ///
    /// \brief Constructeur
    /// Constructeur de la classe SetUpParams
    /// \param[in] runs : Nombre d'éxécution de l'algorithme
    /// \param[in] steps : Nombre d'évolution pour chaque éxécution
    /// \param[in] pop_size : Taille de la population
    /// \param[in] sol_size : Dimension du problème
    SetUpParams (unsigned int runs, unsigned int steps, unsigned int pop_size, unsigned int sol_size);

    //friend std::ostream& operator<< (std::ostream& os, const SetUpParams& setup);
    //friend std::istream& operator>> (std::istream& is, SetUpParams& setup);

    ///
    /// \return Nombre d'éxécutions de l'algorithme
    const unsigned int independent_runs() const;

    ///
    /// \return Nombre d'évolution par éxécution
    const unsigned int nb_evolution_steps() const;

    ///
    /// \return Taille de la population
    const unsigned int population_size() const;

    ///
    /// \return Dimension du problème
    const unsigned int solution_size() const;

    ///
    /// \brief Destructeur
    /// Destructeur par défaut de la classe SetUpParams
    ~SetUpParams()=default;
};


#endif //GSA_SETUPPARAMS_H
