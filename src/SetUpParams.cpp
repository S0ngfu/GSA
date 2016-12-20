//
// Created by Songfu on 24/11/2016.
//

#include "SetUpParams.h"

SetUpParams::SetUpParams():_independent_runs{1},
                           _nb_evolution_steps{200},
                           _population_size{30},
                           _solution_size{30}
{
}

SetUpParams::SetUpParams(unsigned int runs, unsigned int steps, unsigned int pop_size, unsigned int sol_size):
                            _independent_runs{runs},
                            _nb_evolution_steps{steps},
                            _population_size{pop_size},
                            _solution_size{sol_size}
{
}

const unsigned int SetUpParams::independent_runs() const
{
    return _independent_runs;
}

const unsigned int SetUpParams::nb_evolution_steps() const
{
    return _nb_evolution_steps;
}

const unsigned int SetUpParams::population_size() const
{
    return _population_size;
}

const unsigned int SetUpParams::solution_size() const
{
    return _solution_size;
}

void SetUpParams::independent_runs(const unsigned int val)
{
    _independent_runs=val;
}

void SetUpParams::nb_evolution_steps(const unsigned int val)
{
    _nb_evolution_steps=val;
}

void SetUpParams::population_size(const unsigned int val)
{
    _population_size=val;
}

void SetUpParams::solution_size(const unsigned int val)
{
    _solution_size=val;
}
