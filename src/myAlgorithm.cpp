#include "myAlgorithm.cpp"


myAlgorithm::myAlgorithm(const Problem& pbm,const SetUpParams& setup): _setup{setup} {
	_solution.reserve(_setup.population_size());
	for (int i = 0; i < _setup.population_size(); ++i) {
		Solution *s = new Solution(pbm);
		_solution[i] = s;
	}
}

myAlgorithm::~myAlgorithm() {
	for (int i = 0; i < _setup.population_size(); ++i) {
		delete _solution[i];
	}
}

friend std::ostream& operator<< (std::ostream& os, const MyAlgorithm& myAlgo) {
	//toDo
}

friend std::istream& operator>> (std::istream& is, MyAlgorithm& myAlgo) {
	//toDo
}

MyAlgorithm& operator= (const MyAlgorithm& myAlgo) {
	//toDo
}

const SetUpParams& setup() const {
	return _setup;
}

void initialize() {
	for (int i = 0; i < _setup.population_size(); ++i) {
		_solution[i].initialize();
	}
}