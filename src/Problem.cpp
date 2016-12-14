//
// Created by Songfu on 24/11/2016.
//

#include "Problem.h"
#include "Benchmark.h"

Problem::Problem(double lowLim, double upLim, int dimension, Fonction f):
        LowerLimit{lowLim}, UpperLimit{upLim}, _dimension{dimension}, _fonction{f}
{
}

int Problem::dimension() const {
    return _dimension;
}

Fonction Problem::function() const {
    return _fonction;
}

/*
std::ostream& Problem::operator<<(std::ostream& os, const Problem& pbm)
{
    return os;
}

std::istream& Problem::operator>>(std::istream& is, Problem& pbm)
{
    return is;
}
*/