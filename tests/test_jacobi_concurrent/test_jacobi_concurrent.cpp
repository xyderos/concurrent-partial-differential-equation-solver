#include "../../src/jacobi_concurrent/jacobi_concurrent.h"
#include "test_jacobi_concurrent.h"

void
test_jacobi_concurrent::test_case_one()
{
	auto grid = jacobi_concurrent(100, 20, 1, "results/jc1");
	grid.run();
}
void
test_jacobi_concurrent::test_case_two()
{
	auto grid = jacobi_concurrent(100, 20, 2, "results/jc2");
	grid.run();
}
void
test_jacobi_concurrent::test_case_three()
{
	auto grid = jacobi_concurrent(100, 20, 3, "results/jc3");
	grid.run();
}
void
test_jacobi_concurrent::test_case_four()
{
	auto grid = jacobi_concurrent(100, 20, 4, "results/jc4");
	grid.run();
}
void
test_jacobi_concurrent::test_case_five()
{
	auto grid = jacobi_concurrent(200, 20, 4, "results/jc5");
	grid.run();
}
void
test_jacobi_concurrent::test_case_six()
{
	auto grid = jacobi_concurrent(200, 20, 4, "results/jc6");
	grid.run();
}
void
test_jacobi_concurrent::test_case_seven()
{
	auto grid = jacobi_concurrent(200, 20, 4, "results/jc7");
	grid.run();
}
void
test_jacobi_concurrent::test_case_eight()
{
	auto grid = jacobi_concurrent(200, 20, 4, "results/jc8");
	grid.run();
}
