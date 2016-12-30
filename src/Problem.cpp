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

    switch(input)
    {
        default:
            break;
        case 1:
            _fonction=Rosenbrock;
            LowerLimit = -5;
			UpperLimit = 10;
            break;
        case 2:
            _fonction=Rastrigin;
            LowerLimit = -5.12;
			UpperLimit = 5.12;
            break;
        case 3:
            _fonction=Ackley;
            LowerLimit = -32.768;
			UpperLimit = 32.768;
            break;
        case 4:
            _fonction=Schwefel;
            LowerLimit = -500;
			UpperLimit = 500;
            break;
        case 5:
            _fonction=Schaffer;
            LowerLimit = -100;
			UpperLimit = 100;
            break;
        case 6:
            _fonction=Weierstrass;
            LowerLimit = -2;
			UpperLimit = 2;
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
