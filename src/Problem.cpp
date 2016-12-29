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

void Problem::switchBenchmark() {
    int input;
    do
    {
        std::cout<<"\t1 - Rosenbrock\n\t2 - Rastrigin\n\t3 - Ackley\n\t4 - Schwefel\n"
                "\t5 - Schaffer\n\t6 - Weierstrass\n"<<std::endl;
        std::cin>>input;
    } while(input<1 && input>6);

    switch(input) //ToDo change parameters for each bench
    {
        default:
            break;
        case 1:
            _fonction=Rosenbrock;
            break;
        case 2:
            _fonction=Rastrigin;
            break;
        case 3:
            _fonction=Ackley;
            break;
        case 4:
            _fonction=Schwefel;
            break;
        case 5:
            _fonction=Schaffer;
            break;
        case 6:
            _fonction=Weierstrass;
            break;
    }
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