#include "MyAlgorithm.h"
#include "Benchmark.h"

int menu()
{
    int input;
    do
    {
        std::cout<<"1 - Run\n2 - Change benchmark\n3 - Quit"<<std::endl;
        std::cin>>input;
    } while(input<1 && input>3);
    return input;
}

int main(int argc, char *argv[])
{
    Problem problem = Problem(-5, 10, 30, Rosenbrock);

    int choice=menu();
    while(choice != 1)
    {
        switch(choice)
        {
            default:
                break;
            case 2:
                problem.switchBenchmark();
                break;
            case 3:
                return 1;
        }
        choice=menu();
    }

    srand(time(NULL));
    SetUpParams setup = SetUpParams(30, 20000, 30, 30);
    MyAlgorithm GSA(problem, setup);
    GSA.main();

    return 0;
}
