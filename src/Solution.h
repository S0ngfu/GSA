//
// Created by Songfu on 24/11/2016.
//

#ifndef GSA_SOLUTION_H
#define GSA_SOLUTION_H

#include "Problem.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

class Solution
{
    //contient la déclaration d'une solution
public:
    Solution (const Problem& pbm);
    Solution (const Solution& sol);

    friend std::ostream& operator<< (std::ostream& os, const Solution& sol);
    friend std::istream& operator>> (std::istream& is, Solution& sol);

    const Problem& pbm() const;

    Solution& operator=  (const Solution& sol);
    bool operator== (const Solution& sol) const;
    bool operator!= (const Solution& sol) const;

    void initialize();
    double fitness();
    double get_fitness();

    unsigned int size() const;

    std::vector<double>& solution() const;

    double& position(const int index); //retournera une position du tableau d_coord
    void position(const int index, const double value);
    
    double distEucl(const Solution& sol) const;


private:
    std::vector<double> d_coord;
    double _current_fitness;
    const Problem& _pbm;
    double _mass;
};


#endif //GSA_SOLUTION_H
