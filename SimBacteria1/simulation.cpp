#include "environment.h"

int main(void)
{
	Life::Environment env;
	env.Report();
	for (auto clock = 1; clock != 5; ++clock)
		env.Cycle();
	env.Report();
}