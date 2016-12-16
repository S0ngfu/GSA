//
// Created by Simon on 16/11/2016.
//

#include "MyAlgorithm.h"
#include "Benchmark.h"

int menu()
{
    int input;
    do
    {
        std::cout<<"1 - Run\n2 - Change benchmark\n 3 - Quit"<<std::endl;
        std::cin>>input;
    } while(input<1 && input>3);
    return input;
}

int main(int argc, char *argv[])
{
    Problem problem = Problem(-5,12,30,Rastrigin);

    int choice=menu();
    while(choice != 1)
    {
        switch(choice)
        {
            default:
                break;
            case 2:
                //ToDo problem.switchBenchmark();
                break;
            case 3:
                std::exit;
        }
        choice=menu();
    }

/*ToDo ? Pouvoir modifier les paramètres du programme sans toucher au code
 * Il faudrait donc pouvoir mettre en paramètre du constructeur un lien
 * vers un fichier. Dans le cas ou se fichier n'est pas sous le bon format,
 * ne contient pas les paramètres sous la bonne forme, il appel
 * le constructeur par défaut*/

    SetUpParams setup = SetUpParams();
    MyAlgorithm GSA(problem, setup);
    GSA.main();

    return 0;
}