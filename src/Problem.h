//
// Created by Songfu on 24/11/2016.
//

#ifndef GSA_PROBLEM_H
#define GSA_PROBLEM_H

#include <iostream>
#include <vector>

typedef double(*Fonction)(const std::vector<double>&);

class Problem
{
public:
    Problem(double lowLim, double upLim, int dimension, Fonction f);
    ~Problem()=default;

    //friend std::ostream& operator<<(std::ostream& os, const Problem& pbm);
    //friend std::istream& operator>>(std::istream& is, Problem& pbm);

    //Problem& operator=  (const Problem& pbm);
    //bool operator== (const Problem& pbm) const;
    //bool operator!= (const Problem& pbm) const;

    int dimension() const;
    double LowerLimit, UpperLimit;
    Fonction function() const;

private:
    int _dimension;
    Fonction _fonction;
};


#endif //GSA_PROBLEM_H
