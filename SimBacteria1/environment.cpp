#include "environment.h"

#include <iostream>

namespace Life
{
	Environment::Environment(void)
	{
		this->bacteria.emplace_back(0);
	}

	void Environment::Cycle(void)
	{
		++this->clock;
		std::list<Bacterium> new_borns;
		for (auto it = this->bacteria.begin(); it != this->bacteria.end(); ++it)
			it->Action(new_borns);
		if (new_borns.size() > 0)
			this->bacteria.splice(this->bacteria.end(), new_borns);
	}

	void Environment::Report(void)
	{
		std::cout << "Clock = " << this->clock << std::endl;
		std::cout << "Number of units = " << this->bacteria.size() << std::endl;
		for (auto it = this->bacteria.cbegin(); it != this->bacteria.cend(); ++it)
			it->Report();
	}


	Bacterium::Bacterium(unsigned long long marker) : Bacterium()
	{
		this->marker_ = marker;
	}

	void Bacterium::Action(std::list<Bacterium> &newBorns)
	{
		if (this->isHealthy)
			this->Reproduce(newBorns);
	}

	void Bacterium::Report(void) const
	{
		std::cout << "Marker = " << this->marker << std::endl;
		std::cout << "Fission Phase = " << static_cast<std::underlying_type<FissionPhase>::type>(this->fissionPhase) << std::endl;
	}

	unsigned long long Bacterium::MakeNewMarker(void)
	{
		unsigned long long part_1 = 0xFF00000000000000 & this->marker;
		unsigned long long part_2 = (0x0000FF0000000000 & this->marker) << 8;
		unsigned long long part_3 = (0x00000000FF000000 & this->marker) << 16;
		unsigned long long part_4 = (0x000000000000FF00 & this->marker) << 24;
		unsigned long long part_new = 0x00000000FFFFFFFF & std::rand();
		return part_1 | part_2 | part_3 | part_4 | part_new;
	}

	void Bacterium::Reproduce(std::list<Bacterium> &newBorns)
	{
		switch (this->fissionPhase)
		{
		case FissionPhase::A:
			this->fissionPhase_ = FissionPhase::B;
			break;
		case FissionPhase::B:
			this->fissionPhase_ = FissionPhase::C;
			break;
		case FissionPhase::C:
			this->fissionPhase_ = FissionPhase::D;
			break;
		case FissionPhase::D:
			newBorns.emplace_back(Bacterium(this->MakeNewMarker()));
			this->fissionPhase_ = FissionPhase::A;
			break;
		default:
			throw std::logic_error("Unknown Status");
		}
	}
}