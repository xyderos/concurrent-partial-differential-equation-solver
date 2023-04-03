#pragma once

#include <string>
#include <vector>

using std::vector;

class jacobi_concurrent {

	unsigned int grid_size, number_of_iterations, number_of_workers;
	std::string file_name;

	vector<vector<vector<double>>> matrix;

	// Laplace's PDE, or Nabla² takes the limit of each point tending
	// towards the average of its neighbours points, and how this varies
	// with time. This is why it is sometimes called the heat equation:
	// given an input in 1d, 2d, 3d ... where each point has a value
	// corresponding to its temperature, where the temperature is given as
	// f(x,y,z..) , as time -> infinity, the temperatures will reach an
	// equilibrium across the entire input space. A hot point surrounded by
	// very cold points will get colder quickly and the cold points will get
	// slightly warmer, until all of the points reach the same value.
	// Laplaces PDE: Nabla²(f(x,y,z...) = 0. This method simulates this, by
	// updating each point on the matrix to the average of its neighbouring
	// 4 points.
	void jacobi_update_matrix();

	// Calculate the values delta of each point from this iteration and
	// last, and return the value of the highest one. The smaller this value
	// is, the less effective each subsequent iteration is, and the closer
	// we are to the limit.
	auto max_diff() -> double;

    public:
	jacobi_concurrent(unsigned int grid_size_,
	    unsigned int number_of_iterations_, unsigned int number_of_workers_,
	    std::string file_name);
	auto run() -> int;
};
