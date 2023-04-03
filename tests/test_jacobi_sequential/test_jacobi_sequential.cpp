#include "../../src/jacobi_sequential/jacobi_sequential.h"
#include "test_jacobi_sequential.h"

void
test_jacobi_sequential::test_case_one()
{
	auto grid = jacobi_sequential(100, 20, "results/js1");
	grid.run();
}
void
test_jacobi_sequential::test_case_two()
{
	auto grid = jacobi_sequential(200, 20, "results/js2");
	grid.run();
}
