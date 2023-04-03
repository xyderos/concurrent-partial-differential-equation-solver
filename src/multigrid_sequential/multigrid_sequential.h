#pragma once

#include <string>
#include <vector>

using std::vector;

class multigrid_sequential {

	unsigned int grid_size, number_of_iterations;
	std::string file_name;

	vector<vector<vector<double>>> matrix;

	void multigrid_update_matrix();

	void iterate();

	void iterate(unsigned int number_of_iterations);

    public:
	multigrid_sequential(unsigned int grid_size_,
	    unsigned int number_of_iterations_, std::string file_name);
	auto run() -> int;
};
