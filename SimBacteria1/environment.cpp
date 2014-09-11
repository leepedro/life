#include "environment.h"

#include <iostream>
#include <random>

namespace Life
{
	Environment::Environment(void)
	{
		// NOTE: the 1 is the argument of Bacterium(1) instead of the ctor itself.
		this->bacteria.emplace_back(1);
	}

	void Environment::Cycle(void)
	{
		++this->clock;
		std::list<Bacterium> new_borns;
		// NOTE: the iterator needs to be incremented inside of the loop because
		// the current iterator is invalid after std::list<T>::erase().
		for (auto it = this->bacteria.begin(); it != this->bacteria.end();)
		{
			if (it->age > 18)
				it = this->bacteria.erase(it);
			else
			{
				it->Action(new_borns);
				++it;
			}				
		}
		if (new_borns.size() > 0)
			this->bacteria.splice(this->bacteria.end(), new_borns);
	}

	void Environment::ReportLong(void) const
	{
		this->ReportShort();
		for (auto it = this->bacteria.cbegin(); it != this->bacteria.cend(); ++it)
			it->Report();
	}

	void Environment::ReportShort(void) const
	{
		std::cout << "Clock = " << this->clock << std::endl;
		std::cout << "Number of units = " << this->bacteria.size() << std::endl;
	}


	Bacterium::Bacterium(unsigned long long markerSrc) : marker_(markerSrc) {}

	void Bacterium::Action(std::list<Bacterium> &newBorns)
	{
		if (this->age > 12)
			this->isHealthy = false;
		if (this->isHealthy)
			this->Reproduce(newBorns);

		++this->age_;
	}

	void Bacterium::Report(void) const
	{
		std::cout << "Marker = " << this->marker << std::endl;
		std::cout << "Fission Phase = " << static_cast<std::underlying_type<FissionPhase>::type>(this->fissionPhase) << std::endl;
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
			newBorns.emplace_back(MakeNewMarker(this->marker));
			this->fissionPhase_ = FissionPhase::A;
			break;
		default:
			throw std::logic_error("Unknown Status");
		}
	}


	unsigned long long MakeNewMarker(unsigned long long seed)
	{
		unsigned long long byte_0 = 0xFF00000000000000 & seed;
		unsigned long long byte_1 = 0x00FF000000000000 & seed;
		unsigned long long byte_2 = 0x0000FF0000000000 & seed;
		unsigned long long byte_3 = 0x000000FF00000000 & seed;
		unsigned long long byte_4 = 0x00000000FF000000 & seed;
		unsigned long long byte_5 = 0x0000000000FF0000 & seed;
		unsigned long long byte_6 = 0x000000000000FF00 & seed;
		unsigned long long byte_7 = 0x00000000000000FF & seed;

		// Generate a random number between 0 and maximum value of unsigned int.
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<unsigned int> distribution(0);
		unsigned long long bytes_new = 0x00000000FFFFFFFF & distribution(gen);		
		return byte_0 | (byte_2 << 8) | (byte_4 << 16) | (byte_6 << 24) | bytes_new;
	}
}