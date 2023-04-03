#include "../../src/multigrid_sequential/multigrid_sequential.h"
#include "test_multigrid_sequential.h"

void
test_multigrid_sequential::test_case_one()
{
	auto grid = multigrid_sequential(29, 20, "results/ms1");
	grid.run();
}
void
test_multigrid_sequential::test_case_two()
{
	auto grid = multigrid_sequential(69, 20, "results/ms2");
	grid.run();
}
