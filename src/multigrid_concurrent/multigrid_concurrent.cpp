#include "../helpers/helpers.h"
#include "multigrid_concurrent.h"

#include <string>

#define FACTOR 5

using std::string;

multigrid_concurrent::multigrid_concurrent(unsigned int grid_size_,
    unsigned int number_of_iterations_, unsigned int number_of_workers_,
    string file_name_)
    : grid_size(grid_size_)
    , number_of_iterations(number_of_iterations_)
    , number_of_workers(number_of_workers_)
    , file_name(std::move(file_name_))
    , matrix(helpers::jacobi_initialize_grid(grid_size))
{
}

void
multigrid_concurrent::iterate()
{

	for (int i = 0; i < 4; ++i) {
		multigrid_update_matrix();
	}
}
void
multigrid_concurrent::iterate(unsigned int number_of_iterations_)
{

	for (unsigned int i = 0; i < number_of_iterations_; ++i) {
		multigrid_update_matrix();
	}
}

void
multigrid_concurrent::multigrid_update_matrix()
{
	auto g_s = matrix.at(0).size();

	omp_set_num_threads(static_cast<int>(number_of_workers));

#pragma omp parallel for

	// do the calculations for all internal points of the grid (not boundary
	// points)
	for (unsigned long i = 1; i < g_s - 1; ++i) {
		for (unsigned long j = 1; j < g_s - 1; ++j) {
			matrix.at(1).at(i).at(
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
multigrid_concurrent::run() -> int
{
	if ((grid_size - FACTOR) % 4 != 0) {
		return 1;
	}

	vector<vector<vector<double>>> matrix_ =
	    helpers::multigrid_initialize_grid(grid_size);

	for (int i = 0; i < 3; ++i) {

		iterate();

		helpers::restrict(matrix_);
	}

	helpers::restrict(matrix_);

	iterate(number_of_iterations);

	for (int i = 0; i < 3; ++i) {

		helpers::interpolate(matrix_);

		iterate();
	}

	helpers::write_to_file(matrix_, file_name, grid_size);

	return 0;
}
