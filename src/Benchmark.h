#ifndef GSA_BENCHMARK_H
#define GSA_BENCHMARK_H

///
/// \file Benchmark.h
/// \brief Fonctions permettant l'évaluation d'une solution


//topkek

///
/// \brief Fonction de Rosenbrock
/// \image html rosenbrock.png
/// \param[in] coord : Position de la solution à évaluer
/// \return Valeur de la fitness de la solution
double Rosenbrock(const std::vector<double>& coord);

///
/// \brief Fonction de Rastrigin
/// \image html rastrigin.png
/// \param[in] coord : Position de la solution à évaluer
/// \return Valeur de la fitness de la solution
double Rastrigin(const std::vector<double>& coord);

///
/// \brief Fonction de Ackley
/// \image html ackley.png
/// \param[in] coord : Position de la solution à évaluer
/// \return Valeur de la fitness de la solution
double Ackley(const std::vector<double>& coord);

///
/// \brief Fonction de Schwefel
/// \image html schwefel.png
/// \param[in] coord : Position de la solution à évaluer
/// \return Valeur de la fitness de la solution
double Schwefel(const std::vector<double>& coord);

///
/// \brief Fonction de Schaffer
/// \image html schaffer.png
/// \param[in] coord : Position de la solution à évaluer
/// \return Valeur de la fitness de la solution
double Schaffer(const std::vector<double>& coord);

///
/// \brief Fonction de Weierstrass
/// \param[in] coord : Position de la solution à évaluer
/// \return Valeur de la fitness de la solution
double Weierstrass(const std::vector<double>& coord);

#endif //GSA_BENCHMARK_H
