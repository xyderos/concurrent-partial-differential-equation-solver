#pragma once

#include <omp.h>

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#define POINT_FINE .5
#define POINT_TWENTY_FIVE .25
#define POINT_ONE_TWENTY_FIVE .125

using std::vector;

namespace helpers {

// a method which takes the gridsize and initializes our matrix to what it's
// supposed to be (border cells = 1, everything else = 0)
auto jacobi_initialize_grid(unsigned int grid_size)
    -> vector<vector<vector<double>>>;

void write_to_file(const vector<vector<vector<double>>> &, const std::string &,
    unsigned int);

void restrict(vector<vector<vector<double>>> &matrix);

void interpolate(vector<vector<vector<double>>> &matrix);

auto multigrid_initialize_grid(unsigned int grid_size)
    -> vector<vector<vector<double>>>;
}
