#include "helpers.h"

#include <fstream>

auto
helpers::jacobi_initialize_grid(unsigned int grid_size)
    -> vector<vector<vector<double>>>
{
	auto matrix = vector<vector<vector<double>>>();

	// initialize the global matrix
	matrix.resize(2);
	matrix.at(0).resize(grid_size);
	matrix.at(1).resize(grid_size);

	for (unsigned int i = 0; i < grid_size; ++i) {

		matrix.at(0).at(i).resize(grid_size);
		matrix.at(1).at(i).resize(grid_size);
	}

	// set boundary values to 1
	for (unsigned int i = 0; i < grid_size; i += grid_size - 1) {

		if (grid_size == 1) {
			break;
		}
		for (unsigned int j = 0; j < grid_size; ++j) {

			matrix.at(0).at(i).at(j) = 1;
			matrix.at(0).at(j).at(i) = 1;
			matrix.at(1).at(i).at(j) = 1;
			matrix.at(1).at(j).at(i) = 1;
		}
	}
	// set internal values to 0
	for (unsigned int i = 1; i < grid_size - 1; ++i) {
		for (unsigned int j = 1; j < grid_size - 1; ++j) {
			matrix.at(0).at(i).at(j) = 0;
		}
	}

	return matrix;
}

void helpers::restrict(vector<vector<vector<double>>> &matrix)
{

	auto new_size = (matrix.at(0).size() + 1) / 2;

	vector<vector<vector<double>>> temp_matrix = jacobi_initialize_grid(
	    static_cast<unsigned int>(new_size));

	// for each interior point, update it according to G. Andrews textbook
	// p. 550-51
	for (unsigned int i = 1; i < new_size - 1; ++i) {
		for (unsigned int j = 1; j < new_size - 1; ++j) {
			auto correspondingI = 2 * i;
			auto correspondingJ = 2 * j;

			temp_matrix.at(0).at(i).at(
			    j) = matrix.at(0)[correspondingI][correspondingJ] *
				POINT_FINE +
			    (matrix.at(0)[correspondingI - 1][correspondingJ] +
				matrix.at(
				    0)[correspondingI + 1][correspondingJ] +
				matrix.at(
				    0)[correspondingI][correspondingJ - 1] +
				matrix.at(
				    0)[correspondingI][correspondingJ + 1]) *
				POINT_ONE_TWENTY_FIVE;
		}
	}

	matrix = temp_matrix;
}

void
helpers::interpolate(vector<vector<vector<double>>> &matrix)
{
	auto new_size = (matrix.at(0).size() + 1) / 2;

	// initialize the new matrix to size we want + boundary conditions
	vector<vector<vector<double>>> temp_matrix = jacobi_initialize_grid(
	    static_cast<unsigned int>(new_size));

	// iterate only over directly corresponding points
	for (unsigned int i = 2; i < new_size - 1; i += 2) {

		for (unsigned int j = 2; j < new_size - 1; j += 2) {

			// update the directly corresponding points
			auto correspondingI = i / 2;

			auto correspondingJ = j / 2;

			temp_matrix[0][i][j] = matrix.at(
			    0)[correspondingI][correspondingJ];

			// update the points directly next to directly
			// corresponding points
			temp_matrix[0][i - 1][j] += temp_matrix[0][i][j] *
			    POINT_FINE;

			temp_matrix[0][i + 1][j] += temp_matrix[0][i][j] *
			    POINT_FINE;

			temp_matrix[0][i][j - 1] += temp_matrix[0][i][j] *
			    POINT_FINE;

			temp_matrix[0][i][j + 1] += temp_matrix[0][i][j] *
			    POINT_FINE;

			// update the adjacent points
			temp_matrix[0][i - 1][j - 1] += temp_matrix[0][i][j] *
			    POINT_TWENTY_FIVE;

			temp_matrix[0][i - 1][j + 1] += temp_matrix[0][i][j] *
			    POINT_TWENTY_FIVE;

			temp_matrix[0][i + 1][j - 1] += temp_matrix[0][i][j] *
			    POINT_TWENTY_FIVE;

			temp_matrix[0][i + 1][j + 1] += temp_matrix[0][i][j] *
			    POINT_TWENTY_FIVE;
		}
	}
	matrix = temp_matrix;
}

static void
resize(vector<vector<vector<double>>> &matrix, unsigned int grid_size)
{

	matrix.resize(2);

	matrix.at(0).resize(grid_size);
	matrix.at(1).resize(grid_size);

	for (unsigned int i = 0; i < grid_size; ++i) {

		matrix.at(0)[i].resize(grid_size);

		matrix.at(1)[i].resize(grid_size);
	}
}

static void
set_dirichlet_boundary_conditions(vector<vector<vector<double>>> &matrix)
{
	auto grid_size = matrix.at(0).size();

	for (unsigned int i = 0; i < grid_size; i += grid_size - 1) {

		for (unsigned int j = 0; j < grid_size; ++j) {

			matrix.at(0)[i][j] = 1;

			matrix.at(0)[j][i] = 1;

			matrix.at(1)[i][j] = 1;

			matrix.at(1)[j][i] = 1;
		}
	}
}

auto
helpers::multigrid_initialize_grid(unsigned int grid_size)
    -> vector<vector<vector<double>>>
{
	auto matrix = vector<vector<vector<double>>>();

	resize(matrix, grid_size);

	set_dirichlet_boundary_conditions(matrix);

	for (unsigned int i = 1; i < grid_size - 1; ++i) {
		for (unsigned int j = 1; j < grid_size - 1; ++j) {
			matrix.at(0)[i][j] = 0;
		}
	}

	return matrix;
}

void
helpers::write_to_file(const vector<vector<vector<double>>> &matrix,
    const std::string &file_name, unsigned int grid_size)
{
	std::ofstream of(file_name);

	for (unsigned int i = 0; i < grid_size; ++i) {
		for (unsigned int j = 0; j < grid_size; ++j) {
			of << "|" << matrix.at(0)[i][j] << "|";
		}
	}
}
