#pragma once

#include <string>
#include <vector>

using std::vector;

class multigrid_concurrent {

	unsigned int grid_size, number_of_iterations, number_of_workers;
	std::string file_name;

	vector<vector<vector<double>>> matrix;

	void multigrid_update_matrix();

	void iterate();

	void iterate(unsigned int number_of_iterations);

    public:
	multigrid_concurrent(unsigned int grid_size,
	    unsigned int number_of_iterations, unsigned int number_of_workers,
	    std::string file_name);
	auto run() -> int;
};
