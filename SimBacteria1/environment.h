#if !defined(ENVIRONMENT_H)
#define ENVIRONMENT_H

#include <list>

namespace Life
{
	// Forward declarations.
	class Bacterium;

	class Environment
	{
	public:
		Environment(void);

		void Cycle(void);
		void Report(void);

	protected:

		unsigned long long clock = 0;
		std::list<Bacterium> bacteria;
	};

	//enum class BacteriumStatus
	//{
	//	IDLE = 0x0,
	//	FISSION = 0x2,
	//	MOVING = 0x4
	//};

	//enum class BacteriumfissionStep
	//{

	//};

	enum class FissionPhase
	{
		A = 0,
		B = 1,
		C = 2,
		D = 3
	};

	class Bacterium
	{
	public:
		Bacterium(void) = default;
		explicit Bacterium(unsigned long long marker);
		void Action(std::list<Bacterium> &newBorns);
		void Report(void) const;
	
		const unsigned long long &marker = this->marker_;		// Read-only access.
		const FissionPhase &fissionPhase = this->fissionPhase_;	// Read-only access.
		
	protected:
		unsigned long long MakeNewMarker(void);
		void Reproduce(std::list<Bacterium> &newBorns);

		FissionPhase fissionPhase_ = FissionPhase::A;
		unsigned long long marker_ = 0;
		bool isHealthy = true;
		//BacteriumStatus status = BacteriumStatus::IDLE;
	};
}
#endif
