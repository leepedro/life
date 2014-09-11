#include "environment.h"

#include <iostream>

int main(int argc, char *argv[])
{
	Life::Environment env;
	env.ReportLong();
	int count = 0;
	if (argc == 1)
		count = 10;
	else
		count = std::atoi(argv[1]);
	std::clog << "Starting iteration" << std::endl;
	for (auto clock = 1; clock != count; ++clock)
		env.Cycle();
	env.ReportShort();
	std::clog << "Completed." << std::endl;
}