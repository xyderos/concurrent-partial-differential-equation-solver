#include "../helpers/helpers.h"
#include "jacobi_concurrent.h"

#include <utility>

using std::string;

jacobi_concurrent::jacobi_concurrent(unsigned int grid_size_,
    unsigned int number_of_iterations_, unsigned int number_of_workers_,
    string file_name_)
    : grid_size(grid_size_)
    , number_of_iterations(number_of_iterations_)
    , number_of_workers(number_of_workers_)
    , file_name(std::move(file_name_))
    , matrix(helpers::jacobi_initialize_grid(grid_size))
{
}

auto
jacobi_concurrent::run() -> int
{
	for (unsigned int i = 0; i < number_of_iterations; ++i) {
		jacobi_update_matrix();
	}

	helpers::write_to_file(matrix, file_name, grid_size);

	return 0;
}

void
jacobi_concurrent::jacobi_update_matrix()
{
	// set the number of threads we wish to use, taken from the commandline.
	// Do the parallelize the for loop with omp.
	omp_set_num_threads(static_cast<int>(number_of_workers));

#pragma omp parallel for
	// do the calculations for all internal points of the grid (not boundary
	// points)
	for (unsigned int i = 1; i < grid_size - 1; ++i) {
		for (unsigned int j = 1; j < grid_size - 1; ++j) {

			this->matrix.at(1).at(i).at(
			    j) = (matrix.at(0).at(i - 1).at(j) +
				     matrix.at(0).at(i + 1).at(j) +
				     matrix.at(0).at(i).at(j - 1) +
				     matrix.at(0).at(i).at(j + 1)) *
			    POINT_TWENTY_FIVE;
		}
	}

	// make new matrix old matrix to prepare for next iteration, save old
	// matrix in new matrix so we can calculate maxdiff still
	vector<vector<double>> temp;

	auto *p1 = (&matrix.at(0));

	auto *p2 = (&matrix.at(1));

	temp = *p2;

	*p2 = *p1;

	*p1 = temp;
}

auto
jacobi_concurrent::max_diff() -> double
{
	double maxDiff = 0;

	for (unsigned int i = 0; i < grid_size; ++i) {
		for (unsigned int j = 0; j < grid_size; ++j) {

			double currentDiff = (1 - matrix.at(0).at(i).at(j));
			if (maxDiff < currentDiff) {
				maxDiff = currentDiff;
			}
		}
	}
	return maxDiff;
}
