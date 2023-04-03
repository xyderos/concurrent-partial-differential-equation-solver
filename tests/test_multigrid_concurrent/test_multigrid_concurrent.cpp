#include "../../src/multigrid_concurrent/multigrid_concurrent.h"
#include "test_multigrid_concurrent.h"

void
test_multigrid_concurrent::test_case_one()
{
	auto grid = multigrid_concurrent(29, 20, 1, "results/mc1");
	grid.run();
}
void
test_multigrid_concurrent::test_case_two()
{
	auto grid = multigrid_concurrent(29, 20, 2, "results/mc2");
	grid.run();
}
void
test_multigrid_concurrent::test_case_three()
{
	auto grid = multigrid_concurrent(29, 20, 3, "results/mc3");
	grid.run();
}
void
test_multigrid_concurrent::test_case_four()
{
	auto grid = multigrid_concurrent(29, 20, 4, "results/mc4");
	grid.run();
}
void
test_multigrid_concurrent::test_case_five()
{
	auto grid = multigrid_concurrent(69, 20, 1, "results/mc5");
	grid.run();
}
void
test_multigrid_concurrent::test_case_six()
{
	auto grid = multigrid_concurrent(69, 20, 2, "results/mc6");
	grid.run();
}
void
test_multigrid_concurrent::test_case_seven()
{
	auto grid = multigrid_concurrent(69, 20, 3, "results/mc7");
	grid.run();
}
void
test_multigrid_concurrent::test_case_eight()
{
	auto grid = multigrid_concurrent(69, 20, 4, "results/mc8");
	grid.run();
}
