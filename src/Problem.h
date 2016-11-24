//
// Created by Songfu on 24/11/2016.
//

#ifndef GSA_PROBLEM_H
#define GSA_PROBLEM_H

#include <iostream>

class Direction;

class Problem
{
public:
    Problem();
    ~Problem();

    friend std::ostream& operator<< (std::ostream& os, const Problem& pbm);
    friend std::istream& operator>> (std::istream& is, Problem& pbm);

    Problem& operator=  (const Problem& pbm);
    bool operator== (const Problem& pbm) const;
    bool operator!= (const Problem& pbm) const;

    Direction direction () const; //Maximize or Minimize
    int dimension() const;
    double LowerLimit, UpperLimit;

private:

    int _dimension;
};


#endif //GSA_PROBLEM_H
