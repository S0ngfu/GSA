//
// Created by Songfu on 24/11/2016.
//

#include "Problem.h"

Problem::Problem():_dimension(30), LowerLimit{0}, UpperLimit{100}{}

int Problem::dimension() const {
    return _dimension;
}

friend std::ostream& Problem::operator<< (std::ostream& os, const Problem& pbm)
{

    return os;
}

friend std::istream& Problem::operator>> (std::istream& is, Problem& pbm)
{

    return is;
}
