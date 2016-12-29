#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include "Benchmark.h"

double Rosenbrock(const std::vector<double>& coord)
{
	double sum = 0;
	for (int i = 0; i < coord.size() / 2; ++i)
		sum += 100 * pow((pow(coord[2*i], 2) - coord[2*i+1]), 2) + pow(coord[2*i] - 1, 2);
	return sum;
}

double Rastrigin(const std::vector<double>& coord)
{
	double sum = 0;
	for (int i = 0; i < coord.size(); ++i)
		sum += pow(coord[i], 2) - 10 * cos(2 * M_PI * coord[i] );
	sum += 10 * coord.size();
	return sum;
}

double Ackley(const std::vector<double>& coord)
{
	double sum1 = 0;
	double sum2 = 0;
	double sum = 0;
	for(int i = 0; i < coord.size(); ++i)
	{
		sum1 += pow(coord[i], 2);
		sum2 += cos(2 * M_PI * coord[i]);
	}
	sum = -20 * exp(-0.2 * sqrt((1 / 30) * sum1)) - exp((1 / 30) * sum2) + 20 + exp(1);
	return sum;
}

double Schwefel(const std::vector<double>& coord)
{
	double sum = 0;
	for(int i = 0; i < coord.size(); ++i)
		sum += coord[i] * sin(sqrt(abs(coord[i])));
	sum = 418.9829 * 30 - sum;
	return sum;
}

double Schaffer(const std::vector<double>& coord)
{
	double sum = 0;
	for(int i = 0; i < coord.size() - 1; ++i)
		sum += (pow(sin(pow(coord[i], 2) - pow(coord[i+1], 2)), 2) - 0.5) / (pow(1 + 0.001 * (pow(coord[i], 2) + pow(coord[i+1], 2)), 2));
	sum += 0.5;
	return sum;
}

double Weierstrass(const std::vector<double>& coord)
{
	double sum = 0;
	for(int j = 0; j < 50; ++j)
		for(int i = 0; i < coord.size(); ++i)
			sum += pow(0.5, j) * cos(pow(12, j) * M_PI * coord[i]);
	return sum;
}
