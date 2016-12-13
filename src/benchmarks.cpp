const double PI = 3.14159265359;

double Rastrigin()
{
	int sum = 0;
	for (int i = 0; i < d_coord.size(); ++i)
		sum += pow(d_coord[i], 2) - 10 * cos(2 * PI * d_coord[i] );
	sum += 10 * d_coord.size();
	_current_fitness = sum;
	return _current_fitness;
}

double Ackley()
{
	int sum1 = 0;
	int sum2 = 0;
	int sum = 0;
	for(int i = 0; i < d_coord.size(); ++i)
	{
		sum1 += pow(d_coord[i], 2)
		sum2 += cos(2 * PI * d_coord[i])
	}
	sum = -20 * exp(-0.2 * sqrt((1 / 30) * sum1)) - exp((1 / 30) * sum2) + 20 + exp(1);
	_current_fitness = sum;
	return _current_fitness;
}

double Schwefel()
{
	int sum = 0;
	for(int i = 0; i < d_coord.size(); ++i)
		sum += d_coord[i] * sin(sqrt(abs(d_coord[i])))
	sum = 418.9829 * 30 - sum;
	_current_fitness = sum;
	return _current_fitness;
}

double Schaffer()
{
	int sum = 0;
	for(int i = 0; i < d_coord.size() - 1; ++i)
		sum += (pow(sin(pow(d_coord[i], 2) - pow(d_coord[i+1], 2)), 2) - 0.5) / (pow(1 + 0.001 * (pow(d_coord[i], 2) + pow(d_coord[i+1], 2)), 2));
	sum += 0.5;
	_current_fitness = sum;
	return _current_fitness;
}

double Weierstrass()
{
	int sum = 0;
	for(int j = 0; j < 50; ++j)
		for(int i = 0; i < d_coord.size(); ++i)
			sum += pow(0.5, j) * cos(pow(12, j) * PI * d_coord[i]);
	_current_fitness = sum;
	return _current_fitness; 
}
